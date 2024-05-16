/* Copyright 2023
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

#include QMK_KEYBOARD_H

#define _BASE 0
#define _SYMB 1
#define _MEDIA 2
#define _NUM 3
#define _NAV 4
#define _FN 5

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

    // Dynamic Macro
    C_DMPLY
};

enum tap_dance_codes {
    TD_DM
};

typedef struct {
    uint16_t tap;
    uint16_t hold;
    uint16_t held;
} tap_dance_tap_hold_t;

#ifndef MAGIC_ENABLE
uint8_t mod_config(uint8_t mod) {
    return mod;
}
#endif

bool recording_dynamic_macro = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    //uint16_t macro_kc = (keycode == TD(TD_DM) ? DM_RSTP : keycode);

    //if (!process_record_dynamic_macro(macro_kc, record)) {
    /*
    if (!process_dynamic_macro(macro_kc, record)) {
        return false;
    }
    */
    /*
    if (recording_dynamic_macro) {
        uint16_t macro_kc = (keycode == TD(TD_DM) ? DM_RSTP : keycode);
        if (!process_dynamic_macro(macro_kc, record)) {
            return false;
	}
    }

    if (keycode == DM_REC1) {
        recording_dynamic_macro = true;
    }
    */

    //tap_dance_action_t *action;

    switch (keycode) {
    // Tabs
    case M_REOPT:
        if (record->event.pressed) {
	    // when keycode M_REOPT is pressed
	    SEND_STRING(SS_LCTL(SS_LSFT("t")));
	} else {
	    // when keycode M_REOPT is released
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

    // Dynamic Macros
    case TD(TD_DM):
        tap_dance_action_t *action;
        //action = &tap_dance_actions[QK_TAP_DANCE_GET_INDEX(keycode)];
        action = &tap_dance_actions[TD_INDEX(keycode)];
        if (!record->event.pressed && action->state.count && !action->state.finished) {
            tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)action->user_data;
            tap_code16(tap_hold->tap);
        }
	break;
    /*
    case DM_PLY1:
    //[TD_DM] = ACTION_TAP_DANCE_TAP_HOLD(DM_PLY1, DM_REC1)
        if (record->event.pressed) {
            uint16_t kc;
            if (recording_dynamic_macro) {
                kc = DM_RSTP;
            } else {
                kc = keycode;
	    }
            process_dynamic_macro(kc, record)
            return false;
	}
	break;
    */
    /*
    case DM_REC1:
        if (record->event.pressed) {
            recording_dynamic_macro = true;
            process_dynamic_macro(kc, record)
            return false;
	}
	break;
    */
    case C_DMPLY:
        if (record->event.pressed) {
            if (recording_dynamic_macro) {
	        SEND_STRING(SS_TAP(DM_RSTP));
            } else {
	        SEND_STRING(SS_TAP(DM_PLY1));
	    }
	}
	break;
    }
    return true;
};

// Tap Dance
void tap_dance_tap_hold_finished(tap_dance_state_t *state, void *user_data) {
    tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)user_data;

    if (state->pressed) {
        if (state->count == 1
#ifndef PERMISSIVE_HOLD
            && !state->interrupted
#endif
        ) {
            register_code16(tap_hold->hold);
            tap_hold->held = tap_hold->hold;
        } else {
            register_code16(tap_hold->tap);
            tap_hold->held = tap_hold->tap;
        }
    }
}

void tap_dance_tap_hold_reset(tap_dance_state_t *state, void *user_data) {
    tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)user_data;

    if (tap_hold->held) {
        unregister_code16(tap_hold->held);
        tap_hold->held = 0;
    }
}

#define ACTION_TAP_DANCE_TAP_HOLD(tap, hold) \
    { .fn = {NULL, tap_dance_tap_hold_finished, tap_dance_tap_hold_reset}, .user_data = (void *)&((tap_dance_tap_hold_t){tap, hold, 0}), }

tap_dance_action_t tap_dance_actions[] = {
    //[TD_DM] = ACTION_TAP_DANCE_TAP_HOLD(DM_PLY1, DM_REC1)
    [TD_DM] = ACTION_TAP_DANCE_TAP_HOLD(C_DMPLY, DM_REC1)
};

void dynamic_macro_record_start_user(int8_t direction) {
    layer_move(_BASE);
    recording_dynamic_macro = true;
}

void dynamic_macro_record_end_user(int8_t direction) {
    recording_dynamic_macro = false;
}

