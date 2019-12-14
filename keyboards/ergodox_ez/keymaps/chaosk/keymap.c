#include QMK_KEYBOARD_H
#include "version.h"
#include "custom_keycodes.h"
#include "tap_hold_expire.h"
#include "tap_dance.h"
#include "dances/escape.c"
#include "dances/modals.c"

#define BASE 0 // default layer
#define SYMB 1 // symbols
#define MDIA 2 // media keys

enum {
    ACTIVATE_GLYPH = KC_J,
    ACTIVATE_SCAN = KC_P,
    LEARN_ABILITY = KC_O,
    UPGRADE_TALENTS = KC_U,
    SELECT_COURIER = KC_F2,
    DELIVER_ITEMS = KC_F3,
    OPEN_SHOP = KC_F4,
    PURCHASE_QUICKBUY = KC_F5,
    PURCHASE_STICKY = KC_F6,
    PUSH_TO_TALK = KC_F13,
    TAKE_STASH_ITEMS = KC_F14,
    PHRASE_WELL_PLAYED = KC_F15,
    COURIER_BURST = KC_F16,
    COURIER_SHIELD = KC_F17,
    TOWN_PORTAL_SCROLL = KC_F18,
    ITEM_2 = KC_F19,
};

enum {
    TH_COURIER_ITEMS,
    TH_SHOP,
    TH_PURCHASE,
    TH_COURIER_ABILITIES,
    TH_LEVEL_UP,
};

