/* Copyright 2023
		 return true; // this allows for normal processing of key release! 
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

// Compile command
// qmk compile -kb kprepublic/cstc40/single_pcb -km omron

#include QMK_KEYBOARD_H

#include "print.h"

#define _BASE 0
#define _SYMB 1
#define _MEDIA 2
#define _NUM 3
#define _NAV 4
#define _FN 5
#define _MIDI 6
#define _GAME 7

enum custom_keycodes {
    // Tabs
    M_REOPT = SAFE_RANGE,
    M_CLOST,
    M_DUPT,
    M_RELOT,
    M_NEWT,
    M_PREVT,
    M_NEXTT,
    M_TOP,
    M_BOT,

    // Select
    M_SELBL,
    M_SELEL,
    M_SELBT,
    M_SELET,
    M_SELW,
    M_SELL,
    M_SELA,

    // Delete
    M_DELBL,
    M_DELEL,
    M_DELBT,
    M_DELET,
    M_DELW,
    M_DELL,
    M_DELA,

    // Copy
    M_CPBL,
    M_CPEL,
    M_CPBT,
    M_CPET,
    M_CPW,
    M_CPL,
    M_CPA,

    // Paste
    M_PSTBL,
    M_PSTEL,
    M_PSTBT,
    M_PSTET,
    M_PSTW,
    M_PSTL,
    M_PSTA,

    // Cut
    M_CUTBL,
    M_CUTEL,
    M_CUTBT,
    M_CUTET,
    M_CUTW,
    M_CUTL,
    M_CUTA
};

void keyboard_post_init_user(void) {
    rgb_matrix_mode(RGB_MATRIX_CUSTOM_BASE_RGB);
}

layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
    case _SYMB:
	rgb_matrix_mode(RGB_MATRIX_CUSTOM_SYMB_RGB);
        break;
    case _MEDIA:
	rgb_matrix_mode(RGB_MATRIX_CUSTOM_MEDIA_RGB);
        break;
    case _NUM:
	rgb_matrix_mode(RGB_MATRIX_CUSTOM_NUM_RGB);
        break;
    case _NAV:
	rgb_matrix_mode(RGB_MATRIX_CUSTOM_NAV_RGB);
        break;
    case _FN:
	rgb_matrix_mode(RGB_MATRIX_CUSTOM_FN_RGB);
        break;
    case _MIDI:
	rgb_matrix_mode(RGB_MATRIX_CUSTOM_MIDI_RGB);
        break;
    default:
	rgb_matrix_mode(RGB_MATRIX_CUSTOM_BASE_RGB);
        break;
    }
  return state;
}

void caps_word_set_user(bool active) {
    if (active) {
	rgb_matrix_mode(RGB_MATRIX_CUSTOM_SET_CAPS_RGB);
    } else {
	rgb_matrix_mode(RGB_MATRIX_CUSTOM_UNSET_CAPS_RGB);
    }
}

bool recording_dynamic_macro = false;

void handle_dynamic_macro(uint16_t keycode) {

    keyrecord_t kr;

    switch (keycode) {
        case DM_RSTP:
            recording_dynamic_macro = false;
            kr.event.pressed = true;
	    break;
        case DM_PLY1:
            kr.event.pressed = false;
	    break;
        case DM_REC1:
            recording_dynamic_macro = true;
            kr.event.pressed = false;
	    break;
	default:
	    return;
    }
    process_dynamic_macro(keycode, &kr);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  // If console is enabled, it will print the matrix position and status of each key pressed
    uprintf("KL: kc: 0x%04X, col: %2u, row: %2u, pressed: %u, time: %5u, int: %u, count: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);

    switch (keycode) {
    // Tabs
    case M_REOPT:
        if (record->event.pressed) { // when keycode is pressed
	    SEND_STRING(SS_LCTL(SS_LSFT("t")));
	} else { // when keycode is released
	}
	break;
    case M_CLOST:
        if (record->event.pressed) {
	    SEND_STRING(SS_LCTL("w"));
	}
	break;
    case M_DUPT:
        if (record->event.pressed) {
	    SEND_STRING(SS_LALT("d"SS_TAP(X_ENT)));
	}
	break;
    case M_RELOT:
        if (record->event.pressed) {
	    SEND_STRING(SS_LCTL("r"));
	}
	break;
    case M_NEWT:
        if (record->event.pressed) {
	    SEND_STRING(SS_LCTL("t"));
	}
	break;
    case M_PREVT:
        if (record->event.pressed) {
	    SEND_STRING(SS_LCTL(SS_LSFT(SS_TAP(X_TAB))));
	}
	break;
    case M_NEXTT:
        if (record->event.pressed) {
	    SEND_STRING(SS_LCTL(SS_TAP(X_TAB)));
	}
	break;
    case M_TOP:
        if (record->event.pressed) {
	    SEND_STRING(SS_LCTL(SS_TAP(X_HOME)));
	}
	break;
    case M_BOT:
        if (record->event.pressed) {
	    SEND_STRING(SS_LCTL(SS_TAP(X_END)));
	}
	break;

    // Select
    case M_SELBL:
        if (record->event.pressed) {
	    SEND_STRING(SS_LSFT(SS_TAP(X_HOME)));
	}
	break;
    case M_SELEL:
        if (record->event.pressed) {
	    SEND_STRING(SS_LSFT(SS_TAP(X_END)));
	}
	break;
    case M_SELBT:
        if (record->event.pressed) {
	    SEND_STRING(SS_LCTL(SS_LSFT(SS_TAP(X_HOME))));
	}
	break;
    case M_SELET:
        if (record->event.pressed) {
	    SEND_STRING(SS_LCTL(SS_LSFT(SS_TAP(X_END))));
	}
	break;
    case M_SELW:
        if (record->event.pressed) {
	    SEND_STRING(SS_LCTL(SS_TAP(X_LEFT)SS_LSFT(SS_TAP(X_RGHT))));
	}
	break;
    case M_SELL:
        if (record->event.pressed) {
	    SEND_STRING(SS_TAP(X_HOME)SS_LSFT(SS_TAP(X_END)));
	}
	break;
    case M_SELA:
        if (record->event.pressed) {
	    SEND_STRING(SS_LCTL("a"));
	}
	break;

    // Delete
    case M_DELBL:
        if (record->event.pressed) {
	    SEND_STRING(SS_LCTL(SS_LSFT(SS_TAP(X_BSPC))));
	}
	break;
    case M_DELEL:
        if (record->event.pressed) {
	    SEND_STRING(SS_LCTL(SS_LSFT(SS_TAP(X_DEL))));
	}
	break;
    case M_DELBT:
        if (record->event.pressed) {
	    SEND_STRING(SS_LCTL(SS_LSFT(SS_TAP(X_HOME)))SS_TAP(X_BSPC));
	}
	break;
    case M_DELET:
        if (record->event.pressed) {
	    SEND_STRING(SS_LCTL(SS_LSFT(SS_TAP(X_END)))SS_TAP(X_DEL));
	}
	break;
    case M_DELW:
        if (record->event.pressed) {
	    SEND_STRING(SS_LCTL(SS_TAP(X_LEFT)SS_TAP(X_DEL)));
	}
	break;
    case M_DELL:
        if (record->event.pressed) {
	    SEND_STRING(SS_TAP(X_HOME)SS_LCTL(SS_LSFT(SS_TAP(X_DEL)))SS_TAP(X_DEL));
	}
	break;
    case M_DELA:
        if (record->event.pressed) {
	    SEND_STRING(SS_LCTL("a")SS_TAP(X_DEL));
	}
	break;

    // Copy
    case M_CPBL:
        if (record->event.pressed) {
	    SEND_STRING(SS_LSFT(SS_TAP(X_HOME))SS_LCTL("c")SS_TAP(X_RGHT));
	}
	break;
    case M_CPEL:
        if (record->event.pressed) {
	    SEND_STRING(SS_LSFT(SS_TAP(X_END))SS_LCTL("c")SS_TAP(X_LEFT));
	}
	break;
    case M_CPBT:
        if (record->event.pressed) {
	    SEND_STRING(SS_LCTL(SS_LSFT(SS_TAP(X_HOME))"c")SS_TAP(X_RGHT));
	}
	break;
    case M_CPET:
        if (record->event.pressed) {
	    SEND_STRING(SS_LCTL(SS_LSFT(SS_TAP(X_END))"c")SS_TAP(X_LEFT));
	}
	break;
    case M_CPW:
        if (record->event.pressed) {
	    SEND_STRING(SS_LCTL(SS_TAP(X_LEFT)SS_LSFT(SS_TAP(X_RGHT))"c")SS_TAP(X_RIGHT));
	}
	break;
    case M_CPL:
        if (record->event.pressed) {
	    SEND_STRING(SS_TAP(X_HOME)SS_LSFT(SS_TAP(X_END))SS_LCTL("c")SS_TAP(X_RGHT));
	}
	break;
    case M_CPA:
        if (record->event.pressed) {
	    SEND_STRING(SS_LCTL("ac")SS_TAP(X_RGHT));
	}
	break;

    // Paste
    case M_PSTBL:
        if (record->event.pressed) {
	    SEND_STRING(SS_TAP(X_HOME)SS_LCTL("v"));
	}
	break;
    case M_PSTEL:
        if (record->event.pressed) {
	    SEND_STRING(SS_TAP(X_END)SS_LCTL("v"));
	}
	break;
    case M_PSTBT:
        if (record->event.pressed) {
	    SEND_STRING(SS_LCTL(SS_TAP(X_HOME)"v"));
	}
	break;
    case M_PSTET:
        if (record->event.pressed) {
	    SEND_STRING(SS_LCTL(SS_TAP(X_END)"v"));
	}
	break;
    case M_PSTW:
        if (record->event.pressed) {
	    SEND_STRING(SS_LCTL(SS_TAP(X_LEFT)SS_LSFT(SS_TAP(X_RGHT))"v"));
	}
	break;
    case M_PSTL:
        if (record->event.pressed) {
	    SEND_STRING(SS_TAP(X_HOME)SS_LSFT(SS_TAP(X_END))SS_LCTL("v"));
	}
	break;
    case M_PSTA:
        if (record->event.pressed) {
	    SEND_STRING(SS_LCTL("av"));
	}
	break;

    // Cut
    case M_CUTBL:
        if (record->event.pressed) {
	    SEND_STRING(SS_LSFT(SS_TAP(X_HOME))SS_LCTL("x"));
	}
	break;
    case M_CUTEL:
        if (record->event.pressed) {
	    SEND_STRING(SS_LSFT(SS_TAP(X_END))SS_LCTL("x"));
	}
	break;
    case M_CUTBT:
        if (record->event.pressed) {
	    SEND_STRING(SS_LCTL(SS_LSFT(SS_TAP(X_HOME))"x"));
	}
	break;
    case M_CUTET:
        if (record->event.pressed) {
	    SEND_STRING(SS_LCTL(SS_LSFT(SS_TAP(X_END))"x"));
	}
	break;
    case M_CUTW:
        if (record->event.pressed) {
	    SEND_STRING(SS_LCTL(SS_TAP(X_LEFT)SS_LSFT(SS_TAP(X_RGHT))"x"));
	}
	break;
    case M_CUTL:
        if (record->event.pressed) {
	    SEND_STRING(SS_TAP(X_HOME)SS_LSFT(SS_TAP(X_END))SS_LCTL("x")SS_TAP(X_DEL));
	}
	break;
    case M_CUTA:
        if (record->event.pressed) {
	    SEND_STRING(SS_LCTL("ax"));
	}
	break;

    // Dynamic Macro
    case LT(0,KC_NO):
        keyrecord_t kr;
        //if (record->tap.count && record->event.pressed) { // Intercept tap
        if (record->tap.count && !record->event.pressed) { // Intercept tap release
            if (recording_dynamic_macro) {
		//tap_code(KC_S);
                recording_dynamic_macro = false;

                kr.event.pressed = true;
                process_dynamic_macro(DM_RSTP, &kr);
                //handle_dynamic_macro(DM_RSTP);
            } else {
		//tap_code(KC_P);
                kr.event.pressed = false;
                process_dynamic_macro(DM_PLY1, &kr);
                //handle_dynamic_macro(DM_PLY1);
	    }
        //} else if (record->event.pressed) { // Intercept hold
        } else if (!record->event.pressed) { // Intercept hold release
            if (recording_dynamic_macro) {
		//tap_code(KC_S);
                kr.event.pressed = true;
                process_dynamic_macro(DM_RSTP, &kr);
                //handle_dynamic_macro(DM_RSTP);
            } else {
		//tap_code(KC_R);
                kr.event.pressed = false;
                process_dynamic_macro(DM_REC1, &kr);
                //handle_dynamic_macro(DM_REC1);
	    }
            recording_dynamic_macro = !recording_dynamic_macro;
        }
        return false;
    }
    return true;
};


void dynamic_macro_record_start_user(int8_t direction) {
    //tap_code(KC_F);
    //tap_code(KC_R);
    uprintf("in dynamic_macro_record_start_user\n");
}

void dynamic_macro_play_user(int8_t direction) {
    //tap_code(KC_F);
    //tap_code(KC_P);
    uprintf("in dynamic_macro_play_user\n");
}

void dynamic_macro_record_key_user(int8_t direction, keyrecord_t *record) {
    //tap_code(KC_I);
    //tap_code(KC_R);
    uprintf("in dynamic_macro_record_key_user\n");
}

void dynamic_macro_record_end_user(int8_t direction) {
    //tap_code(KC_F);
    //tap_code(KC_S);
    uprintf("in dynamic_macro_record_end_user\n");
}

/*
void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
  debug_enable=true;
  debug_matrix=true;
  debug_keyboard=true;
  //debug_mouse=true;
}
*/

