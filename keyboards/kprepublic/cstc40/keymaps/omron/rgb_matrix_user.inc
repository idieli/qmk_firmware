RGB_MATRIX_EFFECT(BASE_RGB)
RGB_MATRIX_EFFECT(SYMB_RGB)
RGB_MATRIX_EFFECT(MEDIA_RGB)
RGB_MATRIX_EFFECT(NUM_RGB)
RGB_MATRIX_EFFECT(NAV_RGB)
RGB_MATRIX_EFFECT(FN_RGB)
RGB_MATRIX_EFFECT(MIDI_RGB)
RGB_MATRIX_EFFECT(SET_CAPS_RGB)
RGB_MATRIX_EFFECT(UNSET_CAPS_RGB)

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

void skip_shifts(int key_min, int key_max, int *keys_to_color, int num_keys_to_color, uint8_t red, uint8_t green, uint8_t blue) {
    for (uint8_t i = key_min; i < key_max; i++) {
	if (i != 12 && i != 23) {
            rgb_matrix_set_color(i, RGB_OFF);
        }
    }
    for (uint8_t i = 0; i < num_keys_to_color; i++) {
        rgb_matrix_set_color(keys_to_color[i], red, green, blue);
    }
}

static bool BASE_RGB(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    /*
    for (uint8_t i = led_min; i < led_max; i++) {
        if (i != 12 && i != 23) {
            rgb_matrix_set_color_all(RGB_OFF);
        }
    }
    */
    int keys[] = {};
    skip_shifts(led_min, led_max, keys, 0, RGB_OFF);
    return rgb_matrix_check_finished_leds(led_max);
}

static bool SYMB_RGB(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    /*
    for (uint8_t i = led_min; i < led_max; i++) {
	if (i == 22) {
            rgb_matrix_set_color(i, RGB_RED);
	}
	else if (i != 12 && i != 23) {
            rgb_matrix_set_color(RGB_OFF);
        }
    }
	*/
    int keys[] = {22};
    skip_shifts(led_min, led_max, keys, 1, RGB_RED);
    return rgb_matrix_check_finished_leds(led_max);
}

static bool MEDIA_RGB(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    /*
    for (uint8_t i = led_min; i < led_max; i++) {
	if (i == 36) {
            rgb_matrix_set_color(i, RGB_ORANGE);
	}
	else if (i != 12 && i != 23) {
            rgb_matrix_set_color(RGB_OFF);
        }
    }
	*/
    int keys[] = {36};
    skip_shifts(led_min, led_max, keys, 1, RGB_ORANGE);
    return rgb_matrix_check_finished_leds(led_max);
}

static bool NUM_RGB(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    /*
    for (uint8_t i = led_min; i < led_max; i++) {
	if (i == 40) {
            rgb_matrix_set_color(i, RGB_YELLOW);
	}
	else if (i != 12 && i != 23) {
            rgb_matrix_set_color(RGB_OFF);
        }
    }
	*/
    int keys[] = {40};
    skip_shifts(led_min, led_max, keys, 1, RGB_YELLOW);
    return rgb_matrix_check_finished_leds(led_max);
}

static bool NAV_RGB(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    /*
    for (uint8_t i = led_min; i < led_max; i++) {
	if (i == 42) {
            rgb_matrix_set_color(i, RGB_RED);
	}
	else if (i != 12 && i != 23) {
            rgb_matrix_set_color_all(RGB_OFF);
        }
    }
	*/
    int keys[] = {42};
    skip_shifts(led_min, led_max, keys, 1, RGB_GREEN);
    return rgb_matrix_check_finished_leds(led_max);
}

static bool FN_RGB(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    /*
    for (uint8_t i = led_min; i < led_max; i++) {
	if (i == 20 || i == 46) {
            rgb_matrix_set_color(i, RGB_RED);
	}
	else if (i != 12 && i != 23) {
            rgb_matrix_set_color_all(RGB_OFF);
        }
    }
	*/
    int keys[] = {20,46};
    skip_shifts(led_min, led_max, keys, 2, RGB_BLUE);
    return rgb_matrix_check_finished_leds(led_max);
}

static bool MIDI_RGB(effect_params_t* params) {
  RGB_MATRIX_USE_LIMITS(led_min, led_max);
  rgb_matrix_set_color_all(RGB_OFF);
  for (uint8_t i = 0; i < 3; i++) {
    rgb_matrix_set_color(1+(12*i), RGB_RED);
    rgb_matrix_set_color(8+(12*i), RGB_RED);

    rgb_matrix_set_color(2+(12*i), RGB_ORANGE);
    rgb_matrix_set_color(9+(12*i), RGB_ORANGE);

    rgb_matrix_set_color(3+(12*i), RGB_YELLOW);
    rgb_matrix_set_color(10+(12*i), RGB_YELLOW);

    rgb_matrix_set_color(4+(12*i), RGB_GREEN);

    rgb_matrix_set_color(5+(12*i), RGB_BLUE);

    rgb_matrix_set_color(6+(12*i), RGB_PURPLE);

    rgb_matrix_set_color(7+(12*i), RGB_MAGENTA);
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

#endif
