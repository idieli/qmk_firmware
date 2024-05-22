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

// Compile:
//   qmk compile -kb kprepublic/cstc40/single_pcb -km omron

#include QMK_KEYBOARD_H

// Layers
#define _BASE 0
#define _SYMB 1
#define _MEDIA 2
#define _NUM 3
#define _NAV 4
#define _FN 5
#define _GAME 6
#define _MIDI_SCALES 7
#define _MIDI_ALL 8

// Scales
#define IONIAN 0
#define DORIAN 1
#define PHRYGIAN 2
#define LYDIAN 3
#define MIXOLYDIAN 4
#define AEOLIAN 5
#define LOCRIAN 6
#define PENTATONIC 7

#define NOTE_BASE 48
#define VELOCITY_BASE 80

// Midi
extern MidiDevice midi_device;

uint8_t num_of_scales = 8;
uint8_t scales[8][8] = {
    {0, 2, 4, 5, 7,  9,  11, 12}, // Ionian
    {0, 2, 3, 5, 7,  9,  10, 12}, // Dorian
    {0, 1, 3, 5, 7,  8,  10, 12}, // Phrygian
    {0, 2, 4, 6, 7,  9,  11, 12}, // Lydian
    {0, 2, 4, 5, 7,  9,  10, 12}, // Mixolydian
    {0, 2, 3, 5, 7,  8,  10, 12}, // Aeolian
    {0, 1, 3, 5, 6,  8,  10, 12}, // Locrian
    {0, 3, 5, 7, 10, 12, 15, 17}  // Pentatonic
};
uint8_t curr_scale = IONIAN;
uint8_t pitch_mod = 0;
uint8_t octave_mod = 0;
uint8_t velocity_mod = 0;

// Dynamic Macro
bool recording_dynamic_macro = false;

// Leader Key
uint8_t leader_state = 0; // 0: no action, 1: accepted, 2: rejected
bool leader_led_on = false;
static uint16_t leader_timer;

// Custom Keycodes
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
    M_CUTA,

    // Midi
    NOTE_00,
    NOTE_01,
    NOTE_02,
    NOTE_03,
    NOTE_04,
    NOTE_05,
    NOTE_06,
    NOTE_07,

    NOTE_10,
    NOTE_11,
    NOTE_12,
    NOTE_13,
    NOTE_14,
    NOTE_15,
    NOTE_16,
    NOTE_17,

    NOTE_20,
    NOTE_21,
    NOTE_22,
    NOTE_23,
    NOTE_24,
    NOTE_25,
    NOTE_26,
    NOTE_27,

    SCALE_P,
    SCALE_N,

    PITCH_D,
    PITCH_U,

    OCT_D,
    OCT_U,

    VEL_D,
    VEL_U
};

// Midi
uint8_t get_pitch_upper(uint8_t i) {
    return (NOTE_BASE + pitch_mod + octave_mod*12 + scales[curr_scale][i] + 12);
}
uint8_t get_pitch_mid(uint8_t i) {
    return (NOTE_BASE + pitch_mod + octave_mod*12 + scales[curr_scale][i]);
}
uint8_t get_pitch_lower(uint8_t i) {
    return (NOTE_BASE + pitch_mod + octave_mod*12 + scales[curr_scale][i] - 12);
}

// Startup
void keyboard_post_init_user(void) {
    rgb_matrix_mode(RGB_MATRIX_CUSTOM_ALL_OFF_RGB);
}

// RGB
bool rgb_matrix_indicators_user(void) {
    if (leader_state) { 
        if (!leader_led_on) {
            switch (leader_state) {
                case 1: // accepted
                    rgb_matrix_mode(RGB_MATRIX_CUSTOM_SET_LEADER_ACCEPTED_RGB);
                    break;
                case 2: // rejected
                    rgb_matrix_mode(RGB_MATRIX_CUSTOM_SET_LEADER_REJECTED_RGB);
                    break;
            }
            leader_led_on = true;
            leader_timer = timer_read(); 
        } else if (timer_elapsed(leader_timer) > 500) {
            rgb_matrix_mode(RGB_MATRIX_CUSTOM_UNSET_LEADER_RGB);
            leader_state = 0;
            leader_led_on = false;
        }
    } 
    return false;
}

