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
// #define PLOOPY_DRAGSCROLL_MULTIPLIER 0.25
// #define PLOOPY_DRAGSCROLL_DPI 1000
// #define PLOOPY_DRAGSCROLL_FIXED

#define PLOOPY_DRAGSCROLL_FIXED 1
#define PLOOPY_DRAGSCROLL_DPI 100
#define PLOOPY_DPI_DEFAULT 0
#define PLOOPY_DRAGSCROLL_MOMENTARY 1

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


// enum rt_keycodes {
//     EXPOSE = PLOOPY_SAFE_RANGE,
//     EXPOSE_APP,
//     LOWER,
//     RAISE,
// };


////////////////////////////////////////////////////////////////////////////////////////////////////
// Tap dance setup                                                                                
////////////////////////////////////////////////////////////////////////////////////////////////////
// Define a type for as many tap dance states as you need
typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP
} td_state_t;
    
typedef struct {
    bool is_press_action;
    td_state_t state;
} td_tap_t;

enum {
    EXPS_LR, // Expose - Layer 
    EXAP_LR, // Expose App - Layer
};

// Declare the functions to be used with your tap dance key(s)
// Function associated with all tap dances
td_state_t cur_dance(qk_tap_dance_state_t *state);
    // Functions associated with individual tap dances
void expose_finished(qk_tap_dance_state_t *state, void *user_data);
void expose_reset(qk_tap_dance_state_t *state, void *user_data);

// extern uint16_t dpi_array[];

    

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT( /* Base */
        KC_BTN1, _______,   KC_BTN2, TD(EXPS_LR),  TD(EXAP_LR)
    ),
    [1] = LAYOUT(
        BR_BACK, _______,   BR_FWD,  _______,    _______
    ),
    [2] = LAYOUT(
        BR_PREV, _______,   BR_NEXT, _______, _______
    ),
    [3] = LAYOUT(
        DRAG_SC,  _______,  _______, _______, _______
    ),
};

// // DRAG_SCROLL
// bool process_record_user(uint16_t keycode, keyrecord_t *record) {
//     switch (keycode) {
//         case DRAG_SCROLL:
//             if (record->event.pressed) {
//                 // this toggles the state each time you tap it
//                 is_drag_scroll ^= 1;
//                 pmw_set_cpi(dpi_array[keyboard_config.dpi_config] * (is_drag_scroll ? 0.1 : 1));
//             }
//             break;
//         }
//     return true;
// }




// bool process_record_user(uint16_t keycode, keyrecord_t *record) {
//     switch (keycode) {
      // case LOWER:
      //   if (record->event.pressed) {
      //     layer_on(1);
      //     update_tri_layer(1, 2, 3);
      //   } else {
      //     layer_off(1);
      //     update_tri_layer(1, 2, 3);
      //   }
      //   return false;
      //   break;
      // case RAISE:
      //   if (record->event.pressed) {
      //     layer_on(2);
      //     update_tri_layer(1, 2, 3);
      //   } else {
      //     layer_off(2);
      //     update_tri_layer(1, 2, 3);
      //   }
      //   return false;
      //   break;
      // case EXPOSE:
      //   if (record->event.pressed) {
      //     register_code(KC_LCTL);
      //     tap_code_delay(KC_UP, 100);
      //     unregister_code(KC_LCTL);
      //   }
      //   return false;
      //   break;
      // case EXPOSE_APP:
      //   if (record->event.pressed) {
      //     register_code(KC_LCTL);
      //     tap_code_delay(KC_DOWN, 100);
      //     unregister_code(KC_LCTL);
      //   }
      //   return false;
      //   break;
      // case BTN1_LK:
      //   if (record->event.pressed) {
      //     register_code(KC_BTN1);
      //   }
      //   return false;
      //   break;
//     }
//     return true;
// }




// Determine the current tap dance state
td_state_t cur_dance(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (!state->pressed) return TD_SINGLE_TAP;
        else return TD_SINGLE_HOLD;
    } else if (state->count == 2) return TD_DOUBLE_TAP;
    else return TD_UNKNOWN;
}

    
// Initialize tap structure associated with example tap dance key
static td_tap_t expose_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};


// Initialize tap structure associated with example tap dance key
static td_tap_t app_expose_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};


// Functions that control what our tap dance key does
void expose_finished(qk_tap_dance_state_t *state, void *user_data) {
    expose_tap_state.state = cur_dance(state);
    switch (expose_tap_state.state) {
    case TD_SINGLE_TAP:
        register_code(KC_LCTL);
        tap_code_delay(KC_UP, 100);
        unregister_code(KC_LCTL);
        // tap_code(KC_QUOT);
        break;
    case TD_SINGLE_HOLD:
        layer_on(1);
        update_tri_layer(1, 2, 3);
        break;
    case TD_DOUBLE_TAP:
        // Check to see if the layer is already set
        if (layer_state_is(1)) {
        // If already set, then switch it off
            layer_off(1);
        } else {
        // If not already set, then switch the layer on
            // layer_on(_MY_LAYER);
        }
        break;
    default:
        break;
    }
}

void expose_reset(qk_tap_dance_state_t *state, void *user_data) {
// If the key was held down and now is released then switch off the layer
    if (expose_tap_state.state == TD_SINGLE_HOLD) {
        layer_off(1);
        update_tri_layer(1, 2, 3);
    }
        expose_tap_state.state = TD_NONE;
}

// Functions that control what our tap dance key does
void app_expose_finished(qk_tap_dance_state_t *state, void *user_data) {
    app_expose_tap_state.state = cur_dance(state);
    switch (app_expose_tap_state.state) {
    case TD_SINGLE_TAP:
        register_code(KC_LCTL);
        tap_code_delay(KC_DOWN, 100);
        unregister_code(KC_LCTL);
        // tap_code(KC_QUOT);
        break;
    case TD_SINGLE_HOLD:
        layer_on(2);
        update_tri_layer(1, 2, 3);
        break;
    case TD_DOUBLE_TAP:
        // Check to see if the layer is already set
        if (layer_state_is(2)) {
        // If already set, then switch it off
            layer_off(2);
        } else {
        // If not already set, then switch the layer on
            // layer_on(_MY_LAYER);
        }
        break;
    default:
        break;
    }
}

void app_expose_reset(qk_tap_dance_state_t *state, void *user_data) {
// If the key was held down and now is released then switch off the layer
    if (app_expose_tap_state.state == TD_SINGLE_HOLD) {
        layer_off(2);
        update_tri_layer(1, 2, 3);
    }
        app_expose_tap_state.state = TD_NONE;
}

// Associate our tap dance key with its functionality
qk_tap_dance_action_t tap_dance_actions[] = {
    [EXPS_LR] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, expose_finished, expose_reset, 275),
    [EXAP_LR] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, app_expose_finished, app_expose_reset, 275)
};
