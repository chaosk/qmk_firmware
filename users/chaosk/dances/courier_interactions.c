
static tap courier_interactions_state = {
    .is_press_action = true,
    .state           = 0
};


void courier_interactions_finished(qk_tap_dance_state_t *state, void *user_data) {
    courier_interactions_state.state = current_dance(state);
    switch (courier_interactions_state.state) {
        case SINGLE_TAP:
            register_code(KC_F2);
            break;
        case SINGLE_HOLD:
            register_code(KC_F3);
            break;
    }
}

void courier_interactions_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (courier_interactions_state.state) {
        case SINGLE_TAP:
            unregister_code(KC_F2);
            break;
        case SINGLE_HOLD:
            unregister_code(KC_F3);
            break;
    }
    courier_interactions_state.state = 0;
}