// Layers
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
    case _GAME:
	rgb_matrix_mode(RGB_MATRIX_CUSTOM_GAME_RGB);
        break;
    case _MIDI_SCALES:
	rgb_matrix_mode(RGB_MATRIX_CUSTOM_MIDI_SCALES_RGB);
        break;
    case _MIDI_ALL:
	rgb_matrix_mode(RGB_MATRIX_CUSTOM_MIDI_RGB);
        break;
    default:
	rgb_matrix_mode(RGB_MATRIX_CUSTOM_BASE_RGB);
        break;
    }
  return state;
}

// Caps Word
void caps_word_set_user(bool active) {
    if (active) {
	rgb_matrix_mode(RGB_MATRIX_CUSTOM_SET_CAPS_RGB);
    } else {
	rgb_matrix_mode(RGB_MATRIX_CUSTOM_UNSET_CAPS_RGB);
    }
}

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

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
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
	    SEND_STRING(SS_LALT("d"SS_DELAY(10)SS_TAP(X_ENT)));
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
        if (record->tap.count) { // Intercept tap
            if (recording_dynamic_macro) { // Stop recording
                process_dynamic_macro(DM_RSTP, record);
	        rgb_matrix_mode(RGB_MATRIX_CUSTOM_UNSET_MACRO_RGB);
                if (!record->event.pressed) { // On release
                    recording_dynamic_macro = false;
                }
            } else { //	Play recording
                process_dynamic_macro(DM_PLY1, record);
	    }
        } else { // Intercept hold
            if (recording_dynamic_macro) { // Stop recording
                process_dynamic_macro(DM_RSTP, record);
	        rgb_matrix_mode(RGB_MATRIX_CUSTOM_UNSET_MACRO_RGB);
                if (!record->event.pressed) { // On release
                    recording_dynamic_macro = false;
                }
            } else { //	Start recording
                process_dynamic_macro(DM_REC1, record);
	        rgb_matrix_mode(RGB_MATRIX_CUSTOM_SET_MACRO_RGB);
                if (!record->event.pressed) { // On release
                    recording_dynamic_macro = true;
                }
	    }
        }
        return false;

    // Midi
    case NOTE_00:
        if (record->event.pressed) { // On press
            midi_send_noteon(&midi_device,midi_config.channel,get_pitch_upper(0),VELOCITY_BASE+velocity_mod);
        } else { // On release
            midi_send_noteoff(&midi_device,midi_config.channel,get_pitch_upper(0),VELOCITY_BASE+velocity_mod);
        }
	break;
    case NOTE_01:
        if (record->event.pressed) {
            midi_send_noteon(&midi_device,midi_config.channel,get_pitch_upper(1),VELOCITY_BASE+velocity_mod);
        } else {
            midi_send_noteoff(&midi_device,midi_config.channel,get_pitch_upper(1),VELOCITY_BASE+velocity_mod);
        }
	break;
    case NOTE_02:
        if (record->event.pressed) {
            midi_send_noteon(&midi_device,midi_config.channel,get_pitch_upper(2),VELOCITY_BASE+velocity_mod);
        } else {
            midi_send_noteoff(&midi_device,midi_config.channel,get_pitch_upper(2),VELOCITY_BASE+velocity_mod);
        }
	break;
    case NOTE_03:
        if (record->event.pressed) {
            midi_send_noteon(&midi_device,midi_config.channel,get_pitch_upper(3),VELOCITY_BASE+velocity_mod);
        } else {
            midi_send_noteoff(&midi_device,midi_config.channel,get_pitch_upper(3),VELOCITY_BASE+velocity_mod);
        }
	break;
    case NOTE_04:
        if (record->event.pressed) {
            midi_send_noteon(&midi_device,midi_config.channel,get_pitch_upper(4),VELOCITY_BASE+velocity_mod);
        } else {
            midi_send_noteoff(&midi_device,midi_config.channel,get_pitch_upper(4),VELOCITY_BASE+velocity_mod);
        }
	break;
    case NOTE_05:
        if (record->event.pressed) {
            midi_send_noteon(&midi_device,midi_config.channel,get_pitch_upper(5),VELOCITY_BASE+velocity_mod);
        } else {
            midi_send_noteoff(&midi_device,midi_config.channel,get_pitch_upper(5),VELOCITY_BASE+velocity_mod);
        }
	break;
    case NOTE_06:
        if (record->event.pressed) {
            midi_send_noteon(&midi_device,midi_config.channel,get_pitch_upper(6),VELOCITY_BASE+velocity_mod);
        } else {
            midi_send_noteoff(&midi_device,midi_config.channel,get_pitch_upper(6),VELOCITY_BASE+velocity_mod);
        }
	break;
    case NOTE_07:
        if (record->event.pressed) {
            midi_send_noteon(&midi_device,midi_config.channel,get_pitch_upper(7),VELOCITY_BASE+velocity_mod);
        } else {
            midi_send_noteoff(&midi_device,midi_config.channel,get_pitch_upper(7),VELOCITY_BASE+velocity_mod);
        }
	break;


    case NOTE_10:
        if (record->event.pressed) { // On press
            midi_send_noteon(&midi_device,midi_config.channel,get_pitch_mid(0),VELOCITY_BASE+velocity_mod);
        } else { // On release
            midi_send_noteoff(&midi_device,midi_config.channel,get_pitch_mid(0),VELOCITY_BASE+velocity_mod);
        }
	break;
    case NOTE_11:
        if (record->event.pressed) {
            midi_send_noteon(&midi_device,midi_config.channel,get_pitch_mid(1),VELOCITY_BASE+velocity_mod);
        } else {
            midi_send_noteoff(&midi_device,midi_config.channel,get_pitch_mid(1),VELOCITY_BASE+velocity_mod);
        }
	break;
    case NOTE_12:
        if (record->event.pressed) {
            midi_send_noteon(&midi_device,midi_config.channel,get_pitch_mid(2),VELOCITY_BASE+velocity_mod);
        } else {
            midi_send_noteoff(&midi_device,midi_config.channel,get_pitch_mid(2),VELOCITY_BASE+velocity_mod);
        }
	break;
    case NOTE_13:
        if (record->event.pressed) {
            midi_send_noteon(&midi_device,midi_config.channel,get_pitch_mid(3),VELOCITY_BASE+velocity_mod);
        } else {
            midi_send_noteoff(&midi_device,midi_config.channel,get_pitch_mid(3),VELOCITY_BASE+velocity_mod);
        }
	break;
    case NOTE_14:
        if (record->event.pressed) {
            midi_send_noteon(&midi_device,midi_config.channel,get_pitch_mid(4),VELOCITY_BASE+velocity_mod);
        } else {
            midi_send_noteoff(&midi_device,midi_config.channel,get_pitch_mid(4),VELOCITY_BASE+velocity_mod);
        }
	break;
    case NOTE_15:
        if (record->event.pressed) {
            midi_send_noteon(&midi_device,midi_config.channel,get_pitch_mid(5),VELOCITY_BASE+velocity_mod);
        } else {
            midi_send_noteoff(&midi_device,midi_config.channel,get_pitch_mid(5),VELOCITY_BASE+velocity_mod);
        }
	break;
    case NOTE_16:
        if (record->event.pressed) {
            midi_send_noteon(&midi_device,midi_config.channel,get_pitch_mid(6),VELOCITY_BASE+velocity_mod);
        } else {
            midi_send_noteoff(&midi_device,midi_config.channel,get_pitch_mid(6),VELOCITY_BASE+velocity_mod);
        }
	break;
    case NOTE_17:
        if (record->event.pressed) {
            midi_send_noteon(&midi_device,midi_config.channel,get_pitch_mid(7),VELOCITY_BASE+velocity_mod);
        } else {
            midi_send_noteoff(&midi_device,midi_config.channel,get_pitch_mid(7),VELOCITY_BASE+velocity_mod);
        }
	break;


    case NOTE_20:
        if (record->event.pressed) { // On press
            midi_send_noteon(&midi_device,midi_config.channel,get_pitch_lower(0),VELOCITY_BASE+velocity_mod);
        } else { // On release
            midi_send_noteoff(&midi_device,midi_config.channel,get_pitch_lower(0),VELOCITY_BASE+velocity_mod);
        }
	break;
    case NOTE_21:
        if (record->event.pressed) {
            midi_send_noteon(&midi_device,midi_config.channel,get_pitch_lower(1),VELOCITY_BASE+velocity_mod);
        } else {
            midi_send_noteoff(&midi_device,midi_config.channel,get_pitch_lower(1),VELOCITY_BASE+velocity_mod);
        }
	break;
    case NOTE_22:
        if (record->event.pressed) {
            midi_send_noteon(&midi_device,midi_config.channel,get_pitch_lower(2),VELOCITY_BASE+velocity_mod);
        } else {
            midi_send_noteoff(&midi_device,midi_config.channel,get_pitch_lower(2),VELOCITY_BASE+velocity_mod);
        }
	break;
    case NOTE_23:
        if (record->event.pressed) {
            midi_send_noteon(&midi_device,midi_config.channel,get_pitch_lower(3),VELOCITY_BASE+velocity_mod);
        } else {
            midi_send_noteoff(&midi_device,midi_config.channel,get_pitch_lower(3),VELOCITY_BASE+velocity_mod);
        }
	break;
    case NOTE_24:
        if (record->event.pressed) {
            midi_send_noteon(&midi_device,midi_config.channel,get_pitch_lower(4),VELOCITY_BASE+velocity_mod);
        } else {
            midi_send_noteoff(&midi_device,midi_config.channel,get_pitch_lower(4),VELOCITY_BASE+velocity_mod);
        }
	break;
    case NOTE_25:
        if (record->event.pressed) {
            midi_send_noteon(&midi_device,midi_config.channel,get_pitch_lower(5),VELOCITY_BASE+velocity_mod);
        } else {
            midi_send_noteoff(&midi_device,midi_config.channel,get_pitch_lower(5),VELOCITY_BASE+velocity_mod);
        }
	break;
    case NOTE_26:
        if (record->event.pressed) {
            midi_send_noteon(&midi_device,midi_config.channel,get_pitch_lower(6),VELOCITY_BASE+velocity_mod);
        } else {
            midi_send_noteoff(&midi_device,midi_config.channel,get_pitch_lower(6),VELOCITY_BASE+velocity_mod);
        }
	break;
    case NOTE_27:
        if (record->event.pressed) {
            midi_send_noteon(&midi_device,midi_config.channel,get_pitch_lower(7),VELOCITY_BASE+velocity_mod);
        } else {
            midi_send_noteoff(&midi_device,midi_config.channel,get_pitch_lower(7),VELOCITY_BASE+velocity_mod);
        }
	break;


    case SCALE_P:
        if (record->event.pressed) {
            curr_scale = (((curr_scale - 1) % num_of_scales) + num_of_scales) % num_of_scales;
        }
	break;
    case SCALE_N:
        if (record->event.pressed) {
            curr_scale = (curr_scale + 1) % num_of_scales;
        }
	break;


    case PITCH_D:
        if (record->event.pressed) {
            pitch_mod = (pitch_mod - 1);
        }
	break;
    case PITCH_U:
        if (record->event.pressed) {
            pitch_mod = (pitch_mod + 1);
        }
	break;


    case OCT_D:
        if (record->event.pressed) {
            octave_mod = (octave_mod - 1);
        }
	break;
    case OCT_U:
        if (record->event.pressed) {
            octave_mod = (octave_mod + 1);
        }
	break;


    case VEL_D:
        if (record->event.pressed) {
            velocity_mod = (velocity_mod - 5);
        }
	break;
    case VEL_U:
        if (record->event.pressed) {
            velocity_mod = (velocity_mod + 5);
        }
	break;
    }
    return true;
};

