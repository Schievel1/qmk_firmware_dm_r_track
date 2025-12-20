#include QMK_KEYBOARD_H
#include "transactions.h"
#include "debug.h"

#include "transport.h"
#include "keymap.h"
#include "oled_display.h"

/*****************************************************/
/*  T r a n s p o r t   s t a t e   t o   s l a v e  */
/*****************************************************/

void user_sync_init() {
    transaction_register_rpc(USER_SYNC_A, user_sync_a_slave_handler);
}

void user_sync_a_slave_handler(uint8_t in_buflen, const void* in_data, uint8_t out_buflen, void* out_data) {
    const master_to_slave_t* m2s = (const master_to_slave_t*)in_data;
    slave_to_master_t*       s2m = (slave_to_master_t*)out_data;

    if (get_idle_mode() != m2s->current_idle_state) {
        set_idle_mode(m2s->current_idle_state);
    }
    if (get_fake_mode() != m2s->current_fake_state) {
        set_fake_mode(m2s->current_fake_state);
    }
	if (get_jumping() != m2s->current_jumping_state) {
		set_jumping(m2s->current_jumping_state);
	}
    if (get_sneaking() != m2s->current_sneaking_state) {
        set_sneaking(m2s->current_sneaking_state);
    }
    if (debug_config.raw != m2s->debug_config.raw) {
        debug_config.raw = m2s->debug_config.raw;
    }
    // just mirror it back for debug purposes
    s2m->current_idle_state  = m2s->current_idle_state;
    s2m->current_fake_state  = m2s->current_fake_state;
    s2m->current_jumping_state = m2s->current_jumping_state;
    s2m->current_sneaking_state = m2s->current_sneaking_state;
    s2m->debug_config.raw = m2s->debug_config.raw;
}

void master_slave_com() {
    if (is_keyboard_master()) {
        static uint32_t last_sync = 0;
        if (timer_elapsed32(last_sync) > USER_COM_POLL_TIME_MS) {
            /* dprintf("current layer state: %d\n", layer_state); */
            master_to_slave_t m2s = {
                .current_idle_state    = get_idle_mode(),
                .current_fake_state    = get_fake_mode(),
                .current_jumping_state = get_jumping(),
                .current_sneaking_state = get_sneaking(),
                .debug_config.raw      = debug_config.raw,
            };
            slave_to_master_t s2m = {0};
            if (transaction_rpc_exec(USER_SYNC_A, sizeof(m2s), &m2s, sizeof(s2m), &s2m)) {
                last_sync = timer_read32();
                dprintf("Slave current idle value: %d\n", s2m.current_idle_state);
                dprintf("Slave current fake value: %d\n", s2m.current_fake_state);
                dprintf("Slave current debug value: %d\n", s2m.debug_config.raw);
                dprintf("Slave current jumping value: %d\n", s2m.current_jumping_state);
                dprintf("Slave current sneaking value: %d\n", s2m.current_sneaking_state);
            } else {
                dprint("Slave sync failed!\n");
            }
        }
    }
}
