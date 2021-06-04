#include QMK_KEYBOARD_H
#include "quantum.h"

int r_back, g_back, b_back;

enum {
    TD_PLAY_STOP,
    TD_FF
};

void dance_finish_ff(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        register_code16(KC_MEDIA_NEXT_TRACK);
        rgblight_setrgb_at(RGB_BLUE, 1);
    } else {
        register_code(KC_MEDIA_PREV_TRACK);
        rgblight_setrgb_at(RGB_ORANGE, 1);
    }
}

void dance_reset_ff(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        unregister_code16(KC_MEDIA_NEXT_TRACK);
        rgblight_setrgb_at(r_back, g_back, b_back, 1);
    } else {
        unregister_code(KC_MEDIA_PREV_TRACK);
        rgblight_setrgb_at(r_back, g_back, b_back, 1);
    }
}

void dance_finish_play(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        register_code16(KC_MEDIA_PLAY_PAUSE);
        rgblight_setrgb_at(RGB_GREEN, 2);
    } else {
        register_code(KC_MEDIA_STOP);
        rgblight_setrgb_at(RGB_RED, 2);
    }
}

void dance_reset_play(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        unregister_code16(KC_MEDIA_PLAY_PAUSE);
    } else {
        unregister_code(KC_MEDIA_STOP);
    }
}

// All tap dance functions would go here. Only showing this one.
qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_PLAY_STOP] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_finish_play, dance_reset_play),
    [TD_FF] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_finish_ff, dance_reset_ff),
};


const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
	if (record->event.pressed) {
		switch(id) {
        // Mute microphone CTRL+F9
			case 8:
        rgblight_setrgb_at(RGB_RED, 7);
        rgblight_setrgb_at(RGB_RED, 8);
        SEND_STRING(SS_DOWN(X_LCTRL) SS_DELAY(10) SS_DOWN(X_F9) SS_DELAY(10));
        SEND_STRING(SS_UP(X_LCTRL) SS_DELAY(10) SS_UP(X_F9));
        return false;
        // Unmute microphone CTRL+F10
			case 7:
        rgblight_setrgb_at(RGB_GREEN, 7);
        rgblight_setrgb_at(RGB_GREEN, 8);
        SEND_STRING(SS_DOWN(X_LCTRL) SS_DELAY(10) SS_DOWN(X_F10) SS_DELAY(10));
        SEND_STRING(SS_UP(X_LCTRL) SS_DELAY(10) SS_UP(X_F10));
        return false;
        // Volume Down
            case 6:
        rgblight_setrgb_at(RGB_BLUE, 6);
        SEND_STRING(SS_TAP(X__VOLDOWN));
        return false;
        // Volume Up
            case 3:
        rgblight_setrgb_at(RGB_BLUE, 3);
        SEND_STRING(SS_TAP(X__VOLUP));
        return false;




		}
	}
	return MACRO_NONE;
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {


	LAYOUT(
    KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR, KC_HOME, KC_END,  KC_PGUP, KC_PGDN, KC_DEL,
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSLS, KC_BSPC, KC_NLCK, KC_PSLS, KC_PAST, KC_PMNS,
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,          TD(TD_PLAY_STOP),   TD(TD_FF),   M(0),   KC_PMNS,
    KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,                    M(5),   M(4),   M(3),   KC_PPLS,
    KC_LSFT, KC_NUBS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,          KC_UP,   M(8),   M(7),   M(6),   KC_PENT,
    KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT, MO(1),   MO(1),   KC_LEFT, KC_DOWN, KC_RGHT, KC_P0,   KC_PDOT, KC_PENT),



  /* Layer 1, function layer
____________________________________________________________________________________________________________________________________________________________________________
|        |        |        |        |        |        |        |        |        |        |        |        |        |        |  VOL   |  VOL   |        |        |        |
| RESET  |        |        |        |        |        |        |        |        |        |        |        |        | MUTE   |  DOWN  |   UP   |        |        |        |
|________|________|________|________|________|________|________|________|________|________|________|________|________|________|________|________|________|________|________|
|        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
|        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
|________|________|________|________|________|________|________|________|________|________|________|________|________|________|________|________|________|________|________|
|            |  RGB   |        |  RGB   |  HUE   |  HUE   | SATUR. | SATUR. | VALUE  | VALUE  |        |        |        |             |        |        |        |        |
|            | TOGGLE |        |  MODE  |INCREASE| DCRSE  |INCREASE| DCRSE  |INCREASE| DCRSE  |        |        |        |             |        |        |        |        |
|____________|________|________|________|________|________|________|________|________|________|________|________|________|_____________|________|________|________|________|
| BACKLIGHT    |        |        |        |        |        |        |        |        |        |        |        |                    |        |        |        |        |
| TOGGLE       |        |        |        |        |        |        |        |        |        |        |        |                    |        |        |        |        |
|______________|________|________|________|________|________|________|________|________|________|________|________|____________________|________|________|________|________|
|         |        |        |        |BACKLHT |BACKLHT |BACKLHT |        |        |        |        |        |                |        |        |        |        |        |
|         |        |        |        | DCRSE  |TOGGLE  |INCREASE|        |        |        |        |        |                |        |        |        |        |        |
|_________|________|________|________|________|________|________|________|________|________|________|________|________________|________|________|________|________|________|
|          |          |          |                                                        |        |        |        |        |        |        |        |        |        |
|          |          |          |                                                        |        |        |        |        |        |        |        |        |        |
|__________|__________|__________|________________________________________________________|________|________|________|________|________|________|________|________|________|
BL_TOGG, BL_DEC, BL_INC changes the in-switch LEDs
*/


	LAYOUT(
    RESET,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_MUTE, KC_VOLD, KC_VOLU, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, RGB_TOG, _______, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, _______, _______, _______, _______,          _______, _______, _______, _______,
    BL_TOGG, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______,
    _______, _______, _______, _______, BL_DEC,  BL_TOGG, BL_INC,  _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______,
    _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______, _______, _______, _______, _______),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    //rgblight_setrgb(200,242,255);
    r_back = 200;
    g_back = 242;
    b_back = 255;
    rgblight_setrgb_at(r_back, g_back, b_back, 0);
    rgblight_setrgb_at(r_back, g_back, b_back, 1);
    rgblight_setrgb_at(r_back, g_back, b_back, 3);
    rgblight_setrgb_at(r_back, g_back, b_back, 4);
    rgblight_setrgb_at(r_back, g_back, b_back, 5);
    rgblight_setrgb_at(r_back, g_back, b_back, 6);
	return true;
}
