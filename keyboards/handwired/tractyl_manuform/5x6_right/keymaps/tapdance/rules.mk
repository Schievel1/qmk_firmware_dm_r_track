LTO_ENABLE = yes
TAP_DANCE_ENABLE = no
CONSOLE_ENABLE = no
# for changing what shift does to a key
KEY_OVERRIDE_ENABLE = yes

EXTRAFLAGS += -flto -mcall-prologues
