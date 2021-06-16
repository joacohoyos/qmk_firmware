#include QMK_KEYBOARD_H
#include "keymap_dvp.h"
#include "keymap_spanish.h"

enum layer_number {
  _QWERTY = 0,
  _LOWER,
  _RAISE,
  _ADJUST,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

 [_QWERTY] = LAYOUT(DP_AMPR, DP_LBRC, DP_LCBR, DP_RCBR, DP_LPRN, DP_EQL, DP_ASTR, DP_RPRN, DP_PLUS, DP_RBRC, DP_EXLM, KC_BSPC, KC_TAB, DP_SCLN, DP_COMM, DP_DOT, DP_P, DP_Y, DP_F, DP_G, DP_C, DP_R, DP_L, DP_HASH, KC_LSFT, DP_A, DP_O, DP_E, DP_U, DP_I, DP_D, DP_H, DP_T, DP_N, DP_S, DP_MINS, KC_LCTL, DP_QUOT, DP_Q, DP_J, DP_K, DP_X, DP_SLSH, DP_BSLS, DP_B, DP_M, DP_W, DP_V, DP_Z, KC_RSFT, KC_LGUI, KC_LALT, MO(_LOWER), KC_ENT, KC_SPC, MO(_RAISE), KC_RALT, TG(_ADJUST)),


[_LOWER] = LAYOUT(KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_TRNS, KC_TRNS, KC_UP, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT, DP_MINS, KC_TRNS, KC_TRNS, KC_TRNS, KC_F11, KC_F12, KC_TRNS, KC_TRNS, KC_TRNS, DP_CIRC, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, MO(_ADJUST), KC_TRNS, KC_TRNS),

[_RAISE] = LAYOUT(KC_ESC, KC_TRNS, KC_TRNS, DP_ASTR, DP_SLSH, DP_MINS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, DP_7, DP_8, DP_9, DP_PLUS, KC_TRNS, KC_TRNS, KC_ESC, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, DP_0, DP_4, DP_5, DP_6, DP_COMM, KC_TRNS, KC_TRNS, KC_UP, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, DP_1, DP_2, DP_3, DP_EQL, DP_AT, KC_TRNS, KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_ENT, DP_DLR, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),

[_ADJUST] = LAYOUT(KC_EQL, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_TAB, DP_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSPC, KC_LSFT, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_ENT, KC_LCTL, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_LBRC, KC_RBRC, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_LALT, KC_LGUI, MO(_LOWER), KC_ESC, KC_SPC, MO(_RAISE), KC_RALT, TG(_ADJUST)) 

};

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

//SSD1306 OLED update loop, make sure to enable OLED_DRIVER_ENABLE=yes in rules.mk
#ifdef OLED_DRIVER_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master())
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  return rotation;
}

// When you add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);

// const char *read_mode_icon(bool swap);
// const char *read_host_led_state(void);
// void set_timelog(void);
// const char *read_timelog(void);

void oled_task_user(void) {
  if (is_keyboard_master()) {
    // If you want to change the display of OLED, you need to change here
    oled_write_ln(read_layer_state(), false);
    oled_write_ln(read_keylog(), false);
    oled_write_ln(read_keylogs(), false);
    //oled_write_ln(read_mode_icon(keymap_config.swap_lalt_lgui), false);
    //oled_write_ln(read_host_led_state(), false);
    //oled_write_ln(read_timelog(), false);
  } else {
    oled_write(read_logo(), false);
  }
}
#endif // OLED_DRIVER_ENABLE

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    #ifdef OLED_DRIVER_ENABLE
      set_keylog(keycode, record);
    #endif
    // set_timelog();
  }
  return true;
}
