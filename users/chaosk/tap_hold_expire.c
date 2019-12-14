/* Provides tap-hold-expire functionality.
 *
 * When THE key is tapped, a keycode is sent upon release.
 * When THE key is held, a different keycode is sent
 * when the press duration reaches TAPPING_TERM (and not upon release).
 */
#include "tap_hold_expire.h"
#include "custom_keycodes.h"

bool tap_hold_active = false;
uint16_t tap_hold_hold_code;
uint16_t tap_hold_timer = 0;

void process_tap_hold_expire_action(uint16_t tap_keycode, uint16_t hold_keycode, bool pressed) {
    if(pressed) {
        tap_hold_timer = timer_read();
        if (tap_hold_hold_code != hold_keycode) {
            tap_hold_hold_code = hold_keycode;
            tap_hold_active = true;
        }
    } else {
        if (timer_elapsed(tap_hold_timer) < TAPPING_TERM){
            tap_code16(tap_keycode);
        } else if (tap_hold_active) {
            tap_code16(hold_keycode);
        }
        tap_hold_hold_code = 0;
        tap_hold_active = false;
    }
};

bool process_tap_hold_expire(uint16_t keycode, keyrecord_t *record) {
    uint16_t idx = keycode - QK_TAP_HOLD_EXPIRE;
    tap_hold_expire_action_t *action;

    switch (keycode) {
        case QK_TAP_HOLD_EXPIRE ... QK_TAP_HOLD_EXPIRE_MAX:
            action = &tap_hold_expire_actions[idx];
            process_tap_hold_expire_action(action->tap_keycode, action->hold_keycode, record->event.pressed);
            return false;
    };
    return true;
};

void matrix_scan_tap_hold_expire(void) {
    if (tap_hold_active) {
        if (timer_elapsed(tap_hold_timer) > TAPPING_TERM && tap_hold_hold_code) {
            tap_code16(tap_hold_hold_code);
            tap_hold_active = false;
        }
    }
};