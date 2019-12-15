#include QMK_KEYBOARD_H
#include "version.h"
#include "custom_keycodes.h"
#include "tap_hold_expire.h"
#include "tap_dance.h"
#include "dances/escape.c"
#include "dances/modals.c"

#define BASE 0  // default layer
#define SYMB 1  // symbols
#define MDIA 2  // media keys

#define LAYOUT_ergodox_left_only(...) LAYOUT_ergodox(__VA_ARGS__, \
    XXXXXXX, \
    XXXXXXX,XXXXXXX, \
    XXXXXXX,XXXXXXX,XXXXXXX, \
    XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX, \
    XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX, \
    XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX, \
    XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX, \
    XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX, \
    XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX, \
    XXXXXXX,XXXXXXX,XXXXXXX, \
    XXXXXXX,XXXXXXX, \
    XXXXXXX \
)

enum {
    ACTIVATE_GLYPH     = KC_J,
    ACTIVATE_SCAN      = KC_P,
    LEARN_ABILITY      = KC_O,
    UPGRADE_TALENTS    = KC_U,
    SELECT_COURIER     = KC_F2,
    DELIVER_ITEMS      = KC_F3,
    OPEN_SHOP          = KC_F4,
    PURCHASE_QUICKBUY  = KC_F5,
    PURCHASE_STICKY    = KC_F6,
    PUSH_TO_TALK       = KC_F13,
    TAKE_STASH_ITEMS   = KC_F14,
    PHRASE_WP = KC_F15,
    COURIER_BURST      = KC_F16,
    COURIER_SHIELD     = KC_F17,
    TP_SCROLL = KC_F18,
    ITEM_2             = KC_F19,
};

enum {
    TH_C_ITEMS,  // Courier item management
    TH_SHOP,
    TH_PURCHASE,
    TH_C_ABILITIES,  // Courier abilities
    TH_LEVEL_UP,
};

enum {
    TD_ESCAPE = 0,
    TD_MODALS,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Keymap 0: Basic layer
     *
     * ,--------------------------------------------------.
     * | Escape |   1  |   2  |C Item| Shop |Purcha|Modals|
     * |--------+------+------+------+------+-------------|
     * | Tab    |   Q  |   W  |   E  |   R  |   T  |  L1  |
     * |--------+------+------+------+------+------|1 Shot|
     * | PTT    |   A  |   S  |   D  |   F  |   G  |------|
     * |--------+------+------+------+------+------|Courie|
     * | LShift |   Z  |   X  |   C  |   V  |   B  |Abilit|
     * `--------+------+------+------+------+-------------'
     *   |LCtrl |  '"  | Alt  |TPScro|ITEM_2|
     *   `----------------------------------'
     *                                        ,-------------.
     *                                        | WP!  |LvlUp |
     *                                 ,------|------|------|
     *                                 |      |      |Glyph |
     *                                 | Space|Backsp|------|
     *                                 |      |ace   |Scan  |
     *                                 `--------------------'
     */
    [BASE] = LAYOUT_ergodox_left_only(
        TD(TD_ESCAPE),  KC_1,       KC_2,       TH(TH_C_ITEMS), TH(TH_SHOP),    TH(TH_PURCHASE),    TD(TD_MODALS),
        KC_TAB,         KC_Q,       KC_W,       KC_E,           KC_R,           KC_T,               OSL(SYMB),
        PUSH_TO_TALK,   KC_A,       KC_S,       KC_D,           KC_F,           KC_G,
        KC_LSFT,        KC_Z,       KC_X,       KC_C,           KC_V,           KC_B,               TH(TH_C_ABILITIES),
        KC_LCTRL,       KC_QUOT,    KC_LALT,    TP_SCROLL,      ITEM_2,

                                                                                PHRASE_WP,          TH(TH_LEVEL_UP),
                                                                                                    ACTIVATE_SCAN,
                                                                KC_SPC,         KC_BSPC,            ACTIVATE_GLYPH
    ),
    /* Keymap 1: Symbol Layer
     *
     * ,---------------------------------------------------.
     * |Version  |XXXXXX|XXXXXX|XXXXXX|XXXXXX|XXXXXX|XXXXXX|
     * |---------+------+------+------+------+------+------|
     * |XXXXXX   |XXXXXX|XXXXXX|XXXXXX|XXXXXX|XXXXXX|      |
     * |---------+------+------+------+------+------|      |
     * |XXXXXX   |XXXXXX|XXXXXX|XXXXXX|XXXXXX|XXXXXX|------|
     * |---------+------+------+------+------+------|      |
     * |XXXXXX   |XXXXXX|XXXXXX|XXXXXX|XXXXXX|XXXXXX|      |
     * `---------+------+------+------+------+-------------'
     *   |       |      |      |      |      |
     *   `-----------------------------------'
     *                                        ,-------------.
     *                                        |XXXXXX| RESET|
     *                                 ,------|------|------|
     *                                 |Enter |XXXXXX|XXXXXX|
     *                                 |      |      |------|
     *                                 |      |      |XXXXXX|
     *                                 `--------------------'
     */
    [SYMB] = LAYOUT_ergodox_left_only(
        VRSN,       XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,
        XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    KC_TRNS,
        XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,
        XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    KC_TRNS,
        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    

                                                                    XXXXXXX,    RESET,
                                                                                XXXXXXX,
                                                        KC_ENTER,   XXXXXXX,    XXXXXXX
    ),
    /* Keymap 2: Media keys
     *
     * ,--------------------------------------------------.
     * |        |      |      |      |      |      |      |
     * |--------+------+------+------+------+-------------|
     * |        |      |      |      |      |      |      |
     * |--------+------+------+------+------+------|      |
     * |  Play  |      |      |      |      |      |------|
     * |--------+------+------+------+------+------|      |
     * |        |      |      |      |      |      |      |
     * `--------+------+------+------+------+-------------'
     *   |      |      |      |      |      |
     *   `----------------------------------'
     *                                        ,-------------.
     *                                        |      |      |
     *                                 ,------|------|------|
     *                                 |      |      |      |
     *                                 |      |      |------|
     *                                 |      |      |      |
     *                                 `--------------------'
     */
    [MDIA] = LAYOUT_ergodox_left_only(
        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
        KC_MPLY,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    

                                                                    KC_TRNS,    KC_TRNS,
                                                                                KC_TRNS,
                                                        KC_TRNS,    KC_TRNS,    KC_TRNS
    ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!(process_tap_hold_expire(keycode, record))) {
        return false;
    }
    if (record->event.pressed) {
        switch (keycode) {
            case VRSN:
                SEND_STRING(QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
                return false;
        }
    }
    return true;
}

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
    // Swap hands, so that our left-hand master actually uses left side of the layout.
    swap_hands = true;
};

