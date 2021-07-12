/* Copyright 2015-2017 Jack HumbertN
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
#include "muse.h"
#ifdef AUDIO_ENABLE
    #include "audio.h"
#endif
#include "alias.h"

// ////////////////////////////////////////////////////////////////////////////////
// // Tap dance
// ////////////////////////////////////////////////////////////////////////////////
// enum {
//     TD_ESC_CAPS,
// };

// // Tap Dance definitions
// qk_tap_dance_action_t tap_dance_actions[] = {
//     // Tap once for Escape, twice for Caps Lock
//     [TD_ESC_CAPS] = ACTION_TAP_DANCE_DOUBLE(KC_ESC, KC_CAPS),
// };




////////////////////////////////////////////////////////////////////////////////
// Audio stuff
////////////////////////////////////////////////////////////////////////////////
float tone_qwerty[][2]             = SONG(QWERTY_SOUND);
float tone_colemak[][2]            = SONG(COLEMAK_SOUND);
float tone_dvorak[][2]             = SONG(DVORAK_SOUND);
float tone_beakl[][2]              = SONG(ZELDA_TREASURE);
float tone_prog_on[][2]            = SONG(MARIO_MUSHROOM);
float tone_prog_off[][2]           = SONG(CLOSE_ENCOUNTERS_5_NOTE);
float tone_caps_lock[][2]          = SONG(COIN_SOUND);
float tone_tenkey_activate[][2]    = SONG(GUITAR_SOUND);
float tone_tenkey_deactivate[][2]  = SONG(GUITAR_SOUND_DOWN);

////////////////////////////////////////////////////////////////////////////////
// Layers
////////////////////////////////////////////////////////////////////////////////
enum preonic_layers {
  _QWERTY,
  _COLEMAK,
  _DVORAK,
  _BEAKL15,
  _HANDSDOWN,
  _PROGRAMMER,
  _LOWER,
  _RAISE,
  _MOUSE,
  _MOVEMENT,
  _TENKEY,
  _FUNCTIONS,
  _ADJUST
};

enum preonic_keycodes {
  // BASE = SAFE_RANGE,
  QWERTY = SAFE_RANGE,
  COLEMAK,
  DVORAK,
  HANDDWN,
  BEAKL15,
  PROG_ON,
  PROG_OFF,
  LOWER,
  RAISE,
  BACKLIT,
  TB_SCRL,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  |  "   |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |Esc/Mo|   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |Enter |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Shift |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Func | Mouse| Btn1 | Btn2 |Lower | Space/Arrow |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
// KC_DEL: DE
// BACKLIT: Brite

[_QWERTY] = LAYOUT_preonic_grid(
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,   KC_5,   KC_6,   KC_7,   KC_8,    KC_9,    KC_0,      KC_BSPC,
  KC_TAB,  KC_Q,    KC_W,    KC_E,    QWRT_R, KC_T,   KC_Y,   KC_U,   KC_I,    KC_O,    KC_P,      KC_QUOT, 
  ESC_MO,  QWRT_A,  QWRT_S,  QWRT_D,  QWRT_F, QWRT_G, KC_H,   QWRT_J, QWRT_K,  QWRT_L,  QWRT_SCLN, KC_ENT,
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM, KC_DOT,  KC_SLSH,   KC_RSFT,
  FUNC_MO, TB_SCRL, KC_BTN1, KC_BTN2, LOWER,  SPC_MV, SPC_MV, RAISE,  KC_LEFT, KC_DOWN, KC_UP,     KC_RGHT
),

/* Colemak
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   F  |   P  |   G  |   J  |   L  |   U  |   Y  |   ;  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |Esc/Mo|   A  |   R  |   S  |   T  |   D  |   H  |   N  |   E  |   I  |   O  |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   K  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Func | Mouse|      |      |Lower | Space/Arrow |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_COLEMAK] = LAYOUT_preonic_grid(
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,  KC_5,   KC_6,   KC_7,  KC_8,    KC_9,    KC_0,    KC_BSPC,
  KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,  KC_G,   KC_J,   KC_L,  KC_U,    KC_Y,    KC_SCLN, KC_DEL,
  ESC_MO,  KC_A,    KC_R,    KC_S,    KC_T,  KC_D,   KC_H,   KC_N,  KC_E,    KC_I,    KC_O,    KC_QUOT,
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,  KC_B,   KC_K,   KC_M,  KC_COMM, KC_DOT,  KC_SLSH, KC_ENT,
  FUNC_MO, MOUS_MO, _______, _______, LOWER, SPC_MV, SPC_MV, RAISE, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
),

/* Dvorak
 ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   "  |   ,  |   .  |   P  |   Y  |   F  |   G  |   C  |   R  |   L  | /    |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |Esc/Mo|   A  |   O  |   E  |   U  |   I  |   D  |   H  |   T  |   N  |   S  |Enter |
 * |------+------+------+------+------+------|------+------+------+------+------+-----
 * | Shift|   ;  |   Q  |   J  |   K  |   X  |   B  |   M  |   W  |   V  |   Z  |Shift |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Func | Mouse|      |      |Lower | Space/Arrow |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */

