#include QMK_KEYBOARD_H
#include "version.h"

enum layers {
	LAYER_QWERTY, // default layer
	LAYER_NORMAN, //same as the qwerty layer, but with the alphabet in the Norman layout
	LAYER_GAMING, //a layer with arrows and other keys set to not use alternate functions, so games pick the keys up correctly
	LAYER_SYMBOLS, //symbols for programming
	LAYER_MORE_KEYS, //F keys, home/end, etc, basically moves less-used keys to easy positions
	LAYER_MEDIA, //media keys
	LAYER_NUMBERS, //moves numbers to easier positions
	LAYER_COMMANDS, //used for quickly issuing commands like alt-tab, ctrl-s, and so on
};

enum custom_keycodes {
	#ifdef ORYX_CONFIGURATOR
		VRSN = EZ_SAFE_RANGE,
	#else
		VRSN = SAFE_RANGE,
	#endif
	RGB_SLD,
	PHP_ARROW,
	BOTH_BRACKETS,
	BOTH_PARENTHESES,
	SEMICOLON_AT_LINE_END,
	LEFT_BRACE_AT_LINE_END,
	CMD_ALT_TAB,
	CMD_ALT_SHIFT_TAB,
	CMD_CTRL_TAB,
	CMD_CTRL_SHIFT_TAB,
	CMD_PREV_DESKTOP,
	CMD_NEXT_DESKTOP,
};

//Tap dance codes
enum td_keycodes {
	TD_CTRL_HOME,
	TD_CTRL_END,
	TD_ESCAPE_FLASH,
};

//tap dance states
typedef enum {
	SINGLE_TAP,
	SINGLE_HOLD,
	DOUBLE_SINGLE_TAP,
} td_state_t;

static td_state_t td_state;

//get the tap dance state
uint8_t getTapDanceState(qk_tap_dance_state_t *state);

//tap dance hooks for each of our tap dance keycodes
void ctrl_home_finished(qk_tap_dance_state_t *state, void *user_data);
void ctrl_home_reset(qk_tap_dance_state_t *state, void *user_data);
void ctrl_end_finished(qk_tap_dance_state_t *state, void *user_data);
void ctrl_end_reset(qk_tap_dance_state_t *state, void *user_data);
void handleTDEscapeFlash(qk_tap_dance_state_t *state, void *user_data);

