#include QMK_KEYBOARD_H
#include "quantum.h"

int r_back = 200,g_back = 242,b_back = 255;
int mute_mic_cont=0;
int hide_cam_cont=0;
bool first_exec=true;
    

enum {
    TD_PLAY_STOP,
    TD_FF
};

void dance_finish_suspend(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        register_code16(KC_SYSTEM_WAKE);
        rgblight_setrgb_at(RGB_GREEN, 0);
        _delay_ms(1000);
        rgblight_setrgb_at(r_back, g_back, b_back, 0);
        
    } else {
        register_code(KC_SYSTEM_SLEEP);
        rgblight_setrgb_at(RGB_ORANGE, 0);
    }
}

void dance_reset_suspend(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        unregister_code16(KC_SYSTEM_WAKE);
        
    } else {
        unregister_code(KC_SYSTEM_SLEEP );
        
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
    [TD_FF] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_finish_suspend, dance_reset_suspend),
};


const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
	if (record->event.pressed) {
		switch(id) {
        // Mute/Unmute microphone CTRL+SHIFT+M
            case 8:

                if(mute_mic_cont % 2 == 0) {
                    rgblight_setrgb_at(RGB_RED, 8);
                }

                else {
                    rgblight_setrgb_at(RGB_GREEN, 8);
                }
        
                SEND_STRING(SS_DOWN(X_LCTRL) SS_DELAY(10) SS_DOWN(X_LSHIFT) SS_DELAY(10) SS_DOWN(X_M));
                SEND_STRING(SS_UP(X_LCTRL) SS_DELAY(10) SS_UP(X_LSHIFT) SS_DELAY(10) SS_UP(X_M));
                mute_mic_cont++;
                return false;
        // Show/Hide cam CTRL+SHIFT+O
			case 7:
                if(hide_cam_cont % 2 == 0) {
                    rgblight_setrgb_at(RGB_RED, 7);
                }

                else {
                    rgblight_setrgb_at(RGB_GREEN, 7);
                }
        
                SEND_STRING(SS_DOWN(X_LCTRL) SS_DELAY(10) SS_DOWN(X_LSHIFT) SS_DELAY(10) SS_DOWN(X_O));
                SEND_STRING(SS_UP(X_LCTRL) SS_DELAY(10) SS_UP(X_LSHIFT) SS_DELAY(10) SS_UP(X_O));
                hide_cam_cont++;
                return false;
        // Volume Down
            case 6:
                rgblight_setrgb_at(RGB_BLUE, 6);
                SEND_STRING(SS_TAP(X_AUDIO_VOL_DOWN));
                return false;
        // Previous Song
            case 5:
                rgblight_setrgb_at(RGB_ORANGE, 5);
                SEND_STRING(SS_TAP(X_MEDIA_PREV_TRACK));
                return false;
        // Next Down
            case 4:
                rgblight_setrgb_at(RGB_ORANGE, 4);
                SEND_STRING(SS_TAP(X_MEDIA_NEXT_TRACK));
                return false;
        // Volume Up
            case 3:
                rgblight_setrgb_at(RGB_BLUE, 3);
                SEND_STRING(SS_TAP(X_AUDIO_VOL_UP));
                return false;

		}
	}
	return MACRO_NONE;
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {


	LAYOUT(
    KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR, KC_HOME, KC_END,  KC_PGUP, KC_PGDN, KC_DEL,
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSLS, KC_BSPC, KC_NLCK, KC_PSLS, KC_PAST, KC_PMNS,
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,          TD(TD_PLAY_STOP),   M(0),   TD(TD_FF),   KC_PMNS,
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
    if (first_exec) {
        rgblight_setrgb_at(RGB_GREEN, 8);
        rgblight_setrgb_at(RGB_GREEN, 7);
        rgblight_setrgb_at(RGB_GREEN, 2);
        rgblight_setrgb_at(r_back, g_back, b_back, 0);
        rgblight_setrgb_at(r_back, g_back, b_back, 1);
        rgblight_setrgb_at(r_back, g_back, b_back, 3);
        rgblight_setrgb_at(r_back, g_back, b_back, 4);
        rgblight_setrgb_at(r_back, g_back, b_back, 5);
        rgblight_setrgb_at(r_back, g_back, b_back, 6);
        first_exec = false;
    }

    rgblight_setrgb_at(r_back, g_back, b_back, 0);
    rgblight_setrgb_at(r_back, g_back, b_back, 3);
    rgblight_setrgb_at(r_back, g_back, b_back, 4);
    rgblight_setrgb_at(r_back, g_back, b_back, 5);
    rgblight_setrgb_at(r_back, g_back, b_back, 6);
	return true;
}
