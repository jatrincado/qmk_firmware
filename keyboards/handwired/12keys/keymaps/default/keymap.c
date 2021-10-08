/* Copyright 2021 greyhatmiddleman
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

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE,
    _CO,
    _FN
};

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
    QMKBEST = SAFE_RANGE,
    QMKURL
};

enum tap_dance_codes {
  DANCE_0,
  DANCE_1,
  DANCE_2
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_BASE] = LAYOUT_ortho_3x4(
        KC_MUTE, KC_VOLD, KC_VOLU, TD(DANCE_2),
        KC_NO  , KC_NO  , KC_NO  , TD(DANCE_1),
        MO(_CO), _______, _______, MO(_FN)

    ),
    [_CO] = LAYOUT_ortho_3x4(
        KC_NO  , KC_NO  , KC_NO  , KC_NO  ,
        KC_NO  , KC_NO  , KC_NO  , KC_NO  ,
        KC_TRNS, KC_NO  , KC_NO  , KC_NO
    ),
    [_FN] = LAYOUT_ortho_3x4(
        QMKBEST, QMKURL,  _______, RESET  ,
        _______, KC_SPC , XXXXXXX, _______,
        _______, _______, _______, _______
    )
};


// using the pro micro led indicators
bool led_update_user(led_t led_state) {
    switch (get_highest_layer(layer_state)) {
      case _BASE:
        writePinHigh(B0);
        writePinHigh(D5);
        break;
      case _CO:
        writePinLow(B0);
        writePinHigh(D5);
        break;
      case _FN:
        writePinHigh(B0);
        writePinLow(D5);
        break;
      default:
        writePinHigh(B0);
        writePinHigh(D5);
        break;
    }
    return true;
}


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case QMKBEST:
            if (record->event.pressed) {
                // when keycode QMKBEST is pressed
                SEND_STRING("QMK is the best thing ever!");
            } else {
		//testfn();
		SEND_STRING_DELAY(" testing TESTING", 200);
                // when keycode QMKBEST is released
            }
            break;
        case QMKURL:
            if (record->event.pressed) {
                // when keycode QMKURL is pressed
                SEND_STRING("https://qmk.fm/\n");
            } else {
                // when keycode QMKURL is released
            }
            break;
    }
    return true;
}


// Tap Dance
typedef struct {
    bool is_press_action;
    uint8_t step;
} tap;

enum {
    SINGLE_TAP = 1,
    SINGLE_HOLD,
    DOUBLE_TAP,
    DOUBLE_HOLD,
    DOUBLE_SINGLE_TAP,
    MORE_TAPS
};

static tap dance_state = {
    .is_press_action = true,
    .step = 0
};

uint8_t dance_step(qk_tap_dance_state_t *state);

uint8_t dance_step(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return SINGLE_TAP;
        else return SINGLE_HOLD;
    } else if (state->count == 2) {
        if (state->interrupted) return DOUBLE_SINGLE_TAP;
        else if (state->pressed) return DOUBLE_HOLD;
        else return DOUBLE_TAP;
    }
    return MORE_TAPS;
}

// DANCE_0
void on_dance_0(qk_tap_dance_state_t *state, void *user_data);
void dance_0_finished(qk_tap_dance_state_t *state, void *user_data);
void dance_0_reset(qk_tap_dance_state_t *state, void *user_data);

void on_dance_0(qk_tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(LALT(LSFT(KC_GRAVE)));
        tap_code16(LALT(LSFT(KC_GRAVE)));
        tap_code16(LALT(LSFT(KC_GRAVE)));
    }
    if(state->count > 3) {
        tap_code16(LALT(LSFT(KC_GRAVE)));
    }
}

void dance_0_finished(qk_tap_dance_state_t *state, void *user_data) {
    dance_state.step = dance_step(state);
    switch (dance_state.step) {
        case SINGLE_TAP: register_code16(LALT(LSFT(KC_GRAVE))); break;
        case SINGLE_HOLD: register_code16(KC_LCTRL); break;
        case DOUBLE_TAP: register_code16(LALT(LSFT(KC_GRAVE))); register_code16(LALT(LSFT(KC_GRAVE))); break;
        case DOUBLE_SINGLE_TAP: tap_code16(LALT(LSFT(KC_GRAVE))); register_code16(LALT(LSFT(KC_GRAVE)));
    }
}

void dance_0_reset(qk_tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state.step) {
        case SINGLE_TAP: unregister_code16(LALT(LSFT(KC_GRAVE))); break;
        case SINGLE_HOLD: unregister_code16(KC_LCTRL); break;
        case DOUBLE_TAP: unregister_code16(LALT(LSFT(KC_GRAVE))); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(LALT(LSFT(KC_GRAVE))); break;
    }
    dance_state.step = 0;
}


// DANCE_1
void on_dance_1(qk_tap_dance_state_t *state, void *user_data);
void dance_1_finished(qk_tap_dance_state_t *state, void *user_data);
void dance_1_reset(qk_tap_dance_state_t *state, void *user_data);

void on_dance_1(qk_tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_Z);
        tap_code16(KC_Z);
        tap_code16(KC_Z);
    }
    if(state->count > 3) {
        tap_code16(KC_Z);
    }
}

void dance_1_finished(qk_tap_dance_state_t *state, void *user_data) {
    dance_state.step = dance_step(state);
    switch (dance_state.step) {
        case SINGLE_TAP: register_code16(KC_Z); break;
        case SINGLE_HOLD: register_code16(KC_LALT); break;
        case DOUBLE_TAP: register_code16(KC_Z); register_code16(KC_Z); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_Z); register_code16(KC_Z);
    }
}

void dance_1_reset(qk_tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state.step) {
        case SINGLE_TAP: unregister_code16(KC_Z); break;
        case SINGLE_HOLD: unregister_code16(KC_LALT); break;
        case DOUBLE_TAP: unregister_code16(KC_Z); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_Z); break;
    }
    dance_state.step = 0;
}


// DANCE_2
void on_dance_2(qk_tap_dance_state_t *state, void *user_data);
void dance_2_finished(qk_tap_dance_state_t *state, void *user_data);
void dance_2_reset(qk_tap_dance_state_t *state, void *user_data);

void on_dance_2(qk_tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_QUOT);
        tap_code16(KC_QUOT);
        tap_code16(KC_QUOT);
    }
    if(state->count > 3) {
        tap_code16(KC_QUOT);
    }
}

void dance_2_finished(qk_tap_dance_state_t *state, void *user_data) {
    dance_state.step = dance_step(state);
    switch (dance_state.step) {
        //case SINGLE_TAP: SEND_STRING(SS_TAP(X_G) SS_DELAY(100) SS_TAP(X_G)); break;
        case SINGLE_TAP: register_code16(KC_QUOT); break;
        case SINGLE_HOLD: SEND_STRING(SS_LSFT(SS_TAP(X_QUOT))); break;
        case DOUBLE_TAP: SEND_STRING(SS_TAP(X_QUOT) SS_DELAY(100) SS_TAP(X_QUOT) SS_DELAY(100) SS_TAP(X_LEFT)); break;
        case DOUBLE_HOLD: SEND_STRING(SS_LSFT(SS_TAP(X_QUOT)) SS_DELAY(100) SS_LSFT(SS_TAP(X_QUOT)) SS_DELAY(100) SS_TAP(X_LEFT));
    }
}

void dance_2_reset(qk_tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state.step) {
        case SINGLE_TAP: unregister_code16(KC_QUOT); break;
	case SINGLE_HOLD: break;
        case DOUBLE_TAP: break;
        case DOUBLE_HOLD: break;
    }
    dance_state.step = 0;
}




// must stay below
qk_tap_dance_action_t tap_dance_actions[] = {
        [DANCE_0] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_0, dance_0_finished, dance_0_reset),
	[DANCE_1] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_1, dance_1_finished, dance_1_reset),
	[DANCE_2] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_2, dance_2_finished, dance_2_reset),
};