/* The below is a template, with all transparent keys, showing which keys are where
[LAYER_NAME] = LAYOUT_ergodox_pretty(
	//row 1, left hand
	KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
	//row 1, right hand
	KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
	//row 2, left hand
	KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
	//row 2, right hand
	KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
	//row 3, left hand
	KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
	//row 3, right hand
	KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
	//row 4, left hand
	KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
	//row 4, right hand
	KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
	//row 5, left hand
	KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
	//row 5, right hand
	KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
	//top two keys, left cluster
	KC_TRNS, KC_TRNS,
	//top two keys, right cluster
	KC_TRNS, KC_TRNS,
	//center key in 3-key column, left cluster
	KC_TRNS,
	//center key in vertical	column, right cluster
	KC_TRNS,
	//last three keys, left cluster
	KC_TRNS, KC_TRNS, KC_TRNS,
	//last three keys, right cluster
	KC_TRNS, KC_TRNS, KC_TRNS
),
*/

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[LAYER_QWERTY] = LAYOUT_ergodox_pretty(
	//row 1, left hand
	KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_GRAVE,
	//row 1, right hand
	KC_CAPSLOCK, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS,
	//row 2, left hand
	KC_DEL, KC_Q, KC_W, KC_E, KC_R, KC_T, TG(LAYER_MORE_KEYS),
	//row 2, right hand
	LM(LAYER_MORE_KEYS, MOD_LCTL), KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSLS,
	//row 3, left hand
	KC_BSPC, CTL_T(KC_A), GUI_T(KC_S), ALT_T(KC_D), LT(LAYER_SYMBOLS, KC_F), LT(LAYER_COMMANDS, KC_G),
	//row 3, right hand
	LT(LAYER_COMMANDS, KC_H), LT(LAYER_SYMBOLS, KC_J), ALT_T(KC_K), GUI_T(KC_L), CTL_T(KC_SCLN), KC_QUOT,
	//row 4, left hand
	KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, LM(LAYER_MORE_KEYS, MOD_LALT),
	//row 4, right hand
	LM(LAYER_MORE_KEYS, MOD_LALT), KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT,
	//row 5, left hand
	CTL_T(KC_RGHT), GUI_T(KC_DOWN), ALT_T(KC_UP), SFT_T(KC_LEFT), KC_INSERT,
	//row 5, right hand
	LT(LAYER_MEDIA, KC_APP), SFT_T(KC_LEFT), ALT_T(KC_UP), GUI_T(KC_DOWN), CTL_T(KC_RIGHT),
	//top two keys, left cluster
	DF(LAYER_QWERTY), DF(LAYER_NORMAN),
	//top two keys, right cluster
	TD(TD_CTRL_HOME), TD(TD_CTRL_END),
	//vertical center key, outer-most column, left cluster
	DF(LAYER_GAMING),
	//vertical center key, outer-most column, right cluster
	KC_PGUP,
	//last three keys, left cluster
	LT(LAYER_MORE_KEYS, KC_TAB), LT(LAYER_NUMBERS, KC_SPACE), KC_LALT,
	//last three keys, right cluster
	KC_PGDN, LT(LAYER_NUMBERS, KC_ENTER), LT(LAYER_MORE_KEYS, KC_SPACE)
),
[LAYER_NORMAN] = LAYOUT_ergodox_pretty(
/*
q w d f k
j u r l ; [ ] \
a s e t g
y n i o h ’
z x c v b
p m , . /
*/
	//row 1, left hand
	KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
	//row 1, right hand
	KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
	//row 2, left hand
	KC_TRNS, KC_Q, KC_W, KC_D, KC_F, KC_K, KC_TRNS,
	//row 2, right hand
	KC_TRNS, KC_J, KC_U, KC_R, KC_L, KC_SCLN, KC_TRNS,
	//row 3, left hand
	KC_TRNS, CTL_T(KC_A), GUI_T(KC_S), ALT_T(KC_E), LT(LAYER_SYMBOLS, KC_T), LT(LAYER_COMMANDS, KC_G),
	//row 3, right hand
	LT(LAYER_COMMANDS, KC_Y), LT(LAYER_SYMBOLS, KC_N), ALT_T(KC_I), GUI_T(KC_O), CTL_T(KC_H), KC_TRNS,
	//row 4, left hand
	KC_TRNS, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_TRNS,
	//row 4, right hand
	KC_TRNS, KC_P, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT,
	//row 5, left hand
	KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
	//row 5, right hand
	KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
	//top two keys, left cluster
	DF(LAYER_QWERTY), DF(LAYER_NORMAN),
	//top two keys, right cluster
	TD(TD_CTRL_HOME), TD(TD_CTRL_END),
	//vertical center key, outer-most column, left cluster
	DF(LAYER_GAMING),
	//vertical center key, outer-most column, right cluster
	KC_PGUP,
	//last three keys, left cluster
	LT(LAYER_MORE_KEYS, KC_TAB), LT(LAYER_NUMBERS, KC_SPACE), KC_LALT,
	//last three keys, right cluster
	KC_PGDN, LT(LAYER_NUMBERS, KC_ENTER), LT(LAYER_MORE_KEYS, KC_SPACE)
),
[LAYER_SYMBOLS] = LAYOUT_ergodox_pretty(
	//row 1, left hand
	KC_TRNS, KC_EXCLAIM, KC_AT, KC_HASH, KC_DOLLAR, KC_PERCENT, KC_GRAVE,
	//row 1, right hand
	KC_TRNS, KC_CIRCUMFLEX, KC_AMPERSAND, KC_ASTERISK, KC_LEFT_PAREN, KC_RIGHT_PAREN, KC_UNDERSCORE,
	//row 2, left hand
	KC_TRNS, KC_TRNS, BOTH_PARENTHESES, KC_LBRACKET, KC_RBRACKET, BOTH_BRACKETS, KC_TRNS,
	//row 2, right hand
	KC_TRNS, KC_TRNS, KC_TRNS, KC_MINUS, KC_PLUS, KC_TRNS, KC_BSLS,
	//row 3, left hand
	KC_BSPC, KC_LEFT_PAREN, KC_RIGHT_PAREN, KC_LEFT_CURLY_BRACE, KC_RIGHT_CURLY_BRACE, LEFT_BRACE_AT_LINE_END,
	//row 3, right hand
	KC_UNDERSCORE, KC_DOLLAR, PHP_ARROW, KC_EQUAL, SEMICOLON_AT_LINE_END, KC_QUOT,
	//row 4, left hand
	KC_LSFT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
	//row 4, right hand
	KC_TRNS, KC_TRNS, KC_TRNS, KC_LT, KC_GT, KC_QUESTION, KC_RSFT,
	//row 5, left hand
	KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
	//row 5, right hand
	KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
	//top two keys, left cluster
	KC_TRNS, KC_TRNS,
	//top two keys, right cluster
	KC_TRNS, KC_TRNS,
	//vertical center key, outer-most column, left cluster
	KC_TRNS,
	//vertical center key, outer-most column, right cluster
	KC_TRNS,
	//last three keys, left cluster
	KC_TRNS, KC_TRNS, KC_TRNS,
	//last three keys, right cluster
	KC_TRNS, KC_TRNS, KC_TRNS
),
[LAYER_MORE_KEYS] = LAYOUT_ergodox_pretty(
	//row 1, left hand
	KC_TRNS, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6,
	//row 1, right hand
	KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_TRNS,
	//row 2, left hand
	KC_DEL, KC_Q, KC_W, KC_E, KC_R, KC_T,	KC_TRNS,
	//row 2, right hand
	KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
	//row 3, left hand
	KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6,
	//row 3, right hand
	KC_TRNS, KC_LEFT, KC_UP, KC_DOWN, KC_RIGHT, KC_TRNS,
	//row 4, left hand
	KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_TRNS,
	//row 4, right hand
	KC_TRNS, KC_RCTL, KC_HOME, KC_END, KC_PGUP, KC_PGDN, KC_TRNS,
	//row 5, left hand
	KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
	//row 5, right hand
	KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
	//top two keys, left cluster
	KC_TRNS, KC_TRNS,
	//top two keys, right cluster
	KC_TRNS, KC_TRNS,
	//vertical center key, outer-most column, left cluster
	KC_TRNS,
	//vertical center key, outer-most column, right cluster
	KC_TRNS,
	//last three keys, left cluster
	KC_TRNS, KC_TRNS, KC_TRNS,
	//last three keys, right cluster
	KC_TRNS, KC_TRNS, KC_TRNS
),
[LAYER_MEDIA] = LAYOUT_ergodox_pretty(
	//row 1, left hand
	KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
	//row 1, right hand
	KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
	//row 2, left hand
	KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
	//row 2, right hand
	KC_TRNS, KC_TRNS, KC_TRNS, KC_VOLU, KC_TRNS, KC_TRNS, KC_TRNS,
	//row 3, left hand
	KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
	//row 3, right hand
	KC_TRNS, KC_MPRV, KC_MPLY, KC_MNXT, KC_MSTP, KC_TRNS,
	//row 4, left hand
	KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
	//row 4, right hand
	KC_TRNS, KC_TRNS, KC_TRNS, KC_VOLD, KC_TRNS, KC_TRNS, KC_TRNS,
	//row 5, left hand
	KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
	//row 5, right hand
	KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
	//top two keys, left cluster
	KC_TRNS, KC_TRNS,
	//top two keys, right cluster
	KC_TRNS, KC_TRNS,
	//center key in 3-key column, left cluster
	KC_TRNS,
	//center key in vertical	column, right cluster
	KC_TRNS,
	//last three keys, left cluster
	KC_TRNS, KC_TRNS, KC_TRNS,
	//last three keys, right cluster
	KC_TRNS, KC_TRNS, KC_TRNS
),
[LAYER_NUMBERS] = LAYOUT_ergodox_pretty(
	//row 1, left hand
	KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
	//row 1, right hand
	KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
	//row 2, left hand
	KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
	//row 2, right hand
	KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
	//row 3, left hand
	KC_TRNS, KC_1, KC_2, KC_3, KC_4, KC_5,
	//row 3, right hand
	KC_6, KC_7, KC_8, KC_9, KC_0, KC_TRNS,
	//row 4, left hand
	KC_TRNS, KC_PLUS, KC_MINUS, KC_ASTERISK, KC_SLSH, KC_EQUAL, KC_TRNS,
	//row 4, right hand
	KC_TRNS, KC_EQUAL, KC_SLSH, KC_ASTERISK, KC_MINUS, KC_PLUS, KC_TRNS,
	//row 5, left hand
	KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
	//row 5, right hand
	KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
	//top two keys, left cluster
	KC_TRNS, KC_TRNS,
	//top two keys, right cluster
	KC_TRNS, KC_TRNS,
	//center key in 3-key column, left cluster
	KC_TRNS,
	//center key in vertical	column, right cluster
	KC_TRNS,
	//last three keys, left cluster
	KC_TRNS, KC_TRNS, KC_TRNS,
	//last three keys, right cluster
	KC_TRNS, KC_TRNS, KC_TRNS
),
[LAYER_COMMANDS] = LAYOUT_ergodox_pretty(
	//row 1, left hand
	KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
	//row 1, right hand
	KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
	//row 2, left hand
	KC_TRNS, KC_TRNS, KC_TRNS, CMD_CTRL_SHIFT_TAB, CMD_CTRL_TAB, KC_TRNS, KC_TRNS,
	//row 2, right hand
	KC_TRNS, KC_TRNS, CMD_CTRL_SHIFT_TAB, CMD_CTRL_TAB, KC_TRNS, KC_TRNS, KC_TRNS,
	//row 3, left hand
	KC_TRNS, KC_TRNS, KC_TRNS, CMD_ALT_SHIFT_TAB, CMD_ALT_TAB, KC_TRNS,
	//row 3, right hand
	KC_TRNS, CMD_ALT_TAB, CMD_ALT_SHIFT_TAB, KC_TRNS, KC_TRNS, KC_TRNS,
	//row 4, left hand
	KC_TRNS, KC_TRNS, KC_TRNS, CMD_PREV_DESKTOP, CMD_NEXT_DESKTOP, KC_TRNS, KC_TRNS,
	//row 4, right hand
	KC_TRNS, KC_TRNS, CMD_NEXT_DESKTOP, CMD_PREV_DESKTOP, KC_TRNS, KC_TRNS, KC_TRNS,
	//row 5, left hand
	KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
	//row 5, right hand
	KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
	//top two keys, left cluster
	KC_TRNS, KC_TRNS,
	//top two keys, right cluster
	KC_TRNS, KC_TRNS,
	//center key in 3-key column, left cluster
	KC_TRNS,
	//center key in vertical	column, right cluster
	KC_TRNS,
	//last three keys, left cluster
	KC_TRNS, KC_TRNS, KC_TRNS,
	//last three keys, right cluster
	KC_TRNS, KC_TRNS, KC_TRNS
),
[LAYER_GAMING] = LAYOUT_ergodox_pretty(
	//row 1, left hand
	KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_GRAVE,
	//row 1, right hand
	KC_CAPSLOCK, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS,
	//row 2, left hand
	KC_DEL, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_NO,
	//row 2, right hand
	KC_NO, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSLS,
	//row 3, left hand
	KC_BSPC, KC_A, KC_S, KC_D, KC_F, KC_G,
	//row 3, right hand
	KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT,
	//row 4, left hand
	KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_NO,
	//row 4, right hand
	KC_NO, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT,
	//row 5, left hand
	KC_LCTL, KC_LGUI, KC_LALT, KC_NO, KC_INSERT,
	//row 5, right hand
	LT(LAYER_MORE_KEYS, KC_APP), KC_LEFT, KC_UP, KC_DOWN, KC_RIGHT,
	//top two keys, left cluster
	DF(LAYER_QWERTY), DF(LAYER_NORMAN),
	//top two keys, right cluster
	KC_HOME, KC_END,
	//vertical center key, outer-most column, left cluster
	KC_NO,
	//vertical center key, outer-most column, right cluster
	KC_PGUP,
	//last three keys, left cluster
	KC_TAB, LT(LAYER_NUMBERS, KC_SPACE), KC_NO,
	//last three keys, right cluster
	KC_PGDN, KC_ENTER, KC_SPACE
),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	if (record->event.pressed) {
		switch (keycode) {
			case VRSN:
				SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
				return false;
			#ifdef RGBLIGHT_ENABLE
			case RGB_SLD:
				rgblight_mode(1);
				return false;
			#endif
			case PHP_ARROW:
				SEND_STRING("->");
				return false;
			case BOTH_BRACKETS:
				SEND_STRING("[]");
				return false;
			case BOTH_PARENTHESES:
				SEND_STRING("()");
				return false;
			case SEMICOLON_AT_LINE_END:
				SEND_STRING(SS_TAP(X_END)";");
				return false;
			case LEFT_BRACE_AT_LINE_END:
				SEND_STRING(SS_TAP(X_END)" {");
				return false;
			case KC_BSPC:
				//if shift is pressed with backspace, send delete instead
				if(get_mods() & MOD_BIT(KC_RSFT)) {
					unregister_code(KC_RSFT);
					tap_code(KC_DEL);
					register_code(KC_RSFT);
				} else {
					register_code(KC_BSPC);
				}
				return false;
		}
	}/* else {
		switch (keycode) {
			case KC_BSPC:
				if(get_mods() & MOD_BIT(KC_RSFT)) {
					unregister_code(KC_DEL);
				} else {
					unregister_code(KC_BSPC);
				}
				return false;
		}
	}*/
	return true;
}