// Leader Sequences
void leader_start_user(void) {
    // Do something when the leader key is pressed
    // Activate RGB?
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

// Select
const uint16_t PROGMEM select_beginning_of_line[] = {KC_G, KC_LEFT, COMBO_END};
const uint16_t PROGMEM select_end_of_line[] = {KC_G, KC_RGHT, COMBO_END};
const uint16_t PROGMEM select_beginning_of_text[] = {KC_G, KC_UP, COMBO_END};
const uint16_t PROGMEM select_end_of_text[] = {KC_G, KC_DOWN, COMBO_END};
const uint16_t PROGMEM select_word[] = {KC_G, KC_W, COMBO_END};
const uint16_t PROGMEM select_line[] = {KC_G, KC_L, COMBO_END};
const uint16_t PROGMEM select_all[] = {KC_G, KC_A, COMBO_END};

combo_t key_combos[] = {
    // Select
    COMBO(select_beginning_of_line, M_SELBL),
    COMBO(select_end_of_line, M_SELEL),
    COMBO(select_beginning_of_text, M_SELBT),
    COMBO(select_end_of_text, M_SELET),
    COMBO(select_word, M_SELW),
    COMBO(select_line, M_SELL),
    COMBO(select_all, M_SELA)
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
	case TD(TD_DM):
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
    KC_ESC,      KC_Q,       KC_W,     KC_E,     KC_R,      KC_T,    KC_Y,  KC_U,      KC_I,     KC_O,     KC_P,       KC_BSPC,
    KC_LSFT,     KC_A,       KC_S,     KC_D,     KC_F,      KC_G,    KC_H,  KC_J,      KC_K,     KC_L,     TT(_SYMB),  KC_RSFT,
    KC_ENT,      KC_Z,       KC_X,     KC_C,     KC_V,      KC_B,    KC_N,  KC_M,      KC_LEFT,  KC_DOWN,  KC_UP,      KC_RGHT,
    TT(_MEDIA),  TD(TD_DM),  KC_LALT,  KC_LCTL,  TT(_NUM),      KC_SPC,     TT(_NAV),  KC_RCTL,  KC_RGUI,  QK_LEAD,    TT(_FN)   
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
 * |      |      |      |      |      |      |      |      |      |  F11 |  F12 |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |  Ins | Prtsc| Reset| Boot |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_FN] = LAYOUT_planck_mit(
    TO(_BASE),  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   _______,
    _______,    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  KC_F11,   KC_F12,   _______,
    _______,    _______,  _______,  _______,  _______,  _______,  _______,  _______,  KC_INS,   KC_PSCR,  QK_RBT,   QK_BOOT,
    _______,    _______,  _______,  _______,  _______,        _______,      _______,  _______,  _______,  _______,  _______
)

/* Midi
 * ,-----------------------------------------------------------------------------------.
 * | BASE |  C4  |  D4  |  E4  |  F4  |  G4  |  A5  |  B5  |  C5  |  D5  |  E5  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |  C3  |  D3  |  E3  |  F3  |  G3  |  A4  |  B4  |  C4  |  D4  |  E4  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |  C2  |  D2  |  E2  |  F2  |  G2  |  A3  |  B3  |  C3  |  D3  |  E3  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Oct- | Oct+ |      |      |      |             |      |      |      |Trnps-|Trnps+|
 * `-----------------------------------------------------------------------------------'
 */
/*
[_MIDI] = LAYOUT_planck_mit(
    TO(_BASE),  MI_C4,    MI_D4,    MI_E4,    MI_F4,    MI_G4,    MI_A5,    MI_B5,    MI_C5,    MI_D5,    MI_E5,    XXXXXXX,
    XXXXXXX,    MI_C3,    MI_D3,    MI_E3,    MI_F3,    MI_G3,    MI_A4,    MI_B4,    MI_C4,    MI_D4,    MI_E4,    XXXXXXX,
    XXXXXXX,    MI_C2,    MI_D2,    MI_E2,    MI_F2,    MI_G2,    MI_A3,    MI_B3,    MI_C3,    MI_D3,    MI_E3,    XXXXXXX,
    MI_OCTD,    MI_OCTU,  XXXXXXX,  XXXXXXX,  XXXXXXX,        XXXXXXX,      XXXXXXX,  XXXXXXX,  XXXXXXX,  MI_TRSD,  MI_TRSU
)
*/

};
