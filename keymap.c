#include "dz60.h"

#define MODS_CTRL_MASK  (MOD_BIT(KC_LSHIFT)|MOD_BIT(KC_RSHIFT))

#define ______ KC_TRNS

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------------.
 * | ESC |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  |  -  |  =  |   Bkspc   |
 * |-----------------------------------------------------------------------------------------+
 * | Tab    |  Q  |  W  |  E  |  R  |  T  |  Y  |  U  |  I  |  O  |  P  |  [  |  ]  |    \   |
 * |-----------------------------------------------------------------------------------------+
 * | Caps    |  A  |  S  |  D  |  F  |  G  |  H  |  J  |  K  |  L  |  ;  |  '  |    Enter    |
 * |-----------------------------------------------------------------------------------------+
 * | Shift     |  Z  |  X  |  C  |  V  |  B  |  N  |  M  |  ,  |  .  |  /  | RSh |  U  | DEL |
 * |-----------------------------------------------------------------------------------------+
 * | Ctrl |  Alt  |  Cmd  |              Space                |  Cmd |  FN |  L  |  D  |  R  |
 * `-----------------------------------------------------------------------------------------'
 */

  KEYMAP_2_SHIFTS(
      KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, ______, KC_BSPC,
      KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS,
      KC_CAPS, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT,
      KC_LSFT, ______, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_UP, KC_DEL,
      KC_LCTL, KC_LGUI,KC_LALT , KC_SPC, KC_SPC, KC_SPC, MO(2), MO(1), KC_LEFT, KC_DOWN, KC_RIGHT
      ),

/* FN Layer
 * ,-----------------------------------------------------------------------------------------.
 * | `~ | F1  | F2  | F3  | F4  | F5  | F6  | F7  | F8  | F9  | F10 |     |     |   RBGTOG   |
 * |-----------------------------------------------------------------------------------------+
 * |        |RBGM |RBGRM|     |     |     |     |     |     |     |     | Val+ | Val- |      |
 * |-----------------------------------------------------------------------------------------+
 * |  RESET  |     |     |     |     |     |     |     |     |     |     |     |             |
 * |-----------------------------------------------------------------------------------------+
 * |           |     |     |     |     |     |     |     |    |     |      |     | vol+|MUTE |
 * |-----------------------------------------------------------------------------------------+
 * |SLEEP |       |       |                                   |     |      |     | vol-|     |
 * `-----------------------------------------------------------------------------------------'
 */

  KEYMAP_DIRECTIONAL(
      KC_GRV, KC_F1 , KC_F2 , KC_F3 , KC_F4 , KC_F5 , KC_F6 , KC_F7 , KC_F8 , KC_F9 , KC_F10, ______, ______, ______, RGB_TOG,
      ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______,
      RESET, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______,	
      ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, KC_VOLU, KC_MUTE,
      KC_SLEP, ______, ______, ______, ______, ______, ______, ______, ______, KC_VOLD, ______ 
      ),

  /* FN2 Layer
 * ,-----------------------------------------------------------------------------------------.
 * |    | BL  | BL_S| BL- | BL+ |     |     |RESET|     |     |     |     |     |   RBGTOG   |
 * |-----------------------------------------------------------------------------------------+
 * |        |LClick |RClick|    |    |    |     |     |     |     |     | Val+ | Val- |      |
 * |-----------------------------------------------------------------------------------------+
 * |         | Hue+| Hue-| Sat+| Sat-|     |     |     |     |     |     |     |             |
 * |-----------------------------------------------------------------------------------------+
 * |           |     |     |     |     |     |     |     |     |     |     |     | MO+ |     |
 * |-----------------------------------------------------------------------------------------+
 * |      |       |       |                                   |     |      |L_MO | MO-| R_MO |
 * `-----------------------------------------------------------------------------------------'
 */

  KEYMAP_DIRECTIONAL(
      ______, BL_TOGG, BL_STEP, BL_DEC, BL_INC, ______, ______, RESET, ______, ______, ______, ______, ______, ______, RGB_TOG,
      ______, KC_BTN1, KC_BTN2, ______, ______, ______, ______, ______, ______, ______, ______, RGB_VAI, RGB_VAD, ______,
      ______, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, ______, ______, ______, ______, ______, ______, ______, 
      ______, ______, RGB_M_B, RGB_M_R, RGB_M_G, RGB_M_SW, RGB_M_P, RGB_M_K, ______, ______, ______, ______, ______, KC_MS_U, ______,
      ______, ______, ______, ______, ______, ______, ______, ______, KC_MS_L, KC_MS_D, KC_MS_R 
      ),
};

enum function_id {
    SHIFT_ESC,
};

const uint16_t PROGMEM fn_actions[] = {
  [0]  = ACTION_FUNCTION(SHIFT_ESC),
};

void action_function(keyrecord_t *record, uint8_t id, uint8_t opt) {
  static uint8_t shift_esc_shift_mask;
  switch (id) {
    case SHIFT_ESC:
      shift_esc_shift_mask = get_mods()&MODS_CTRL_MASK;
      if (record->event.pressed) {
        if (shift_esc_shift_mask) {
          add_key(KC_GRV);
          send_keyboard_report();
        } else {
          add_key(KC_ESC);
          send_keyboard_report();
        }
      } else {
        if (shift_esc_shift_mask) {
          del_key(KC_GRV);
          send_keyboard_report();
        } else {
          del_key(KC_ESC);
          send_keyboard_report();
        }
      }
      break;
  }
}