// Runs just one time when the keyboard initializes.
void keyboard_post_init_user(void) {
#ifdef RGBLIGHT_COLOR_LAYER_0
	rgblight_setrgb(RGBLIGHT_COLOR_LAYER_0);
#endif
};

// Runs whenever there is a layer state change.
layer_state_t layer_state_set_user(layer_state_t state) {
	ergodox_board_led_off();
	ergodox_right_led_1_off();
	ergodox_right_led_2_off();
	ergodox_right_led_3_off();

	uint8_t layer = get_highest_layer(state);
	switch (layer) {
			case 0:
				#ifdef RGBLIGHT_COLOR_LAYER_0
					rgblight_setrgb(RGBLIGHT_COLOR_LAYER_0);
				#endif
				break;
			case 1:
				ergodox_right_led_1_on();
				#ifdef RGBLIGHT_COLOR_LAYER_1
					rgblight_setrgb(RGBLIGHT_COLOR_LAYER_1);
				#endif
				break;
			case 2:
				ergodox_right_led_2_on();
				#ifdef RGBLIGHT_COLOR_LAYER_2
					rgblight_setrgb(RGBLIGHT_COLOR_LAYER_2);
				#endif
				break;
			case 3:
				ergodox_right_led_3_on();
				#ifdef RGBLIGHT_COLOR_LAYER_3
					rgblight_setrgb(RGBLIGHT_COLOR_LAYER_3);
				#endif
				break;
			case 4:
				ergodox_right_led_1_on();
				ergodox_right_led_2_on();
				#ifdef RGBLIGHT_COLOR_LAYER_4
					rgblight_setrgb(RGBLIGHT_COLOR_LAYER_4);
				#endif
				break;
			case 5:
				ergodox_right_led_1_on();
				ergodox_right_led_3_on();
				#ifdef RGBLIGHT_COLOR_LAYER_5
					rgblight_setrgb(RGBLIGHT_COLOR_LAYER_5);
				#endif
				break;
			case 6:
				ergodox_right_led_2_on();
				ergodox_right_led_3_on();
				#ifdef RGBLIGHT_COLOR_LAYER_6
					rgblight_setrgb(RGBLIGHT_COLOR_LAYER_6);
				#endif
				break;
			case 7:
				ergodox_right_led_1_on();
				ergodox_right_led_2_on();
				ergodox_right_led_3_on();
				#ifdef RGBLIGHT_COLOR_LAYER_7
					rgblight_setrgb(RGBLIGHT_COLOR_LAYER_7);
				#endif
				break;
			default:
				break;
		}

	return state;
};