// Leader Sequences
void leader_start_user(void) {
    layer_move(_BASE);
}

void leader_end_user(void) {
    // One key sequence
    if (leader_sequence_one_key(KC_Q)) {
        // q : Quit
	SEND_STRING(SS_LALT(SS_TAP(X_F4)));
    } else if (leader_sequence_one_key(KC_F)) {
        // f : Open File Explorer
	SEND_STRING(SS_TAP(X_MYCM));
    } else if (leader_sequence_one_key(KC_C)) {
        // c : Open Calculator
	SEND_STRING(SS_TAP(X_CALC));
    } else if (leader_sequence_one_key(KC_T)) {
        // t : Open Task Manager
	SEND_STRING(SS_LCTL(SS_LSFT(SS_TAP(X_ESC))));
    } else if (leader_sequence_one_key(KC_M)) {
        // m : MIDI Layer
        layer_move(_MIDI);
    } else if (leader_sequence_one_key(KC_G)) {
        // g : Game Layer
        layer_move(_GAME);

    // Three key sequence
    } else if (leader_sequence_three_keys(KC_C, KC_A, KC_D)) {
        // c, a, d : Ctrl+Alt+Del
	SEND_STRING(SS_LCTL(SS_LALT(SS_TAP(X_DEL))));
    } else if (leader_sequence_three_keys(KC_S, KC_E, KC_T)) {
        // s, e, t : Open Settings
	SEND_STRING(SS_LGUI("i"));
    } else if (leader_sequence_three_keys(KC_E, KC_M, KC_A)) {
        // e, m, a : Type email address 1
	SEND_STRING("idieli1554@gmail.com");
    } else if (leader_sequence_three_keys(KC_E, KC_M, KC_S)) {
        // e, m, s : Type email address 2
	SEND_STRING("i.hate.grenades@gmail.com");
    } else if (leader_sequence_three_keys(KC_E, KC_M, KC_D)) {
        // e, m, d : Type email address 3
	SEND_STRING("pmegiasc@gmail.com");

    // Four key sequence
    } else if (leader_sequence_four_keys(KC_S, KC_N, KC_I, KC_P)) {
        // s, n, i, p : Partial screenshot
	SEND_STRING(SS_LGUI(SS_LSFT("s")));
    } else if (leader_sequence_four_keys(KC_H, KC_E, KC_L, KC_P)) {
        // h, e, l, p : Type github url
	SEND_STRING("https://github.com/idieli/qmk_firmware/tree/master/keyboards/kprepublic/cstc40/keymaps/omron");

    // Five key sequence
    } else if (leader_sequence_five_keys(KC_E, KC_M, KC_O, KC_J, KC_I)) {
        // e, m, o, j, i : Open Emoji Panel
	SEND_STRING(SS_LGUI("."));
    } else if (leader_sequence_five_keys(KC_A, KC_B, KC_O, KC_U, KC_T)) {
        // a, b, o, u, t : Open System Properties
	SEND_STRING(SS_LGUI(SS_TAP(X_PAUS)));
    }
}