enum {
    TD_ESCAPE_SCOREBOARD_PAUSE = 0,
    TD_DOTAPLUS_DEATHSUMMARY_CONSOLE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * | TD_SCOR|   1  |   2  |THCOUR|THSHOP|THPURC|TDMODL|           | RIGHT|   6  |   7  |   8  |   9  |   0  |   -    |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | Tab    |   Q  |   W  |   E  |   R  |   T  |  L1  |           |  L1  |   Y  |   U  |   I  |   O  |   P  |   \    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | PTT    |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |; / L2|' / Cmd |
 * |--------+------+------+------+------+------|THCOUR|           | Meh  |------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   V  |   B  |DEFENC|           |      |   N  |   M  |   ,  |   .  |//Ctrl| RShift |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |Ctrl  |  '"  |Alt   |TPSCRL|ITEM_2|                                       |  Up  | Down |   [  |   ]  | ~L1  |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |WP!   |THLVLU|       | Alt  |Ctrl/Esc|
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      |GLYPH |       | PgUp |        |      |
 *                                 | Space|Backsp|------|       |------|  Tab   |Enter |
 *                                 |      |ace   |SCAN  |       | PgDn |        |      |
 *                                 `--------------------'       `----------------------'
 */
[BASE] = LAYOUT_ergodox(
    // left hand
    TD(TD_ESCAPE_SCOREBOARD_PAUSE),          KC_1,        KC_2,          TH(TH_COURIER_ITEMS),    TH(TH_SHOP),    TH(TH_PURCHASE),    TD(TD_DOTAPLUS_DEATHSUMMARY_CONSOLE),
    KC_TAB,          KC_Q,        KC_W,          KC_E,    KC_R,    KC_T,    OSL(SYMB),
    PUSH_TO_TALK,         KC_A,        KC_S,          KC_D,    KC_F,    KC_G,
    KC_LSFT,         KC_Z, KC_X,          KC_C,    KC_V,    KC_B,    TH(TH_COURIER_ABILITIES),
    KC_LCTRL, KC_QUOT,     KC_LALT, TOWN_PORTAL_SCROLL, ITEM_2,
                                                                                                                     PHRASE_WELL_PLAYED, TH(TH_LEVEL_UP),
                                                                                                                                                    ACTIVATE_SCAN,
                                                                                                                 KC_SPC, KC_BSPC, ACTIVATE_GLYPH,
    // right hand
    KC_RGHT,      KC_6,    KC_7,    KC_8,    KC_9,              KC_0,           KC_MINS,
    TG(SYMB),     KC_Y,    KC_U,    KC_I,    KC_O,              KC_P,           KC_BSLS,
    KC_H,         KC_J,    KC_K,    KC_L,    LT(MDIA, KC_SCLN), GUI_T(KC_QUOT),
    MEH_T(KC_NO), KC_N,    KC_M,    KC_COMM, KC_DOT,            CTL_T(KC_SLSH), KC_RSFT,
    KC_UP,        KC_DOWN, KC_LBRC, KC_RBRC, TT(SYMB),
    KC_LALT, CTL_T(KC_ESC),
    KC_PGUP,
    KC_PGDN, KC_TAB, KC_ENT
),
/* Keymap 1: Symbol Layer
 *
 * ,---------------------------------------------------.           ,--------------------------------------------------.
 * |Version  |XXXXXX|XXXXXX|XXXXXX|XXXXXX|XXXXXX|XXXXXX|           |      |  F6  |  F7  |  F8  |  F9  |  F10 |   F11  |
 * |---------+------+------+------+------+------+------|           |------+------+------+------+------+------+--------|
 * |XXXXXX   |XXXXXX|XXXXXX|XXXXXX|XXXXXX|XXXXXX|      |           |      |   Up |   7  |   8  |   9  |   *  |   F12  |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |XXXXXX   |XXXXXX|XXXXXX|XXXXXX|XXXXXX|XXXXXX|------|           |------| Down |   4  |   5  |   6  |   +  |        |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |XXXXXX   |XXXXXX|XXXXXX|XXXXXX|XXXXXX|XXXXXX|      |           |      |   &  |   1  |   2  |   3  |   \  |        |
 * `---------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |       |      |      |      |      |                                       |      |    . |   0  |   =  |      |
 *   `-----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |XXXXXX| RESET|       |Toggle|Solid |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |Enter |XXXXXX|XXXXXX|       |      |Hue-  |Hue+  |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |XXXXXX|       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
[SYMB] = LAYOUT_ergodox(
    // left hand
    VRSN,    XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX, KC_TRNS,
    XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_TRNS,
    KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                                                                             XXXXXXX, RESET,
                                                                                                                XXXXXXX,
                                                                            KC_ENTER, KC_ENTER, XXXXXXX,
    // right hand
    KC_TRNS, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
    KC_TRNS, KC_UP,   KC_7,    KC_8,    KC_9,    KC_ASTR, KC_F12,
    KC_DOWN, KC_4,    KC_5,    KC_6,    KC_PLUS, KC_TRNS,
    KC_TRNS, KC_AMPR, KC_1,    KC_2,    KC_3,    KC_BSLS, KC_TRNS,
    KC_TRNS, KC_DOT,  KC_0,    KC_EQL,  KC_TRNS,
    KC_TRNS, KC_TRNS,
    KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS
),
/* Keymap 2: Media and mouse keys
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      | MsUp |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |MsLeft|MsDown|MsRght|      |------|           |------|      |      |      |      |      |  Play  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      | Prev | Next |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      | Lclk | Rclk |                                       |VolUp |VolDn | Mute |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |Brwser|
 *                                 |      |      |------|       |------|      |Back  |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
[MDIA] = LAYOUT_ergodox(
    // left hand
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_MS_U, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_MS_L, KC_MS_D, KC_MS_R, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_BTN1, KC_BTN2,
                                                                                             KC_TRNS, KC_TRNS,
                                                                                                                KC_TRNS,
                                                                            KC_TRNS, KC_TRNS, KC_TRNS,
    // right hand
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MPLY,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_MPRV, KC_MNXT, KC_TRNS, KC_TRNS,
                                        KC_VOLU, KC_VOLD, KC_MUTE, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS,
    KC_TRNS,
    KC_TRNS, KC_TRNS, KC_WBAK
),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!(process_tap_hold_expire(keycode, record))) {
        return false;
    }
    if (record->event.pressed) {
        switch (keycode) {
            case VRSN:
                SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
                return false;
        }
    }
    return true;
}

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
    // Swap hands, so that our left-hand master actually uses left side of the layout.
    swap_hands = true;

#ifdef RGBLIGHT_COLOR_LAYER_0
    rgblight_setrgb(RGBLIGHT_COLOR_LAYER_0);
#endif
};

void matrix_scan_user(void) {
    matrix_scan_tap_hold_expire();
}

// Runs whenever there is a layer state change.
layer_state_t layer_state_set_user(layer_state_t state) {
    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();

    uint8_t layer = get_highest_layer(state);
    switch (layer) {
            case 0:
                #ifdef RGBLIGHT_COLOR_LAYER_0
                    rgblight_setrgb(RGBLIGHT_COLOR_LAYER_0);
                #else
                #ifdef RGBLIGHT_ENABLE
                    rgblight_init();
                #endif
                #endif
                break;
            case 1:
                ergodox_right_led_1_on();
                #ifdef RGBLIGHT_COLOR_LAYER_1
                    rgblight_setrgb(RGBLIGHT_COLOR_LAYER_1);
                #endif
                break;
            case 2:
                ergodox_right_led_2_on();
                #ifdef RGBLIGHT_COLOR_LAYER_2
                    rgblight_setrgb(RGBLIGHT_COLOR_LAYER_2);
                #endif
                break;
            case 3:
                ergodox_right_led_3_on();
                #ifdef RGBLIGHT_COLOR_LAYER_3
                    rgblight_setrgb(RGBLIGHT_COLOR_LAYER_3);
                #endif
                break;
            case 4:
                ergodox_right_led_1_on();
                ergodox_right_led_2_on();
                #ifdef RGBLIGHT_COLOR_LAYER_4
                    rgblight_setrgb(RGBLIGHT_COLOR_LAYER_4);
                #endif
                break;
            case 5:
                ergodox_right_led_1_on();
                ergodox_right_led_3_on();
                #ifdef RGBLIGHT_COLOR_LAYER_5
                    rgblight_setrgb(RGBLIGHT_COLOR_LAYER_5);
                #endif
                break;
            case 6:
                ergodox_right_led_2_on();
                ergodox_right_led_3_on();
                #ifdef RGBLIGHT_COLOR_LAYER_6
                    rgblight_setrgb(RGBLIGHT_COLOR_LAYER_6);
                #endif
                break;
            case 7:
                ergodox_right_led_1_on();
                ergodox_right_led_2_on();
                ergodox_right_led_3_on();
                #ifdef RGBLIGHT_COLOR_LAYER_7
                    rgblight_setrgb(RGBLIGHT_COLOR_LAYER_7);
                #endif
                break;
            default:
                break;
        }

    return state;
};

qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_ESCAPE_SCOREBOARD_PAUSE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, escape_finished, escape_reset),
    [TD_DOTAPLUS_DEATHSUMMARY_CONSOLE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, modals_finished, modals_reset),
};

tap_hold_expire_action_t tap_hold_expire_actions[] = {
    [TH_COURIER_ITEMS] = ACTION_TAP_HOLD_EXPIRE(SELECT_COURIER, DELIVER_ITEMS),
    [TH_SHOP] = ACTION_TAP_HOLD_EXPIRE(OPEN_SHOP, TAKE_STASH_ITEMS),
    [TH_PURCHASE] = ACTION_TAP_HOLD_EXPIRE(PURCHASE_QUICKBUY, PURCHASE_STICKY),
    [TH_COURIER_ABILITIES] = ACTION_TAP_HOLD_EXPIRE(COURIER_SHIELD, COURIER_BURST),
    [TH_LEVEL_UP] = ACTION_TAP_HOLD_EXPIRE(LEARN_ABILITY, UPGRADE_TALENTS),
};
