#pragma once

enum custom_layers {
    _DVORAK,
    _LOWER,
    _RAISE,
};

#define RAISE MO(_RAISE)
#define LOWER MO(_LOWER)

bool get_idle_mode(void);
bool get_fake_mode(void);

void set_idle_mode(bool toset);
void set_fake_mode(bool toset);

#define MIN_WALK_SPEED 5
#define MIN_RUN_SPEED 50