// Combos

// Select (Grab)
const uint16_t PROGMEM select_beginning_of_line[] = {KC_G, KC_LEFT, COMBO_END};
const uint16_t PROGMEM select_end_of_line[] = {KC_G, KC_RGHT, COMBO_END};
const uint16_t PROGMEM select_beginning_of_text[] = {KC_G, KC_UP, COMBO_END};
const uint16_t PROGMEM select_end_of_text[] = {KC_G, KC_DOWN, COMBO_END};
const uint16_t PROGMEM select_word[] = {KC_G, KC_W, COMBO_END};
const uint16_t PROGMEM select_line[] = {KC_G, KC_L, COMBO_END};
const uint16_t PROGMEM select_all[] = {KC_G, KC_A, COMBO_END};

// Delete (Remove)
const uint16_t PROGMEM delete_beginning_of_line[] = {KC_R, KC_LEFT, COMBO_END};
const uint16_t PROGMEM delete_end_of_line[] = {KC_R, KC_RGHT, COMBO_END};
const uint16_t PROGMEM delete_beginning_of_text[] = {KC_R, KC_UP, COMBO_END};
const uint16_t PROGMEM delete_end_of_text[] = {KC_R, KC_DOWN, COMBO_END};
const uint16_t PROGMEM delete_word[] = {KC_R, KC_W, COMBO_END};
const uint16_t PROGMEM delete_line[] = {KC_R, KC_L, COMBO_END};
const uint16_t PROGMEM delete_all[] = {KC_R, KC_A, COMBO_END};