// Leader Key
void leader_start_user(void) {
    rgb_matrix_mode(RGB_MATRIX_CUSTOM_SET_LEADER_RGB);
}

void leader_end_user(void) {
    // One key sequence
    if (leader_sequence_one_key(KC_Q)) {
        // q : Quit
	SEND_STRING(SS_LALT(SS_TAP(X_F4)));
        leader_state = 1;
    } else if (leader_sequence_one_key(KC_F)) {
        // f : Open File Explorer
	SEND_STRING(SS_TAP(X_MYCM));
        leader_state = 1;
    } else if (leader_sequence_one_key(KC_C)) {
        // c : Open Calculator
	SEND_STRING(SS_TAP(X_CALC));
        leader_state = 1;
    } else if (leader_sequence_one_key(KC_T)) {
        // t : Open Task Manager
	SEND_STRING(SS_LCTL(SS_LSFT(SS_TAP(X_ESC))));
        leader_state = 1;
    } else if (leader_sequence_one_key(KC_G)) {
        // g : Game Layer
        layer_move(_GAME);
        leader_state = 1;
    } else if (leader_sequence_one_key(KC_M)) {
        // m : MIDI Scales Layer
        layer_move(_MIDI_SCALES);
        leader_state = 1;
    } else if (leader_sequence_one_key(NOTE_00)) {
        // Ionian Scale
        curr_scale = IONIAN;
        leader_state = 1;
    } else if (leader_sequence_one_key(NOTE_01)) {
        // Dorian Scale
        curr_scale = DORIAN;
        leader_state = 1;
    } else if (leader_sequence_one_key(NOTE_02)) {
        // Phrygian Scale
        curr_scale = PHRYGIAN;
        leader_state = 1;
    } else if (leader_sequence_one_key(NOTE_03)) {
        // Lydian Scale
        curr_scale = LYDIAN;
        leader_state = 1;
    } else if (leader_sequence_one_key(NOTE_04)) {
        // Mixolydian Scale
        curr_scale = MIXOLYDIAN;
        leader_state = 1;
    } else if (leader_sequence_one_key(NOTE_05)) {
        // Aeolian Scale
        curr_scale = AEOLIAN;
        leader_state = 1;
    } else if (leader_sequence_one_key(NOTE_06)) {
        // Locrian Scale
        curr_scale = LOCRIAN;
        leader_state = 1;
    } else if (leader_sequence_one_key(NOTE_07)) {
        // Pentatonic Scale
        curr_scale = PENTATONIC;
        leader_state = 1;
    } else if (leader_sequence_one_key(PITCH_U)) {
        // Reset pitch_mod
        pitch_mod = 0;
        leader_state = 1;
    } else if (leader_sequence_one_key(OCT_U)) {
        // Reset octave_mod
        octave_mod = 0;
        leader_state = 1;
    } else if (leader_sequence_one_key(VEL_U)) {
        // Reset velocity_mod
        velocity_mod = 0;
        leader_state = 1;

    // Two key sequence
    } else if (leader_sequence_two_keys(KC_M, KC_A)) {
        // ma : MIDI (All Notes) Layer
        layer_move(_MIDI_ALL);
        leader_state = 1;

    // Three key sequence
    } else if (leader_sequence_three_keys(KC_C, KC_A, KC_D)) {
        // c, a, d : Ctrl+Alt+Del
	SEND_STRING(SS_LCTL(SS_LALT(SS_TAP(X_DEL))));
        leader_state = 1;
    } else if (leader_sequence_three_keys(KC_S, KC_E, KC_T)) {
        // s, e, t : Open Settings
	SEND_STRING(SS_LGUI("i"));
        leader_state = 1;
    } else if (leader_sequence_three_keys(KC_E, KC_M, KC_A)) {
        // e, m, a : Type email address 1
	SEND_STRING("idieli1554@gmail.com");
        leader_state = 1;
    } else if (leader_sequence_three_keys(KC_E, KC_M, KC_S)) {
        // e, m, s : Type email address 2
	SEND_STRING("i.hate.grenades@gmail.com");
        leader_state = 1;
    } else if (leader_sequence_three_keys(KC_E, KC_M, KC_D)) {
        // e, m, d : Type email address 3
	SEND_STRING("pmegiasc@gmail.com");
        leader_state = 1;

    // Four key sequence
    } else if (leader_sequence_four_keys(KC_S, KC_N, KC_I, KC_P)) {
        // s, n, i, p : Partial screenshot
	SEND_STRING(SS_LGUI(SS_LSFT("s")));
        leader_state = 1;
    } else if (leader_sequence_four_keys(KC_H, KC_E, KC_L, KC_P)) {
        // h, e, l, p : Type github url
	SEND_STRING("https://github.com/idieli/qmk_firmware/tree/master/keyboards/kprepublic/cstc40/keymaps/omron");
        leader_state = 1;

    // Five key sequence
    } else if (leader_sequence_five_keys(KC_E, KC_M, KC_O, KC_J, KC_I)) {
        // e, m, o, j, i : Open Emoji Panel
	SEND_STRING(SS_LGUI("."));
        leader_state = 1;
    } else if (leader_sequence_five_keys(KC_A, KC_B, KC_O, KC_U, KC_T)) {
        // a, b, o, u, t : Open System Properties
	SEND_STRING(SS_LGUI(SS_TAP(X_PAUS)));
        leader_state = 1;

    } else {
        leader_state = 2;
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

// Layers
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
    KC_LSFT,     KC_A,         KC_S,     KC_D,     KC_F,      KC_G,    KC_H,  KC_J,      KC_K,     KC_L,     MO(_SYMB),  KC_RSFT,
    KC_ENT,      KC_Z,         KC_X,     KC_C,     KC_V,      KC_B,    KC_N,  KC_M,      KC_LEFT,  KC_DOWN,  KC_UP,      KC_RGHT,
    MO(_MEDIA),  LT(0,KC_NO),  KC_LALT,  KC_LCTL,  MO(_NUM),      KC_SPC,     MO(_NAV),  KC_RCTL,  KC_RGUI,  QK_LEAD,    MO(_FN)
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
 * |      |Prv Tr|Nxt Tr| Play |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | Vol- | Vol+ | Mute |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_MEDIA] = LAYOUT_planck_mit(
    TO(_BASE),  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
    _______,    KC_MPRV,  KC_MNXT,  KC_MPLY,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
    _______,    KC_VOLD,  KC_VOLU,  KC_MUTE,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
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
),

/* Midi Scales
 * ,-----------------------------------------------------------------------------------.
 * | BASE |      |  00  |  01  |  02  |  03  |  04  |  05  |  06  |  07  |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |  10  |  11  |  12  |  13  |  14  |  15  |  16  |  17  |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |  20  |  21  |  22  |  23  |  24  |  25  |  26  |  27  |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |Scale-|      | Vel- | Oct- |Pitch-|    Space    |Pitch+| Oct+ | Vel+ | Lead |Scale+|
 * `-----------------------------------------------------------------------------------'
 */
[_MIDI_SCALES] = LAYOUT_planck_mit(
    TO(_BASE),  XXXXXXX,  NOTE_00,  NOTE_01,  NOTE_02,  NOTE_03,  NOTE_04,  NOTE_05,  NOTE_06,  NOTE_07,  XXXXXXX,  XXXXXXX,
    XXXXXXX,    XXXXXXX,  NOTE_10,  NOTE_11,  NOTE_12,  NOTE_13,  NOTE_14,  NOTE_15,  NOTE_16,  NOTE_17,  XXXXXXX,  XXXXXXX,
    XXXXXXX,    XXXXXXX,  NOTE_20,  NOTE_21,  NOTE_22,  NOTE_23,  NOTE_24,  NOTE_25,  NOTE_26,  NOTE_27,  XXXXXXX,  XXXXXXX,
    SCALE_P,    XXXXXXX,  VEL_D,    OCT_D,    PITCH_D,        KC_SPC,       PITCH_U,  OCT_U,    VEL_U,    QK_LEAD,  SCALE_N
),

/* Midi (All Notes)
 * ,-----------------------------------------------------------------------------------.
 * |  C4  |  Cs4 |  D4  |  Ds4 |  E4  |  F4  |  Fs4 |  G4  |  Gs4 |  A4  |  As4 |  B4  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |  C3  |  Cs3 |  D3  |  Ds3 |  E3  |  F3  |  Fs3 |  G3  |  Gs3 |  A3  |  As3 |  B3  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |  C2  |  Cs2 |  D2  |  Ds2 |  E2  |  F2  |  Fs2 |  G2  |  Gs2 |  A2  |  As2 |  B2  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | BASE |      |      | Oct- |Trnps-|    Space    |Trnps+| Oct+ |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_MIDI_ALL] = LAYOUT_planck_mit(
    MI_C4,      MI_Cs4,   MI_D4,    MI_Ds4,   MI_E4,    MI_F4,  MI_Fs4,  MI_G4,    MI_Gs4,   MI_A4,    MI_As4,   MI_B4,
    MI_C3,      MI_Cs3,   MI_D3,    MI_Ds3,   MI_E3,    MI_F3,  MI_Fs3,  MI_G3,    MI_Gs3,   MI_A3,    MI_As3,   MI_B3,
    MI_C2,      MI_Cs2,   MI_D2,    MI_Ds2,   MI_E2,    MI_F2,  MI_Fs2,  MI_G2,    MI_Gs2,   MI_A2,    MI_As2,   MI_B2,
    TO(_BASE),  XXXXXXX,  XXXXXXX,  MI_OCTD,  MI_TRSD,      KC_SPC,      MI_TRSU,  MI_OCTU,  XXXXXXX,  XXXXXXX,  XXXXXXX
)


};