uint8_t getTapDanceState(qk_tap_dance_state_t *state) {
	if(state->count == 1) {
		if (state->interrupted || !state->pressed) return SINGLE_TAP;
		else return SINGLE_HOLD;
	}
	if (state->count == 2) return DOUBLE_SINGLE_TAP;
	else return 10; //the number doesn't matter, it just has to be more than the states we defined earlier
}

//now the hook functions for the tap dance keys we want to handle

void ctrl_home_finished(qk_tap_dance_state_t *state, void *user_data)	{
	td_state = getTapDanceState(state);
	switch(td_state) {
		case SINGLE_TAP:
			SEND_STRING(SS_TAP(X_HOME));
			break;
		case SINGLE_HOLD:
			tap_code16(LCTL(KC_HOME));
		case DOUBLE_SINGLE_TAP:
			tap_code16(LSFT(KC_HOME));
			break;
	}
}
void ctrl_home_reset(qk_tap_dance_state_t *state, void *user_data) {
	td_state = getTapDanceState(state);
	switch(td_state) {
		case SINGLE_TAP:
			break;
		case SINGLE_HOLD:
			break;
		case DOUBLE_SINGLE_TAP:
			break;
	}
}
void ctrl_end_finished(qk_tap_dance_state_t *state, void *user_data) {
	td_state = getTapDanceState(state);
	switch(td_state) {
		case SINGLE_TAP:
			SEND_STRING(SS_TAP(X_END));
			break;
		case SINGLE_HOLD:
			tap_code16(LCTL(KC_END));
			break;
		case DOUBLE_SINGLE_TAP:
			tap_code16(LSFT(KC_END));
			break;
	}
}
void ctrl_end_reset(qk_tap_dance_state_t *state, void *user_data) {
	td_state = getTapDanceState(state);
	switch(td_state) {
		case SINGLE_TAP:
			break;
		case SINGLE_HOLD:
			break;
		case DOUBLE_SINGLE_TAP:
			break;
	}
}
void handleTDEscapeFlash(qk_tap_dance_state_t *state, void *user_data) {
	switch(state->count) {
		case 1:
			tap_code16(KC_ESC);
			reset_tap_dance(state);
			break;
		case 5:
			tap_code16(RESET);
			reset_tap_dance(state);
			break;
	}
}

qk_tap_dance_action_t tap_dance_actions[] = {
	[TD_CTRL_HOME] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, ctrl_home_finished, ctrl_home_reset),
	[TD_CTRL_END] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, ctrl_end_finished, ctrl_end_reset),
	[TD_ESCAPE_FLASH] = ACTION_TAP_DANCE_FN(handleTDEscapeFlash),
};