[_DVORAK] = LAYOUT_preonic_grid(
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,   KC_5,   KC_6,   KC_7,   KC_8,    KC_9,    KC_0,   KC_BSPC,
  KC_TAB,  KC_QUOT, KC_COMM, KC_DOT,  DVRK_P, KC_Y,   KC_F,   KC_G,   KC_C,    KC_R,    KC_L,   KC_SLSH,
  ESC_MO,  DVRK_A,  DVRK_O,  DVRK_E,  DVRK_U, DVRK_I, KC_D,   DVRK_H, DVRK_T,  DVRK_N,  DVRK_S, KC_ENT,
  KC_LSFT, KC_SCLN, KC_Q,    KC_J,    KC_K,   KC_X,   KC_B,   KC_M,   KC_W,    KC_V,    KC_Z,   KC_RSFT,
  FUNC_MO, MOUS_MO, _______, _______, LOWER,  SPC_MV, SPC_MV, RAISE,  KC_LEFT, KC_DOWN, KC_UP,  KC_RGHT
),

/* Beakl 15 (https://deskthority.net/wiki/BEAKL)
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   Q  |   H  |   O  |   U  |   X  |   G  |   C  |   R  |   F  |   Z  | ;    |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |Esc/Mo|   Y  |   I  |   E  |   A  |   .  |   D  |   S  |   T  |   N  |   B  |Enter |
 * |------+------+------+------+------+------|------+------+------+------+------+-----
 * | Shift|   J  |   /  |   ,  |   K  |   "  |   W  |   M  |   L  |   P  |   V  |Shift |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Func | Mouse|10 Key|      |Lower | Space/Arrow |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_BEAKL15] = LAYOUT_preonic_grid(
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,   KC_5,    KC_6,   KC_7,  KC_8,    KC_9,    KC_0,   KC_BSPC,
  KC_TAB,  KC_Q,    KC_H,    KC_O,    BEKL_U, KC_X,    KC_G,   KC_C,  KC_R,    KC_F,    KC_Z,   KC_SCLN,    
  ESC_MO,  BEKL_Y,  BEKL_I,  BEKL_E,  BEKL_A, BEKLDT,  KC_D,   BEKL_S, BEKL_T, BEKL_N,  BEKL_B, KC_ENT, 
  KC_LSFT, KC_J,    KC_SLSH, KC_COMM, KC_K,   KC_QUOT, KC_W,   KC_M,  KC_L,    KC_P,    KC_V,   KC_RSFT,  
  FUNC_MO, MOUS_MO, _______, _______, LOWER,  SPC_MV,  SPC_MV, RAISE, KC_LEFT, KC_DOWN, KC_UP,  KC_RGHT
  ),

/* Hands Down (https://https://sites.google.com/alanreiser.com/handsdown)
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   Q  |   C  |   H  |   P  |   V  |   K  |   Y  |   O  |   J  |   /  | ;    |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |Esc/Mo|   R  |   S  |   N  |   T  |   G  |   W  |   U  |   E  |   I  |   A  |Enter |
 * |------+------+------+------+------+------|------+------+------+------+------+-----
 * | Shift|   X  |   M  |   L  |   D  |   B  |   Z  |   F  |   '  |   ,  |   .  |Shift |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Func | Mouse|10 Key|      |Lower | Space/Arrow |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */

[_HANDSDOWN] = LAYOUT_preonic_grid(
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,   KC_5,    KC_6,   KC_7,   KC_8,    KC_9,    KC_0,    KC_BSPC,
  KC_TAB,  KC_Q,    KC_C,    KC_H,    HNDS_P, KC_V,    KC_K,   KC_Y,   KC_O,    KC_J,    KC_SLSH, KC_SCLN,    
  ESC_MO,  HNDS_R,  HNDS_S,  HNDS_N,  HNDS_T, HNDS_G,  KC_W,   HNDS_U, HNDS_E,  HNDS_I,  HNDS_A,  KC_ENT, 
  KC_LSFT, KC_X,    KC_M,    KC_L,    KC_D,   KC_B,    KC_Z,   KC_F,   KC_QUOT, KC_COMM, KC_DOT,  KC_RSFT,  
  FUNC_MO, MOUS_MO, _______, _______, LOWER,  SPC_MV,  SPC_MV, RAISE,  KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
  ),

/* Programmer
 * ,-----------------------------------------------------------------------------------.
 * |      |   !  |   @  |  #   |  $   |  %   |  ^   |  &   |  *   |  (   |  )   |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_PROGRAMMER] = LAYOUT_preonic_grid(
  _______, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |   <  |   +  |   >  |      |      |   [  |   =  |   ]  |      | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Del  |      |   (  |   -  |   )  |      |      |   {  |   _  |   }  |  |   |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |  \   |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |     Del     |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_preonic_grid(
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  _______, _______, KC_LT,   KC_PLUS, KC_GT,   _______, _______, KC_LBRC, KC_EQL,  KC_RBRC, _______, KC_DEL, 
  KC_DEL,  _______, KC_LPRN, KC_MINS, KC_RPRN, _______, _______, KC_LCBR, KC_UNDS, KC_RCBR, KC_PIPE, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_BSLS, _______,
  _______, _______, _______, _______, _______, KC_DEL,  KC_DEL,  _______, _______, _______, _______, _______
),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |   <  |   +  |   >  |      |      |   [  |   =  |   ]  |      | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Del  |      |   (  |   -  |   )  |      |      |   {  |   _  |   }  |  |   |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |  \   |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |    Bksp     |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
 
[_RAISE] = LAYOUT_preonic_grid(
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  _______, _______, KC_LT,   KC_PLUS, KC_GT,   _______, _______, KC_LBRC, KC_EQL,  KC_RBRC, _______, KC_DEL, 
  KC_DEL,  _______, KC_LPRN, KC_MINS, KC_RPRN, _______, _______, KC_LCBR, KC_UNDS, KC_RCBR, KC_PIPE, _______, 
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_BSLS, _______,
  _______, _______, _______, _______, _______, KC_BSPC, KC_BSPC, _______, _______, _______, _______, _______
),


/* Movement
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      | Prev | Next |      | Home | Pg Dn| Pg Up| End  |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      | Left | Down |  Up  |Right |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      | Back | Fwd  |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_MOVEMENT] = LAYOUT_preonic_grid(
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, 
  _______, _______, _______, KC_PREV, KC_NEXT, _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END,  _______, _______, 
  _______, _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______, 
  _______, _______, _______, KC_BACK, KC_FWD,  _______, _______, _______, _______, _______, _______, _______, 
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ 
),

/* Tenkey
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |Clear |  /   |  *   |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |  /   |  7   |  8   |  9   |  *   |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |  -   |  4   |  5   |  6   |  +   |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      | Tab  |  1   |  2   |  3   |  .   |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      0      |  0   |  0   |  .   |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_TENKEY] = LAYOUT_preonic_grid(
  _______, _______, _______, _______, _______, _______, _______, KC_CLEAR, KC_SLSH, KC_ASTR, _______, _______, 
  _______, _______, _______, _______, _______, _______, KC_SLSH, KC_7,     KC_8,    KC_9,    KC_ASTR, _______, 
  _______, _______, _______, _______, _______, _______, KC_MINS, KC_4,     KC_5,    KC_6,    KC_PLUS, _______, 
  _______, _______, _______, _______, _______, _______, KC_TAB,  KC_1,     KC_2,    KC_3,    KC_DOT,  _______, 
  _______, _______, _______, _______, _______, KC_0,     KC_0,   KC_0,     KC_0,    KC_DOT,  _______, _______ 
),

/* Mouse
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |Speed0|Speed1|Speed2|      |      | Btn1 |  Up  | Btn2 | Btn2 |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |      | Left | Down | Right| Btn1 |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |Speed0|Speed1|Speed2|      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_MOUSE] = LAYOUT_preonic_grid(
  _______, _______, _______,      _______,      _______,      _______, _______, _______, _______, _______, _______, _______, 
  _______, _______, KC_MS_ACCEL0, KC_MS_ACCEL1, KC_MS_ACCEL2, _______, _______, KC_BTN1, KC_MS_U, KC_BTN2, KC_BTN2, _______, 
  _______, _______, _______,      _______,      _______,      _______, _______, KC_MS_L, KC_MS_D, KC_MS_R, KC_BTN1, _______, 
  _______, _______, KC_MS_ACCEL0, KC_MS_ACCEL1, KC_MS_ACCEL2, _______, _______, _______, _______, _______, _______, _______, 
  _______, _______, _______,      _______,      _______,      _______, _______, _______, _______, _______, _______, _______ 
),

/* Functions
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  | Pg Dn| Pg Up|   [  |   ]  |  \   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |ISO # |      |      | Vol+ | Mute |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Prev | Next | Vol- | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_FUNCTIONS] = LAYOUT_preonic_grid(
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL,
  KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_PGDN, KC_PGUP, KC_LBRC, KC_RBRC, KC_BSLS,
  _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_NUHS, KC_NUBS, _______, KC_VOLU, KC_MUTE,
  _______, _______, _______, _______, _______, _______, _______, _______, KC_MPRV, KC_MNXT, KC_VOLD, KC_MPLY
),


/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | Reset| Debug|      |      |      |      |TermOf|TermOn|      |      |      |  
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |Aud cy|Aud on|AudOff|AGnorm|AGswap|Qwerty|Colemk|Dvorak| BEAKL|      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |Voice-|Voice+|Mus on|MusOff|MidiOn|MidOff|PrgOn |PrgOff|      |Backlt|      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_preonic_grid(
  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,    KC_F10,  KC_F11,  KC_F12,
  _______, RESET,   DEBUG,   KC_LSCR, KC_SLCK, _______, _______, TERM_ON, TERM_OFF, _______, _______, _______,
  _______, _______, MU_MOD,  AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, QWERTY,  COLEMAK,  DVORAK,  HANDDWN, _______,
  _______, MUV_DE,  MUV_IN,  MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  PROG_ON, PROG_OFF, _______, BACKLIT, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______
),

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
        case QWERTY:
          if (record->event.pressed) {
            // set_single_persistent_default_layer(_QWERTY);
            default_layer_set(_QWERTY);
            layer_on(_QWERTY);
            layer_off(_COLEMAK);
            layer_off(_DVORAK);
            layer_off(_BEAKL15);
            layer_off(_HANDSDOWN);
            #ifdef AUDIO_ENABLE
                PLAY_SONG(tone_qwerty);
            #endif //AUDIO_ENABLE
          }
          return false;
          break;
        case COLEMAK:
          if (record->event.pressed) {
            // set_single_persistent_default_layer(_COLEMAK);
            default_layer_set(_QWERTY);
            layer_off(_QWERTY);
            layer_on(_COLEMAK);
            layer_off(_DVORAK);
            layer_off(_BEAKL15);
            layer_off(_HANDSDOWN);
            #ifdef AUDIO_ENABLE
                PLAY_SONG(tone_colemak);
            #endif //AUDIO_ENABLE
          }
          return false;
          break;
        case DVORAK:
          if (record->event.pressed) {
            // set_single_persistent_default_layer(_DVORAK);
            default_layer_set(_DVORAK);
            layer_off(_QWERTY);
            layer_off(_COLEMAK);
            layer_on(_DVORAK);
            layer_off(_BEAKL15);
            layer_off(_HANDSDOWN);
            #ifdef AUDIO_ENABLE
                PLAY_SONG(tone_dvorak);
            #endif //AUDIO_ENABLE
          }
          return false;
          break;
        case BEAKL15:
          if (record->event.pressed) {
            // set_single_persistent_default_layer(_BEAKL15);
            default_layer_set(_BEAKL15);
            layer_off(_QWERTY);
            layer_off(_COLEMAK);
            layer_off(_DVORAK);
            layer_on(_BEAKL15);
            layer_off(_HANDSDOWN);
            #ifdef AUDIO_ENABLE
                PLAY_SONG(tone_beakl);
            #endif //AUDIO_ENABLE
          }
          return false;
          break;
        case HANDDWN:
          if (record->event.pressed) {
            // set_single_persistent_default_layer(_BEAKL15);
            default_layer_set(_HANDSDOWN);
            layer_off(_QWERTY);
            layer_off(_COLEMAK);
            layer_off(_DVORAK);
            layer_off(_BEAKL15);
            layer_on(_HANDSDOWN);
            #ifdef AUDIO_ENABLE
                PLAY_SONG(tone_beakl);
            #endif //AUDIO_ENABLE
          }
          return false;
          break;
        case LOWER:
          if (record->event.pressed) {
            layer_on(_LOWER);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          } else {
            layer_off(_LOWER);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          }
          return false;
          break;
        case RAISE:
          if (record->event.pressed) {
            layer_on(_RAISE);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          } else {
            layer_off(_RAISE);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          }
          return false;
          break;
        case BACKLIT:
          if (record->event.pressed) {
            register_code(KC_RSFT);
            #ifdef BACKLIGHT_ENABLE
              backlight_step();
            #endif
            #ifdef __AVR__
            writePinLow(E6);
            #endif
          } else {
            unregister_code(KC_RSFT);
            #ifdef __AVR__
            writePinHigh(E6);
            #endif
          }
          return false;
          break;        
        case PROG_ON:
          layer_on(_PROGRAMMER);
          #ifdef AUDIO_ENABLE
            PLAY_SONG(tone_prog_on);
          #endif
          return false;
          break;
        case PROG_OFF:
          layer_off(_PROGRAMMER);
          #ifdef AUDIO_ENABLE
            PLAY_SONG(tone_prog_off);
          #endif
          return false;
          break;
        case KC_CAPS:
          #ifdef AUDIO_ENABLE
            PLAY_SONG(tone_caps_lock);
          #endif
          return true;
        case TB_SCRL:
          if (record->event.pressed) {
            led_t led_usb_state = host_keyboard_led_state();
            if (!led_usb_state.caps_lock) {
              register_code(KC_CAPS);
            }}
            else {
              register_code(KC_CAPS);
          }
          return false;
      }
    return true;
};

bool muse_mode = false;
uint8_t last_muse_note = 0;
uint16_t muse_counter = 0;
uint8_t muse_offset = 70;
uint16_t muse_tempo = 50;

void encoder_update_user(uint8_t index, bool clockwise) {
  if (muse_mode) {
    if (IS_LAYER_ON(_RAISE)) {
      if (clockwise) {
        muse_offset++;
      } else {
        muse_offset--;
      }
    } else {
      if (clockwise) {
        muse_tempo+=1;
      } else {
        muse_tempo-=1;
      }
    }
  } else {
    if (clockwise) {
      register_code(KC_PGDN);
      unregister_code(KC_PGDN);
    } else {
      register_code(KC_PGUP);
      unregister_code(KC_PGUP);
    }
  }
}

void dip_switch_update_user(uint8_t index, bool active) {
    switch (index) {
        case 0:
            if (active) {
                layer_on(_ADJUST);
            } else {
                layer_off(_ADJUST);
            }
            break;
        case 1:
            if (active) {
                muse_mode = true;
            } else {
                muse_mode = false;
            }
    }
}


void matrix_scan_user(void) {
#ifdef AUDIO_ENABLE
    if (muse_mode) {
        if (muse_counter == 0) {
            uint8_t muse_note = muse_offset + SCALE[muse_clock_pulse()];
            if (muse_note != last_muse_note) {
                stop_note(compute_freq_for_midi_note(last_muse_note));
                play_note(compute_freq_for_midi_note(muse_note), 0xF);
                last_muse_note = muse_note;
            }
        }
        muse_counter = (muse_counter + 1) % muse_tempo;
    } else {
        if (muse_counter) {
            stop_all_notes();
            muse_counter = 0;
        }
    }
#endif
}



bool music_mask_user(uint16_t keycode) {
  switch (keycode) {
    case RAISE:
    case LOWER:
      return false;
    default:
      return true;
  }
}

////////////////////////////////////////////////////////////////////////////////
// Combos
////////////////////////////////////////////////////////////////////////////////
// enum combo_events {
//     ESC_ENTER_CAPS_LOCK
    // DFJK_QWERTY_MODS,
    // EUHT_DVORAK_MODS
// };

// const uint16_t PROGMEM esc_enter_caps_lock[] = {KC_LSFT, KC_RSFT, COMBO_END};
// const uint16_t PROGMEM dfjk_combo[] = {KC_D, KC_F, KC_J, KC_K, COMBO_END};
// const uint16_t PROGMEM euht_combo[] = {KC_E, KC_U, KC_H, KC_T, COMBO_END};

// combo_t key_combos[COMBO_COUNT] = {
    // [ESC_ENTER_CAPS_LOCK] = COMBO_ACTION(esc_enter_caps_lock),
//     [DFJK_QWERTY_MODS] = COMBO_ACTION(dfjk_combo),
//     [EUHT_DVORAK_MODS] = COMBO_ACTION(euht_combo)
  // };



// void process_combo_event(uint16_t combo_index, bool pressed) {
//   switch(combo_index) {
      // case ESC_ENTER_CAPS_LOCK:
      //     if (pressed) {
      //         tap_code16(KC_CAPS);
      //     }
      //     break;
//     case DFJK_QWERTY_MODS:
//       if (pressed) {
//         layer_on(_QWERTY_MODS);
//       }
//       break;
//     case EUHT_DVORAK_MODS:
//       if (pressed) {
//         layer_on(_DVORAK_MODS);
//       }
//       break;}
//    }
// }

////////////////////////////////////////////////////////////////////////////////
// Combos
////////////////////////////////////////////////////////////////////////////////
enum combos {
    SHIFTS_QWERTY,
    SHIFTS_DVORAK,
    SHIFTS_BEKL,
    TENKEY_QWERTY,
    C_EQUALS,
    C_BACKSLASH,
    C_PIPE,
    C_EXPOSE,
};

const uint16_t PROGMEM shifts_querty_combo[] = {KC_Z, KC_X, COMBO_END};
const uint16_t PROGMEM shifts_dvorak_combo[] = {KC_SCLN, KC_Q, COMBO_END};
const uint16_t PROGMEM shifts_bekl_combo[]   = {KC_J, KC_SLSH, COMBO_END};
const uint16_t PROGMEM tenkey_querty_combo[] = {KC_Z, KC_C, COMBO_END};
const uint16_t PROGMEM equals_combo[]        = {KC_4, KC_PLUS, COMBO_END};
const uint16_t PROGMEM backslash_combo[]     = {KC_COMM, KC_SLSH, COMBO_END};
const uint16_t PROGMEM pipe_combo[]          = {KC_DOT, KC_SLSH, COMBO_END};
const uint16_t PROGMEM expose_combo[]        = {KC_BTN1, KC_BTN2, COMBO_END};



combo_t key_combos[COMBO_COUNT] = {
    [SHIFTS_QWERTY] = COMBO_ACTION(shifts_querty_combo),
    [SHIFTS_DVORAK] = COMBO_ACTION(shifts_dvorak_combo),
    [SHIFTS_BEKL]   = COMBO_ACTION(shifts_bekl_combo),
    [TENKEY_QWERTY] = COMBO_ACTION(tenkey_querty_combo),
    [C_EQUALS]      = COMBO(equals_combo, KC_EQL),
    [C_BACKSLASH]   = COMBO(backslash_combo, KC_BSLS),
    [C_PIPE]        = COMBO(pipe_combo, KC_PIPE),
    [C_EXPOSE]      = COMBO(expose_combo, KC_PIPE),
};

void process_combo_event(uint16_t combo_index, bool pressed) {
    switch(combo_index) {
        case SHIFTS_QWERTY:
        case SHIFTS_DVORAK:
        case SHIFTS_BEKL:
        if (pressed) {
            #ifdef AUDIO_ENABLE
                PLAY_SONG(tone_caps_lock);
            #endif //AUDIO_ENABLE
            tap_code_delay(KC_CAPS,500);
            // SEND_STRING(SS_TAP(KC_CAP));
            }
        break;

        case TENKEY_QWERTY:
            if (pressed) {
                layer_invert(_TENKEY);
                #ifdef AUDIO_ENABLE
                    if (IS_LAYER_ON(_TENKEY))
                        PLAY_SONG(tone_tenkey_activate);
                    else
                        PLAY_SONG(tone_tenkey_deactivate);
                #endif //AUDIO_ENABLE
            }
        break;
               
    }
}


// bool led_update_user(led_t led_state) {
//     #ifdef AUDIO_ENABLE
//     static uint8_t caps_state = 0;
//     if (caps_state != led_state.caps_lock) {
//         led_state.caps_lock ? PLAY_SONG(caps_on) : PLAY_SONG(caps_off);
//         caps_state = led_state.caps_lock;
//     }
//     #endif
//     return true;
// }



