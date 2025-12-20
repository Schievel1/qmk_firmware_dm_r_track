BOOTLOADER = tinyuf2

CONSOLE_ENABLE = yes

SWAP_HANDS_ENABLE                = no
MAGIC_ENABLE = yes
BOOTMAGIC_ENABLE = yes
COMMAND_ENABLE = no
WPM_ENABLE = yes
NO_SUSPEND_POWER_DOWN = yes

# RGB_MATRIX_ENABLE = yes
# RGB_MATRIX_DRIVER = ws2812

# ENCODER_ENABLE = yes

# for the small oled display
OLED_ENABLE = yes
I2C_DRIVER_REQUIRED = yes
# BACKLIGHT_ENABLE = yes # using feature_backlight for the backlight of the LED screen
# BACKLIGHT_DRIVER = pwm

# for changing what shift does to a key
KEY_OVERRIDE_ENABLE = yes

# for the big oled display
# QUANTUM_PAINTER_ENABLE = yes
# QUANTUM_PAINTER_DRIVERS = ili9341_spi

# master slave user sync
SRC += transport.c
# big LED display
# SRC += ili9341_display.c
# small oled display
SRC += oled_display.c
# rgb matrix
# SRC += rgb_matrix_user.c
# painter images
