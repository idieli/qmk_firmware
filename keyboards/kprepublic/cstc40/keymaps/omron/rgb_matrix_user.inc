RGB_MATRIX_EFFECT(BASE_RGB)
RGB_MATRIX_EFFECT(SYMB_RGB)
RGB_MATRIX_EFFECT(MEDIA_RGB)
RGB_MATRIX_EFFECT(NUM_RGB)
RGB_MATRIX_EFFECT(NAV_RGB)
RGB_MATRIX_EFFECT(FN_RGB)
RGB_MATRIX_EFFECT(MIDI_RGB)

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

static bool BASE_RGB(effect_params_t* params) {
  RGB_MATRIX_USE_LIMITS(led_min, led_max);
  rgb_matrix_set_color_all(RGB_OFF);
  return rgb_matrix_check_finished_leds(led_max);
}

static bool SYMB_RGB(effect_params_t* params) {
  RGB_MATRIX_USE_LIMITS(led_min, led_max);
  rgb_matrix_set_color_all(RGB_OFF);
  //rgb_matrix_set_color(22, RGB_RED);
  rgb_matrix_set_color(22, 205, 130, 130);
  return rgb_matrix_check_finished_leds(led_max);
}

static bool MEDIA_RGB(effect_params_t* params) {
  RGB_MATRIX_USE_LIMITS(led_min, led_max);
  rgb_matrix_set_color_all(RGB_OFF);
  rgb_matrix_set_color(36, RGB_RED);
  return rgb_matrix_check_finished_leds(led_max);
}

static bool NUM_RGB(effect_params_t* params) {
  RGB_MATRIX_USE_LIMITS(led_min, led_max);
  rgb_matrix_set_color_all(RGB_OFF);
  rgb_matrix_set_color(40, RGB_RED);
  return rgb_matrix_check_finished_leds(led_max);
}

static bool NAV_RGB(effect_params_t* params) {
  RGB_MATRIX_USE_LIMITS(led_min, led_max);
  rgb_matrix_set_color_all(RGB_OFF);
  rgb_matrix_set_color(42, RGB_RED);
  return rgb_matrix_check_finished_leds(led_max);
}

static bool FN_RGB(effect_params_t* params) {
  RGB_MATRIX_USE_LIMITS(led_min, led_max);
  rgb_matrix_set_color_all(RGB_OFF);
  rgb_matrix_set_color(46, RGB_RED);
  return rgb_matrix_check_finished_leds(led_max);
}

static bool MIDI_RGB(effect_params_t* params) {
  RGB_MATRIX_USE_LIMITS(led_min, led_max);
  rgb_matrix_set_color_all(RGB_OFF);
  for (uint8_t i = 1; i < 7; i++) {
    rgb_matrix_set_color(i, RGB_RED);
  }
  for (uint8_t i = 7; i < 11; i++) {
    rgb_matrix_set_color(i, RGB_GREEN);
  }
  for (uint8_t i = 13; i < 20; i++) {
    rgb_matrix_set_color(i, RGB_PINK);
  }
  for (uint8_t i = 20; i < 23; i++) {
    rgb_matrix_set_color(i, RGB_RED);
  }
  for (uint8_t i = 25; i < 32; i++) {
    rgb_matrix_set_color(i, RGB_PURPLE);
  }
  for (uint8_t i = 32; i < 35; i++) {
    rgb_matrix_set_color(i, RGB_PINK);
  }
  return rgb_matrix_check_finished_leds(led_max);
}

#endif
