RGB_MATRIX_EFFECT(ALL_OFF_RGB)
RGB_MATRIX_EFFECT(BASE_RGB)
RGB_MATRIX_EFFECT(SYMB_RGB)
RGB_MATRIX_EFFECT(MEDIA_RGB)
RGB_MATRIX_EFFECT(NUM_RGB)
RGB_MATRIX_EFFECT(NAV_RGB)
RGB_MATRIX_EFFECT(FN_RGB)
RGB_MATRIX_EFFECT(GAME_RGB)
RGB_MATRIX_EFFECT(MIDI_RGB)
RGB_MATRIX_EFFECT(MIDI_SCALES_RGB)
RGB_MATRIX_EFFECT(SET_CAPS_RGB)
RGB_MATRIX_EFFECT(UNSET_CAPS_RGB)
RGB_MATRIX_EFFECT(SET_MACRO_RGB)
RGB_MATRIX_EFFECT(UNSET_MACRO_RGB)
RGB_MATRIX_EFFECT(SET_LEADER_RGB)
RGB_MATRIX_EFFECT(SET_LEADER_ACCEPTED_RGB)
RGB_MATRIX_EFFECT(SET_LEADER_REJECTED_RGB)
RGB_MATRIX_EFFECT(UNSET_LEADER_RGB)

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

static bool ALL_OFF_RGB(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    rgb_matrix_set_color_all(RGB_OFF);
    return rgb_matrix_check_finished_leds(led_max);
}

static bool BASE_RGB(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    for (uint8_t i = led_min; i < led_max; i++) {
	if (i != 12 && i != 23 && i != 37 && i != 45) {
            rgb_matrix_set_color(i, RGB_OFF);
        }
    }
    return rgb_matrix_check_finished_leds(led_max);
}

static bool SYMB_RGB(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    rgb_matrix_set_color(22, RGB_RED);
    return rgb_matrix_check_finished_leds(led_max);
}

static bool MEDIA_RGB(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    rgb_matrix_set_color(36, RGB_ORANGE);
    return rgb_matrix_check_finished_leds(led_max);
}

static bool NUM_RGB(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    rgb_matrix_set_color(40, RGB_YELLOW);
    return rgb_matrix_check_finished_leds(led_max);
}

static bool NAV_RGB(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    rgb_matrix_set_color(42, RGB_GREEN);
    return rgb_matrix_check_finished_leds(led_max);
}

static bool FN_RGB(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    rgb_matrix_set_color(20, RGB_BLUE);
    rgb_matrix_set_color(46, RGB_BLUE);
    return rgb_matrix_check_finished_leds(led_max);
}

static bool GAME_RGB(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    rgb_matrix_set_color_all(RGB_OFF);
    rgb_matrix_set_color(16, RGB_RED);
    rgb_matrix_set_color(17, RGB_RED);
    rgb_matrix_set_color(18, RGB_RED);
    rgb_matrix_set_color(19, RGB_RED);
    return rgb_matrix_check_finished_leds(led_max);
}

static bool MIDI_RGB(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    rgb_matrix_set_color_all(RGB_OFF);
    rgb_matrix_set_color(1, RGB_RED);
    rgb_matrix_set_color(15, RGB_ORANGE);
    rgb_matrix_set_color(30, RGB_YELLOW);
    rgb_matrix_set_color(20, RGB_GREEN);
    rgb_matrix_set_color(10, RGB_BLUE);
    return rgb_matrix_check_finished_leds(led_max);
}

static bool MIDI_SCALES_RGB(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    rgb_matrix_set_color_all(RGB_OFF);
    for (uint8_t i = 0; i < 3; i++) {
      rgb_matrix_set_color(2+(12*i), RGB_RED);
      rgb_matrix_set_color(3+(12*i), RGB_ORANGE);
      rgb_matrix_set_color(4+(12*i), RGB_YELLOW);
      rgb_matrix_set_color(5+(12*i), RGB_GREEN);
      rgb_matrix_set_color(6+(12*i), RGB_BLUE);
      rgb_matrix_set_color(7+(12*i), RGB_PURPLE);
      rgb_matrix_set_color(8+(12*i), RGB_PINK);
      rgb_matrix_set_color(9+(12*i), RGB_RED);
  
    }
    return rgb_matrix_check_finished_leds(led_max);
}

static bool SET_CAPS_RGB(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    rgb_matrix_set_color(12, RGB_WHITE);
    rgb_matrix_set_color(23, RGB_WHITE);
    return rgb_matrix_check_finished_leds(led_max);
}

static bool UNSET_CAPS_RGB(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    rgb_matrix_set_color(12, RGB_OFF);
    rgb_matrix_set_color(23, RGB_OFF);
    return rgb_matrix_check_finished_leds(led_max);
}

static bool SET_MACRO_RGB(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    rgb_matrix_set_color(37, RGB_WHITE);
    return rgb_matrix_check_finished_leds(led_max);
}

static bool UNSET_MACRO_RGB(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    rgb_matrix_set_color(37, RGB_OFF);
    return rgb_matrix_check_finished_leds(led_max);
}

static bool SET_LEADER_RGB(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    rgb_matrix_set_color(45, RGB_WHITE);
    return rgb_matrix_check_finished_leds(led_max);
}

static bool SET_LEADER_ACCEPTED_RGB(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    rgb_matrix_set_color(45, RGB_GREEN);
    return rgb_matrix_check_finished_leds(led_max);
}

static bool SET_LEADER_REJECTED_RGB(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    rgb_matrix_set_color(45, RGB_RED);
    return rgb_matrix_check_finished_leds(led_max);
}

static bool UNSET_LEADER_RGB(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    rgb_matrix_set_color(45, RGB_OFF);
    return rgb_matrix_check_finished_leds(led_max);
}

#endif
