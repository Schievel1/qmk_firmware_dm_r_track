/* Copyright 2020 Pascal Jaeger <pascal.jaeger@leimstift.de>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "process_key_override.h"
#include "tractyl_manuform.h"
#include "wpm.h"
#include QMK_KEYBOARD_H
#include "pointing_device.h"
#include "debug.h"

#include "oled_driver.h"

// user level imports
#include "keymap.h"
#include "transport.h"
#include "oled_display.h"

// debugging:
#ifdef CONSOLE_ENABLE
#    include "print.h"
#endif


// global declarations for idle mode
static bool idle_mode = false;
bool get_idle_mode(void)
{
	return idle_mode;
}
void set_idle_mode(bool toset)
{
    idle_mode = toset;
}

static bool fake_mode = false;
bool get_fake_mode(void)
{
    return fake_mode;
}
void set_fake_mode(bool toset)
{
	fake_mode = toset;
}

void housekeeping_task_user(void) {
    master_slave_com();
    // enable sniping mode with lower layer
    charybdis_set_pointer_sniping_enabled(biton32(layer_state) == _LOWER);
    // enable dragscroll mode when left shift key is rressed
    charybdis_set_pointer_dragscroll_enabled(biton32(layer_state) == _RAISE);

    if (!idle_mode && last_input_activity_elapsed() > IDLE_TIMEOUT_SECS * 1000) {
		oled_clear();
        idle_mode = true;
    } else if (idle_mode && last_input_activity_elapsed() <= IDLE_TIMEOUT_SECS * 1000) {
        oled_clear();
        idle_mode = false;
    }

    // read chip timer to generate random number for cat idle blinks
    set_anim_frame_duration1_old(timer_read32() % 10);
}

/***********/
/*  i n i t */
/***********/
void keyboard_post_init_user(void) {
    // Debug: Customise these values to desired behaviour
    debug_config.enable = false;
    debug_config.matrix = false;
    debug_config.keyboard = false;
    debug_config.mouse    = false;
    // user comms
    user_sync_init();
    // turn numlock on on startup
    if (!(host_keyboard_led_state().num_lock)) {
        register_code(KC_NUM_LOCK); //        unregister_code(KC_NUM_LOCK);
    }
}

/*******************/
/*  k e y m a p s  */
/*******************/
const key_override_t   lcbr_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_LCBR, KC_LBRC); // Shift { is [
const key_override_t   rcbr_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_RCBR, KC_RBRC); // Shift } is ]
const key_override_t*  key_overrides[]   = {&lcbr_key_override, &rcbr_key_override};