void matrix_scan_user(void) { matrix_scan_tap_hold_expire(); }

// Runs whenever there is a layer state change.
layer_state_t layer_state_set_user(layer_state_t state) {
    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();

    uint8_t layer = get_highest_layer(state);
    switch (layer) {
        case 0:
            break;
        case 1:
            ergodox_right_led_1_on();
            break;
        case 2:
            ergodox_right_led_2_on();
            break;
        case 3:
            ergodox_right_led_3_on();
            break;
        case 4:
            ergodox_right_led_1_on();
            ergodox_right_led_2_on();
            break;
        case 5:
            ergodox_right_led_1_on();
            ergodox_right_led_3_on();
            break;
        case 6:
            ergodox_right_led_2_on();
            ergodox_right_led_3_on();
            break;
        case 7:
            ergodox_right_led_1_on();
            ergodox_right_led_2_on();
            ergodox_right_led_3_on();
            break;
        default:
            break;
    }

    return state;
};

qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_ESCAPE]       = ACTION_TAP_DANCE_FN_ADVANCED(NULL, escape_finished, escape_reset),
    [TD_MODALS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, modals_finished, modals_reset),
};

tap_hold_expire_action_t tap_hold_expire_actions[] = {
    [TH_C_ITEMS] = ACTION_TAP_HOLD_EXPIRE(SELECT_COURIER, DELIVER_ITEMS),
    [TH_SHOP] = ACTION_TAP_HOLD_EXPIRE(OPEN_SHOP, TAKE_STASH_ITEMS),
    [TH_PURCHASE] = ACTION_TAP_HOLD_EXPIRE(PURCHASE_QUICKBUY, PURCHASE_STICKY),
    [TH_C_ABILITIES] = ACTION_TAP_HOLD_EXPIRE(COURIER_SHIELD, COURIER_BURST),
    [TH_LEVEL_UP] = ACTION_TAP_HOLD_EXPIRE(LEARN_ABILITY, UPGRADE_TALENTS),
};
