/* Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
 * Copyright 2019 Sunjun Kim
 * Copyright 2020 Ploopy Corporation
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

// #define PLOOPY_DPI_OPTIONS { 200, 1200, 1600, 2400 }
// #define PLOOPY_DPI_DEFAULT 0
#define OPT_SCALE 0.5
#define PLOOPY_DRAGSCROLL_MULTIPLIER 5.2

// safe range starts at `PLOOPY_SAFE_RANGE` instead.
 
// bool expose_on = false; // init expose state

// Aliases
// - Browser
# define BR_BACK  G(KC_LBRC)
# define BR_FWD   G(KC_RBRC)
# define BR_PREV  G(KC_LCBR)
# define BR_NEXT  G(KC_RCBR)
// - Scrolling
# define DRAG_SC DRAG_SCROLL


enum rt_keycodes {
    EXPOSE = PLOOPY_SAFE_RANGE,
    EXPOSE_APP,
    LOWER,
    RAISE,
    // BTN1_LK
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT( /* Base */
        KC_BTN1, _______,   KC_BTN2, LOWER,  RAISE
    ),
    [1] = LAYOUT(
        BR_BACK, DRAG_SC,   BR_FWD,  _______,    _______
    ),
    [2] = LAYOUT(
        BR_PREV, _______,   BR_NEXT, _______, _______
    ),
    [3] = LAYOUT(
        EXPOSE,  _______,   EXPOSE_APP, _______, _______
    ),
};

// DRAG_SCROLL



bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
      case LOWER:
        if (record->event.pressed) {
          layer_on(1);
          update_tri_layer(1, 2, 3);
        } else {
          layer_off(1);
          update_tri_layer(1, 2, 3);
        }
        return false;
        break;
      case RAISE:
        if (record->event.pressed) {
          layer_on(2);
          update_tri_layer(1, 2, 3);
        } else {
          layer_off(2);
          update_tri_layer(1, 2, 3);
        }
        return false;
        break;
      case EXPOSE:
        if (record->event.pressed) {
          register_code(KC_LCTL);
          tap_code_delay(KC_UP, 100);
          unregister_code(KC_LCTL);
        }
        return false;
        break;
      case EXPOSE_APP:
        if (record->event.pressed) {
          register_code(KC_LCTL);
          tap_code_delay(KC_DOWN, 100);
          unregister_code(KC_LCTL);
        }
        return false;
        break;
      // case BTN1_LK:
      //   if (record->event.pressed) {
      //     register_code(KC_BTN1);
      //   }
      //   return false;
      //   break;
    }
    return true;
}
