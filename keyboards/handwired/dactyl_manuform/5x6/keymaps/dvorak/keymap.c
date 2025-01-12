#include QMK_KEYBOARD_H


enum custom_layers {
    _DVORAK,
    _LOWER,
    _RAISE,
};


#define RAISE MO(_RAISE)
#define LOWER MO(_LOWER)


const key_override_t   lcbr_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_LCBR, KC_LBRC); // Shift { is [
const key_override_t   rcbr_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_RCBR, KC_RBRC); // Shift } is ]
const key_override_t** key_overrides     = (const key_override_t*[]){&lcbr_key_override, &rcbr_key_override, NULL};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_DVORAK] = LAYOUT_5x6(
                         KC_GRV,     KC_1,    KC_2,    KC_3 ,    KC_4 ,    KC_5,                  KC_6    ,    KC_7 ,       KC_8 ,      KC_9 ,      KC_0        ,KC_EQL,
                         KC_TAB,     KC_QUOT, KC_COMM, KC_DOT  , KC_P    , KC_Y   ,               KC_F    ,    KC_G       , KC_C      , KC_R      , KC_L ,       KC_SLSH,
                         KC_ESC, KC_A ,   KC_O   , KC_E    , KC_U    , KC_I   ,               KC_D    ,    KC_H       , KC_T      , KC_N      , KC_S        ,KC_MINS,
                         KC_NO,      KC_SCLN, KC_Q   , KC_J    , KC_K    , KC_X   ,               KC_B    ,    KC_M       , KC_W   ,    KC_V    ,   KC_Z     ,   KC_BSLS,
                                          KC_LBRC, KC_RBRC,                                                       KC_PGUP, KC_PGDN,
                                                            KC_LSFT,    KC_SPC,              KC_LGUI,KC_RSFT,
                                                            KC_LCTL,    KC_SPC,              KC_LGUI,KC_BSPC,
                                                            KC_LALT,    LOWER,               KC_ENT, KC_RALT
                         ),

  [_LOWER] = LAYOUT_5x6(

                        KC_TILD,     KC_F1,    KC_F2,    KC_F3,         KC_F4,     KC_F5,        KC_F6,   KC_F7,     KC_F8,     KC_F9,       KC_F10,     KC_DEL ,
                        _______,    _______, _______,  _______,       _______,   KC_LCBR,        KC_RCBR, KC_BTN2,   _______,   _______  ,   _______ ,   _______,
                        _______,    _______, _______,  RAISE,     KC_DEL,   KC_LPRN,        KC_RPRN, KC_LEFT ,  KC_UP,     KC_DOWN,     KC_RGHT,    KC_PIPE,
                        KC_CAPS ,   _______, _______,  LCTL(KC_X), LCTL(KC_C),LCTL(KC_V),        _______, KC_BTN1  , _______,   _______,     _______,    _______,
                                           _______,_______,                                                       _______,_______,
                                                                 _______,_______,                 _______,_______,
                                                                 _______,_______,                 _______,_______,
                                                                 _______,_______,                 _______,_______
                        ),

  [_RAISE] = LAYOUT_5x6(

                        _______, _______, _______, _______, _______, _______,                    _______, KC_NLCK, KC_PSLS, KC_PAST, KC_PMNS, KC_CALC,
                        _______, _______, _______, _______, _______, KC_LBRC,                    KC_RBRC, KC_P7,   KC_P8,   KC_P9,   KC_PPLS, KC_MUTE,
                        _______, _______, _______, _______, _______, KC_LPRN,                    KC_RPRN, KC_P4,   KC_P5,   KC_P6,   _______, KC_VOLU,
                        _______, _______, _______, _______, _______, _______,                    KC_P0,   KC_P1,   KC_P2,   KC_P3,   KC_PEQL, KC_VOLD,
                                           _______,_______,                                                         KC_DOT, KC_COMM,
                                                                 _______,_______,             _______,_______,
                                                                 _______,_______,             _______,_______,
                                                                 _______,_______,             _______,_______
                        ),
};