// Copy (Bring)
const uint16_t PROGMEM copy_beginning_of_line[] = {KC_B, KC_LEFT, COMBO_END};
const uint16_t PROGMEM copy_end_of_line[] = {KC_B, KC_RGHT, COMBO_END};
const uint16_t PROGMEM copy_beginning_of_text[] = {KC_B, KC_UP, COMBO_END};
const uint16_t PROGMEM copy_end_of_text[] = {KC_B, KC_DOWN, COMBO_END};
const uint16_t PROGMEM copy_word[] = {KC_B, KC_W, COMBO_END};
const uint16_t PROGMEM copy_line[] = {KC_B, KC_L, COMBO_END};
const uint16_t PROGMEM copy_all[] = {KC_B, KC_A, COMBO_END};

// Paste
const uint16_t PROGMEM paste_beginning_of_line[] = {KC_V, KC_LEFT, COMBO_END};
const uint16_t PROGMEM paste_end_of_line[] = {KC_V, KC_RGHT, COMBO_END};
const uint16_t PROGMEM paste_beginning_of_text[] = {KC_V, KC_UP, COMBO_END};
const uint16_t PROGMEM paste_end_of_text[] = {KC_V, KC_DOWN, COMBO_END};
const uint16_t PROGMEM paste_word[] = {KC_V, KC_W, COMBO_END};
const uint16_t PROGMEM paste_line[] = {KC_V, KC_L, COMBO_END};
const uint16_t PROGMEM paste_all[] = {KC_V, KC_A, COMBO_END};

