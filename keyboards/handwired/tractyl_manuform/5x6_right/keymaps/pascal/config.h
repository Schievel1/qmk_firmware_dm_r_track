#pragma once

/*******************************/
/*  d e b u g   d e f i n e s  */
/*******************************/
// #define DEBUG_MATRIX_SCAN_RATE

/*****************************************/
/*  b o o t m a g i c   l i t e   k e y  */
/*****************************************/
/* We want the top left key to be the bootmagic lite key.
 * Hold this key down while plugging in the keyboard to put the MCU
 * into bootloader mode. Be aware that (since we are defining MASTER_RIGHT
 * further down) the key for the left half is also the TOP LEFT key. */

/* #define BOOTMAGIC_LITE_ROW 6 */ // this is only here for reference, it is
                                   // defined like this in 5x6_right config.h
                                   // already
// we want to have the top left key to be the bootmagic lite key
// pressing the top right key (predefined in 5x6_right config.h
// is inconvenient)
#undef BOOTMAGIC_COLUMN_RIGHT // we want to have the top left key to be
                                   // the bootmagic lite key. Pressing the
                                   // top right key (like defined in 5x6_right config.h
                                   // is inconvenient)
#define BOOTMAGIC_COLUMN 0
#define BOOTMAGIC_ROW 0
#define BOOTMAGIC_COLUMN_RIGHT 6

// #define NO_ACTION_LAYER
// #define NO_ACTION_TAPPING
// #define NO_ACTION_ONESHOT
/*************************/
/*  s p a c e  c a d e t */
/*************************/
#define LSPO_KEYS KC_LSFT, KC_LSFT, KC_LBRC
#define RSPC_KEYS KC_RSFT, KC_LSFT, KC_RBRC

/***********************/
/*  i d l e   m o d e  */
/***********************/
#define IDLE_TIMEOUT_SECS 10

/*************************************************************************************************************************/
/*  S p l i t   o p t i o n s */
#define MASTER_RIGHT

/*  T h i s   i s   t o   h a v e   l a y e r   d a t a   o f
 *  t h e   m a s t e r   o n   t h e   s l a v e   s i d e  */
/************************************************************************************************************************/
#define SPLIT_TRANSPORT_MIRROR
#define SPLIT_TRANSACTION_IDS_USER USER_SYNC_A
#define SPLIT_LAYER_STATE_ENABLE
#define SPLIT_LED_STATE_ENABLE
#define SPLIT_ACTIVITY_ENABLE
#define SPLIT_WPM_ENABLE
#define SPLIT_OLED_ENABLE
#define USER_COM_POLL_TIME_MS 100 // user data is sent between the two halfes by this time in milliseconds

/*********************************/
/*  E n c o d e r   c o n f i g  */
/*********************************/
#define ENCODER_RESOLUTION 1

/*****************************************************/
/*  P M W 3 3 6 0   t r a c k b a l l   s e n s o r  */
/*****************************************************/
#define PMW33XX_LIFTOFF_DISTANCE 0x08
#define POINTING_DEVICE_ROTATION_180
#undef ROTATIONAL_TRANSFORM_ANGLE
#define ROTATIONAL_TRANSFORM_ANGLE -15
#define CHARYBDIS_MINIMUM_DEFAULT_DPI 1600
#define CHARYBDIS_DRAGSCROLL_DPI 200
#define CHARYBDIS_DRAGSCROLL_REVERSE_Y

/***************************************************/
/*  I L I 9 3 4 1   b i g   L E D   d i s p l a y  */
/***************************************************/
#define ILI9341_CS_PIN C15
#define ILI9341_DCRS_PIN B10
#define ILI9341_RESET_PIN B2
// LED backlight of the screen
// Using the audio pin from the original Tracktyl, since we dont have audio anyway
#undef AUDIO_PIN
#undef AUDIO_PWM_DRIVER
#undef AUDIO_PWM_CHANNEL
#undef AUDIO_PWM_PAL_MODE
#define BACKLIGHT_PIN B1
#define BACKLIGHT_PWM_DRIVER PWMD3
#define BACKLIGHT_PWM_CHANNEL 4
#define BACKLIGHT_PAL_MODE 2
#define BACKLIGHT_LEVELS 5

#undef NO_DEBUG
#undef NO_PRINT
// #undef OLED_TIMEOUT
// #define OLED_TIMEOUT 0
#define OLED_DISABLE_TIMEOUT
#define OLED_FADE_OUT
#define OLED_FADE_OUT_INTERVAL 15
#define OLED_UPDATE_INTERVAL 50
// #define SPLIT_USB_DETECT
// #define NO_USB_STARTUP_CHECK