enum custom_keycodes {
	KC_FAKE = SAFE_RANGE,
};
// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_DVORAK] = LAYOUT_5x6_right(
KC_GRV,     KC_1,    KC_2,    KC_3 ,    KC_4,    KC_5,                  KC_6,    KC_7,       KC_8,      KC_9,      KC_0,   KC_EQL,
KC_TAB,  KC_QUOT, KC_COMM,   KC_DOT,    KC_P,    KC_Y,                  KC_F,    KC_G,       KC_C,      KC_R,      KC_L,  KC_SLSH,
KC_ESC,     KC_A,    KC_O,     KC_E,    KC_U,    KC_I,                  KC_D,    KC_H,       KC_T,      KC_N,      KC_S,  KC_MINS,
KC_NO,   KC_SCLN,    KC_Q,     KC_J,    KC_K,    KC_X,                  KC_B,    KC_M,       KC_W,      KC_V,      KC_Z,  KC_BSLS,
                  KC_LBRC,  KC_RBRC,                                                      KC_PGUP,     KC_PGDN,
                                   SC_LSPO,    KC_SPC,                    SC_RSPC,
                                   KC_LCTL,    LOWER,                     KC_BSPC,
                                   KC_LALT,    KC_LGUI,        KC_ENT, KC_RGUI
),

  [_LOWER] = LAYOUT_5x6_right(
QK_BOOT,     KC_F1,    KC_F2,    KC_F3,         KC_F4,     KC_F5,          KC_F6,   KC_F7,     KC_F8,       KC_F9,      KC_F10,     KC_DEL,
QK_RBT,    _______, _______,  _______,       _______,   KC_LCBR,        KC_RCBR, MS_BTN2,   BS_NORM,     BS_TOGG,      EE_CLR,    QK_BOOT,
_______,    _______, _______,    RAISE,        KC_DEL,   KC_LPRN,        KC_RPRN, KC_LEFT,     KC_UP,     KC_DOWN,     KC_RGHT,    KC_PIPE,
KC_CAPS ,   _______, _______,  LCTL(KC_X), LCTL(KC_C),LCTL(KC_V),        _______, MS_BTN1,   BL_TOGG,       BL_UP,     BL_DOWN,    DB_TOGG,
                   _______,_______,                                                       _______,_______,
                                         _______,_______,                         _______,
                                         _______,_______,                         _______,
                                         _______,_______,                 _______,_______
),

  [_RAISE] = LAYOUT_5x6_right(
_______, _______, _______, _______, _______, _______,                    _______,  KC_NUM, KC_PSLS, KC_PAST, KC_PMNS, KC_CALC,
_______, _______, _______, _______, _______, KC_LBRC,                    KC_RBRC,   KC_P7,   KC_P8,   KC_P9,   KC_PPLS, KC_MUTE,
KC_FAKE, _______, _______, _______, _______, KC_LPRN,                    KC_RPRN,   KC_P4,   KC_P5,   KC_P6,   _______, KC_VOLU,
_______, _______, _______, _______, _______, _______,                    KC_P0,     KC_P1,   KC_P2,   KC_P3,   KC_PEQL, KC_VOLD,
                   _______,_______,                                                         KC_DOT, KC_COMM,
                                         _______,_______,                     _______,
                                         _______,_______,                     _______,
                                         _______,_______,             _______,_______
),};
// clang-format on

/*****************************/
/*  f o r   e n c o d e r s  */
/*****************************/
bool encoder_update_user(uint8_t index, bool clockwise) {
    // dprintf("encoder index: %d\n", index);
    if (index == 1) // master side
    {
        if (clockwise) {
            tap_code(MS_WHLU);
        } else {
            tap_code(MS_WHLD);
        }
    }
    if (index == 0) // slave side
    {
        if (clockwise) {
            tap_code(MS_WHLU);
        } else {
            tap_code(MS_WHLD);
        }
    }
    return true;
}

/*******************************************/
/*  k e y b o a r d   i d l e   t i m e r  */
/*******************************************/
bool process_record_user(uint16_t keycode, keyrecord_t* record) {
	if (record->event.pressed) {
        set_fake_mode(false);
    }

    switch (keycode) {
        case KC_FAKE:
            if (record->event.pressed) {
                if (!get_fake_mode()) {
					set_fake_mode(true);
					}
				else {
                        set_fake_mode(false);
				}
            }
			return true;
        /* KEYBOARD PET STATUS START */
        case KC_LCTL:
        case KC_RCTL:
            if (record->event.pressed) {
                set_sneaking(true);
                // DragScrollX = 255;
            } else {
                set_sneaking(false);
                // DragScrollX = 6;
            }
            return true;
        case KC_SPC:
            if (record->event.pressed) {
				set_jumping(true);
            } else {
				set_jumping(false);
            }
            return true;
        case SC_LSPO:
            if (record->event.pressed && get_current_wpm() > MIN_WALK_SPEED) {
                set_jumping(true);
            } else {
                set_jumping(false);
            }
            return true;
        /* KEYBOARD PET STATUS END */
    }

    dprintf("KL: kc: 0x%04X, col: %2u, row: %2u, pressed: %u, time: %5u, int: %u, count: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
    dprintf("kc: %s\n", get_keycode_string(keycode));

    return true;
}

report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
	static bool togg = false;
	if (fake_mode) {
		if (togg) {
            mouse_report.x = 10;
			togg = false;
        } else {
            mouse_report.x = -10;
			togg = true;
        }
	}

    return mouse_report;
}