// Cut (Take)
const uint16_t PROGMEM cut_beginning_of_line[] = {KC_T, KC_LEFT, COMBO_END};
const uint16_t PROGMEM cut_end_of_line[] = {KC_T, KC_RGHT, COMBO_END};
const uint16_t PROGMEM cut_beginning_of_text[] = {KC_T, KC_UP, COMBO_END};
const uint16_t PROGMEM cut_end_of_text[] = {KC_T, KC_DOWN, COMBO_END};
const uint16_t PROGMEM cut_word[] = {KC_T, KC_W, COMBO_END};
const uint16_t PROGMEM cut_line[] = {KC_T, KC_L, COMBO_END};
const uint16_t PROGMEM cut_all[] = {KC_T, KC_A, COMBO_END};

combo_t key_combos[] = {
    // Select
    COMBO(select_beginning_of_line, M_SELBL),
    COMBO(select_end_of_line, M_SELEL),
    COMBO(select_beginning_of_text, M_SELBT),
    COMBO(select_end_of_text, M_SELET),
    COMBO(select_word, M_SELW),
    COMBO(select_line, M_SELL),
    COMBO(select_all, M_SELA),

    // Delete
    COMBO(delete_beginning_of_line, M_DELBL),
    COMBO(delete_end_of_line, M_DELEL),
    COMBO(delete_beginning_of_text, M_DELBT),
    COMBO(delete_end_of_text, M_DELET),
    COMBO(delete_word, M_DELW),
    COMBO(delete_line, M_DELL),
    COMBO(delete_all, M_DELA),

    // Copy
    COMBO(copy_beginning_of_line, M_CPBL),
    COMBO(copy_end_of_line, M_CPEL),
    COMBO(copy_beginning_of_text, M_CPBT),
    COMBO(copy_end_of_text, M_CPET),
    COMBO(copy_word, M_CPW),
    COMBO(copy_line, M_CPL),
    COMBO(copy_all, M_CPA),

    // Paste
    COMBO(paste_beginning_of_line, M_PSTBL),
    COMBO(paste_end_of_line, M_PSTEL),
    COMBO(paste_beginning_of_text, M_PSTBT),
    COMBO(paste_end_of_text, M_PSTET),
    COMBO(paste_word, M_PSTW),
    COMBO(paste_line, M_PSTL),
    COMBO(paste_all, M_PSTA),

    // Cut
    COMBO(cut_beginning_of_line, M_CUTBL),
    COMBO(cut_end_of_line, M_CUTEL),
    COMBO(cut_beginning_of_text, M_CUTBT),
    COMBO(cut_end_of_text, M_CUTET),
    COMBO(cut_word, M_CUTW),
    COMBO(cut_line, M_CUTL),
    COMBO(cut_all, M_CUTA)
};

bool caps_word_press_user(uint16_t keycode) {
    switch (keycode) {
        // Keycodes that continue Caps Word, with shift applied.
        case KC_A ... KC_Z:
            add_weak_mods(MOD_BIT(KC_LSFT));  // Apply shift to next key.
            return true;

	// Keycodes that deactivate Caps Word.
	case TO(_BASE):
	case KC_ESC:
	case KC_LSFT:
	case KC_RSFT:
        case LT(0,KC_NO):
	case KC_LALT:
	case KC_RALT:
	case KC_LCTL:
	case KC_RCTL:
	case KC_LGUI:
	case KC_RGUI:
	case QK_LEAD:
	    return false;

        // Continue Caps Word, without shifting.
        default:
            return true;
    }
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Empty
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
/*
[_EMPTY] = LAYOUT_planck_mit(
    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
    _______,  _______,  _______,  _______,  _______,        _______,      _______,  _______,  _______,  _______,  _______
),
*/

/* Base
 * ,-----------------------------------------------------------------------------------.
 * | Esc  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift|   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  | SYMB | Shift|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Enter|   Z  |   X  |   C  |   V  |   B  |   N  |   M  | Left | Down |  Up  | Right|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | MEDIA| Macro|  Alt | Ctrl |  NUM |    Space    |  NAV | Ctrl |  Win | Lead |  FN  |
 * `-----------------------------------------------------------------------------------'
 */
[_BASE] = LAYOUT_planck_mit(
    KC_ESC,      KC_Q,         KC_W,     KC_E,     KC_R,      KC_T,    KC_Y,  KC_U,      KC_I,     KC_O,     KC_P,       KC_BSPC,
    KC_LSFT,     KC_A,         KC_S,     KC_D,     KC_F,      KC_G,    KC_H,  KC_J,      KC_K,     KC_L,     TT(_SYMB),  KC_RSFT,
    KC_ENT,      KC_Z,         KC_X,     KC_C,     KC_V,      KC_B,    KC_N,  KC_M,      KC_LEFT,  KC_DOWN,  KC_UP,      KC_RGHT,
    TT(_MEDIA),  LT(0,KC_NO),  KC_LALT,  KC_LCTL,  TT(_NUM),      KC_SPC,     TT(_NAV),  KC_RCTL,  KC_RGUI,  QK_LEAD,    MO(_FN)
),

/* Symbols
 * ,-----------------------------------------------------------------------------------.
 * | BASE |   {  |   }  |   &  |   |  |   ~  |      |   ?  |   '  |   `  |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |   [  |   ]  |   (  |   )  |      |      |   .  |   ,  |   :  |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |   @  |   $  |   #  |   _  |   \  |      |   !  |   "  |   ;  |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_SYMB] = LAYOUT_planck_mit(
    TO(_BASE),  KC_LCBR,  KC_RCBR,  KC_AMPR,  KC_PIPE,  KC_TILD,  _______,  KC_QUES,  KC_QUOT,  KC_GRV,   _______,  _______,
    _______,    KC_LBRC,  KC_RBRC,  KC_LPRN,  KC_RPRN,  _______,  _______,  KC_DOT,   KC_COMM,  KC_COLN,  _______,  _______,
    _______,  	KC_AT,    KC_DLR,   KC_HASH,  KC_UNDS,  KC_BSLS,  _______,  KC_EXLM,  KC_DQT,   KC_SCLN,  _______,  _______,
    _______,    _______,  _______,  _______,  _______,       _______,       _______,  _______,  _______,  _______,  _______
),

/* Media
 * ,-----------------------------------------------------------------------------------.
 * | BASE |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |Prv Tr|Nxt Tr|      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | Vol- | Vol+ | Mute | Play |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_MEDIA] = LAYOUT_planck_mit(
    TO(_BASE),  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
    _______,    KC_MPRV,  KC_MNXT,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
    _______,    KC_VOLD,  KC_VOLU,  KC_MUTE,  KC_MPLY,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
    _______,    _______,  _______,  _______,  _______,       _______,       _______,  _______,  _______,  _______,  _______
),

/* Numerical
 * ,-----------------------------------------------------------------------------------.
 * | BASE |      |   7  |   8  |   9  |      |      |   <  |   *  |   /  |      |  Del |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |   0  |   4  |   5  |   6  |      |      |   =  |   +  |   -  |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Bksp |   .  |   1  |   2  |   3  |      |      |   >  |   ^  |   %  |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |     Tab     |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_NUM] = LAYOUT_planck_mit(
    TO(_BASE),  _______,  KC_7,     KC_8,     KC_9,     _______,  _______,  KC_LT,    KC_ASTR,  KC_SLSH,  _______,  KC_DEL,
    _______,    KC_0,     KC_4,     KC_5,     KC_6,     _______,  _______,  KC_EQL,   KC_PLUS,  KC_MINS,  _______,  _______,
    KC_BSPC,    KC_DOT,   KC_1,     KC_2,     KC_3,     _______,  _______,  KC_GT,    KC_CIRC,  KC_PERC,  _______,  _______,
    _______,    _______,  _______,  _______,  _______,        KC_TAB,       _______,  _______,  _______,  _______,  _______
),

/* Navigation
 * ,-----------------------------------------------------------------------------------.
 * | BASE |ReO Tb|Cls Tb|Dup Tb|Rld Tb|New Tb|Scr Lt|Scr Dn|Scr Up|Scr Rt|Pg Top|  Del |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |Prv Tb|Nxt Tb|Rt Clk|Lt Clk|Md Clk|Mou Lt|Mou Dn|Mou Up|Mou Rt|Pg Bot|      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | Acc0 | Acc1 | Acc2 |      |      |      |      | Home | PgDn | PgUp |  End |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |     Tab     |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_NAV] = LAYOUT_planck_mit(
    TO(_BASE),  M_REOPT,  M_CLOST,  M_DUPT,   M_RELOT,  M_NEWT,   KC_WH_L,  KC_WH_D,  KC_WH_U,  KC_WH_R,  M_TOP,    KC_DEL,
    _______,    M_PREVT,  M_NEXTT,  KC_BTN2,  KC_BTN1,  KC_BTN3,  KC_MS_L,  KC_MS_D,  KC_MS_U,  KC_MS_R,  M_BOT,    _______,
    _______,    KC_ACL0,  KC_ACL1,  KC_ACL2,  _______,  _______,  _______,  _______,  KC_HOME,  KC_PGUP,  KC_PGDN,  KC_END,
    _______,    _______,  _______,  _______,  _______,        KC_TAB,       _______,  _______,  _______,  _______,  _______
),

/* Function
 * ,-----------------------------------------------------------------------------------.
 * | BASE |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |  Ins | Prtsc| Reset| Boot |  F11 |  F12 |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_FN] = LAYOUT_planck_mit(
    TO(_BASE),  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   _______,
    _______,    _______,  _______,  _______,  _______,  KC_INS,   KC_PSCR,  QK_RBT,   QK_BOOT,  KC_F11,   KC_F12,   _______,
    _______,    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
    _______,    _______,  _______,  _______,  _______,        _______,      _______,  _______,  _______,  _______,  _______
),

/* Midi
 * ,-----------------------------------------------------------------------------------.
 * |  C4  |  Cs4 |  D4  |  Ds4 |  E4  |  F4  |  Fs4 |  G4  |  Gs4 |  A4  |  As4 |  B4  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |  C3  |  Cs3 |  D3  |  Ds3 |  E3  |  F3  |  Fs3 |  G3  |  Gs3 |  A3  |  As3 |  B3  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |  C2  |  Cs2 |  D2  |  Ds2 |  E2  |  F2  |  Fs2 |  G2  |  Gs2 |  A2  |  As2 |  B2  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Oct- | Oct+ |      |      |      |             |      |      |      |Trnps-|Trnps+|
 * `-----------------------------------------------------------------------------------'
 */
[_MIDI] = LAYOUT_planck_mit(
    MI_C4,    MI_Cs4,   MI_D4,    MI_Ds4,   MI_E4,    MI_F4,    MI_Fs4,  MI_G4,    MI_Gs4,   MI_A4,    MI_As4,   MI_B4,
    MI_C3,    MI_Cs3,   MI_D3,    MI_Ds3,   MI_E3,    MI_F3,    MI_Fs3,  MI_G3,    MI_Gs3,   MI_A3,    MI_As3,   MI_B3,
    MI_C2,    MI_Cs2,   MI_D2,    MI_Ds2,   MI_E2,    MI_F2,    MI_Fs2,  MI_G2,    MI_Gs2,   MI_A2,    MI_As2,   MI_B2,
    MI_OCTD,  MI_OCTD,  XXXXXXX,  XXXXXXX,  XXXXXXX,     TO(_BASE),      XXXXXXX,  XXXXXXX,  XXXXXXX,  MI_TRSD,  MI_TRSU
),

/* Game
 * ,-----------------------------------------------------------------------------------.
 * | Esc  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   .  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Enter|   Z  |   X  |   C  |   V  |   B  |   N  |   M  | Left | Down |  Up  | Right|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | BASE |      |      |      |      |    Space    |   1  |   2  |   3  |   4  |   5  |
 * `-----------------------------------------------------------------------------------'
 */
[_GAME] = LAYOUT_planck_mit(
    KC_ESC,     KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,    KC_Y,  KC_U,  KC_I,     KC_O,     KC_P,    KC_BSPC,
    XXXXXXX,    KC_A,     KC_S,     KC_D,     KC_F,     KC_G,    KC_H,  KC_J,  KC_K,     KC_L,     KC_DOT,  XXXXXXX,
    KC_ENT,     KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,    KC_N,  KC_M,  KC_LEFT,  KC_DOWN,  KC_UP,   KC_RGHT,
    TO(_BASE),  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,      KC_SPC,     KC_1,  KC_2,     KC_3,     KC_4,    KC_5
)

};
