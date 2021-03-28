/* Copyright 2015-2017 Jack Humbert
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


// QWERTY home row aliases
// Left-hand home row mods
#define QHOME_A LCTL_T(KC_A)
#define QHOME_S LALT_T(KC_S)
#define QHOME_D LGUI_T(KC_D)
#define QHOME_F LSFT_T(KC_F)
// Right-hand home row mods
#define QHOME_J RSFT_T(KC_J)
#define QHOME_K RGUI_T(KC_K)
#define QHOME_L LALT_T(KC_L)
#define QHOME_SCLN RCTL_T(KC_SCLN)

//Dvorak home row aliases
// Left-hand home row mods
#define DHOME_A LCTL_T(KC_A)
#define DHOME_O LALT_T(KC_O)
#define DHOME_E LGUI_T(KC_E)
#define DHOME_U LSFT_T(KC_U)
// Right-hand home row mods
#define DHOME_H RSFT_T(KC_H)
#define DHOME_T RGUI_T(KC_T)
#define DHOME_N LALT_T(KC_N)
#define DHOME_S RCTL_T(KC_S)


enum preonic_layers {
  _QWERTY,
  _COLEMAK,
  _DVORAK,
  _BEAKL15,
  _LOWER,
  _RAISE,
  _PROGRAMMER,
  _MOUSE,
  _TENKEY,
  _FUNCTIONS,
  _ADJUST
};

enum preonic_keycodes {
  QWERTY = SAFE_RANGE,
  COLEMAK,
  DVORAK,
  BEAKL15,
  LOWER,
  RAISE,
  BACKLIT
};

// Custom key shortcuts
#define CTR_ESC  MT(MOD_LCTL, KC_ESC)
#define PROG_TG  TG(_PROGRAMMER)
#define TENK_MO  MO(_TENKEY)
#define FUNC_MO  MO(_FUNCTIONS)
#define MOUS_MO  MO(_MOUSE)
#define CTR_ESC  MT(MOD_LCTL, KC_ESC)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  |  "   |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | ESC  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |Enter |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Shift |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Func | Mouse|10 Key| Prog |Lower |    Space    |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
// KC_DEL: DEL
// BACKLIT: Brite

[_QWERTY] = LAYOUT_preonic_grid(
  KC_GRV,   KC_1,    KC_2,    KC_3,    KC_4,    KC_5,   KC_6,   KC_7,    KC_8,    KC_9,    KC_0,       KC_BSPC,
  KC_TAB,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,   KC_Y,   KC_U,    KC_I,    KC_O,    KC_P,       KC_QUOT, 
  CTR_ESC,  QHOME_A, QHOME_S, QHOME_D, QHOME_F, KC_G,   KC_H,   QHOME_J, QHOME_K, QHOME_L, QHOME_SCLN, KC_ENT,
  KC_LSFT,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,   KC_N,   KC_M,    KC_COMM, KC_DOT,  KC_SLSH,    KC_RSFT,
  FUNC_MO,  MOUS_MO, TENK_MO, PROG_TG, LOWER,   KC_SPC, KC_SPC, RAISE,   KC_LEFT, KC_DOWN, KC_UP,      KC_RGHT
),
  // CTR_ESC,  KC_A,    KC_S,    KC_D,   KC_F,  KC_G,   KC_H,   KC_J,  KC_K,    KC_L,    KC_SCLN, KC_ENT,

/* Colemak
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   F  |   P  |   G  |   J  |   L  |   U  |   Y  |   ;  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   R  |   S  |   T  |   D  |   H  |   N  |   E  |   I  |   O  |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   K  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Func | Mouse|10 Key| Prog |Lower |    Space    |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_COLEMAK] = LAYOUT_preonic_grid(
  KC_GRV,   KC_1,    KC_2,    KC_3,    KC_4,  KC_5,   KC_6,   KC_7,  KC_8,    KC_9,    KC_0,    KC_BSPC,
  KC_TAB,   KC_Q,    KC_W,    KC_F,    KC_P,  KC_G,   KC_J,   KC_L,  KC_U,    KC_Y,    KC_SCLN, KC_DEL,
  KC_ESC,   KC_A,    KC_R,    KC_S,    KC_T,  KC_D,   KC_H,   KC_N,  KC_E,    KC_I,    KC_O,    KC_QUOT,
  KC_LSFT,  KC_Z,    KC_X,    KC_C,    KC_V,  KC_B,   KC_K,   KC_M,  KC_COMM, KC_DOT,  KC_SLSH, KC_ENT,
  FUNC_MO,  MOUS_MO, TENK_MO, PROG_TG, LOWER, KC_SPC, KC_SPC, RAISE, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
),

/* Dvorak
 ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   "  |   ,  |   .  |   P  |   Y  |   F  |   G  |   C  |   R  |   L  | /    |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | CTRL |   A  |   O  |   E  |   U  |   I  |   D  |   H  |   T  |   N  |   S  |Enter |
 * |------+------+------+------+------+------|------+------+------+------+------+-----
 * | Shift|   ;  |   Q  |   J  |   K  |   X  |   B  |   M  |   W  |   V  |   Z  |Shift |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Func | Mouse|10 Key| Prog |Lower |    Space    |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
// KC_DEL: DEL

[_DVORAK] = LAYOUT_preonic_grid(
  KC_GRV,   KC_1,    KC_2,    KC_3,    KC_4,    KC_5,   KC_6,   KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
  KC_TAB,   KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,   KC_F,   KC_G,    KC_C,    KC_R,    KC_L,    KC_SLSH,
  CTR_ESC,  DHOME_A, DHOME_O, DHOME_E, DHOME_U, KC_I,   KC_D,   DHOME_H, DHOME_T, DHOME_N, DHOME_S, KC_ENT,
  KC_LSFT,  KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,   KC_B,   KC_M,    KC_W,    KC_V,    KC_Z,    KC_RSFT,
  FUNC_MO,  MOUS_MO, TENK_MO, PROG_TG, LOWER,   KC_SPC, KC_SPC, RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
),

/* Beakl 15 (https://deskthority.net/wiki/BEAKL)
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   Q  |   H  |   O  |   U  |   X  |   G  |   C  |   R  |   F  |   Z  | ;    |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | CTRL |   Y  |   I  |   E  |   A  |   .  |   D  |   S  |   T  |   N  |   B  |Enter |
 * |------+------+------+------+------+------|------+------+------+------+------+-----
 * | Shift|   J  |   /  |   ,  |   K  |   '  |   W  |   M  |   L  |   P  |   V  |Shift |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Func | Mouse|10 Key| Prog |Lower |    Space    |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
// KC_DEL: DEL
[_BEAKL15] = LAYOUT_preonic_grid(
  KC_GRV,   KC_1,    KC_2,    KC_3,    KC_4,  KC_5,    KC_6,   KC_7,  KC_8,    KC_9,    KC_0,  KC_BSPC,
  KC_TAB,   KC_Q,    KC_H,    KC_O,    KC_U,  KC_X,    KC_G,   KC_C,  KC_R,    KC_F,    KC_Z,  KC_SCLN,    
  KC_LCTL,  KC_Y,    KC_I,    KC_E,    KC_A,  KC_DOT,  KC_D,   KC_S,  KC_T,    KC_N,    KC_B,  KC_ENT, 
  KC_LSFT,  KC_J,    KC_SLSH, KC_COMM, KC_K,  KC_QUOT, KC_W,   KC_M,  KC_L,    KC_P,    KC_V,  KC_RSFT,  
  FUNC_MO,  MOUS_MO, TENK_MO, PROG_TG, LOWER, KC_SPC,  KC_SPC, RAISE, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT
),


/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   -  |   =  |   [  |   ]  |  \   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |ISO # |ISO / | Pg Up| Pg Dn|      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_preonic_grid(
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  _______, _______, KC_LT,   KC_PLUS, KC_GT,   _______, _______, KC_LBRC, KC_EQL,  KC_RBRC, _______, KC_DEL, 
  KC_DEL,  _______, KC_LPRN, KC_MINS, KC_RPRN, _______, _______, KC_LCBR, KC_UNDS, KC_RCBR, _______, KC_PIPE,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_BSLS, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END
  // KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
  // KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL,
  // KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
  // _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_NUHS, KC_NUBS, KC_PGUP, KC_PGDN, _______,
  // _______, _______, _______, _______, _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY
),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |   <  |   +  |   >  |      |      |   [  |   _  |   ]  |      | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Del  |      |   (  |   -  |   )  |      |      |   {  |   =  |   }  |      |  |   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |  \   |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             | Home | Pg Dn| Pg Up| End  |      |
 * `-----------------------------------------------------------------------------------'
 */
 
[_RAISE] = LAYOUT_preonic_grid(
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  _______, _______, KC_LT,   KC_PLUS, KC_GT,   _______, _______, KC_LBRC, KC_EQL,  KC_RBRC, _______, KC_DEL, 
  KC_DEL,  _______, KC_LPRN, KC_MINS, KC_RPRN, _______, _______, KC_LCBR, KC_UNDS, KC_RCBR, _______, KC_PIPE,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_BSLS, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END
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

/* Tenkey
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |Clear |  /   |  *   |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |  7   |  8   |  9   |  -   |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |  4   |  5   |  6   |  +   |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |  1   |  2   |  3   |Enter |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |     Tab     |  0   |  0   |  .   |Enter |      |
 * `-----------------------------------------------------------------------------------'
 */
[_TENKEY] = LAYOUT_preonic_grid(
  _______, _______, _______, _______, _______, _______, _______, KC_CLEAR, KC_SLSH, KC_ASTR, _______, _______, 
  _______, _______, _______, _______, _______, _______, _______, KC_7,     KC_8,    KC_9,    KC_MINS, _______, 
  _______, _______, _______, _______, _______, _______, _______, KC_4,     KC_5,    KC_6,    KC_PLUS, _______, 
  _______, _______, _______, _______, _______, _______, _______, KC_1,     KC_2,    KC_3,    KC_ENT,  _______, 
  _______, _______, _______, _______, _______, KC_TAB,  KC_TAB,  KC_0,     KC_0,    KC_DOT,  KC_ENT,  _______ 
),

/* Mouse
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      | Btn1 |  Up  | Btn2 | Btn2 |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |      | Left | Down | Right| Btn1 |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_MOUSE] = LAYOUT_preonic_grid(
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, 
  _______, _______, _______, _______, _______, _______, _______, KC_BTN1, KC_MS_U, KC_BTN2, KC_BTN2, _______, 
  _______, _______, _______, _______, _______, _______, _______, KC_MS_L, KC_MS_D, KC_MS_R, KC_BTN1, _______, 
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, 
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ 
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
 * |      | Reset| Debug|      |      |      |      |TermOf|TermOn|      |      |  Del |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |Aud cy|Aud on|AudOff|AGnorm|AGswap|Qwerty|Colemk|Dvorak|      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |Voice-|Voice+|Mus on|MusOff|MidiOn|MidOff|      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_preonic_grid(
  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
  _______, RESET,   DEBUG,   _______, _______, _______, _______, TERM_ON, TERM_OFF,_______, _______, KC_DEL,
  _______, _______, MU_MOD,  AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, QWERTY,  COLEMAK, DVORAK,  BEAKL15, _______,
  _______, MUV_DE,  MUV_IN,  MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
)

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
        case QWERTY:
          if (record->event.pressed) {
            set_single_persistent_default_layer(_QWERTY);
          }
          return false;
          break;
        case COLEMAK:
          if (record->event.pressed) {
            set_single_persistent_default_layer(_COLEMAK);
          }
          return false;
          break;
        case DVORAK:
          if (record->event.pressed) {
            set_single_persistent_default_layer(_DVORAK);
          }
          return false;
          break;
        case BEAKL15:
          if (record->event.pressed) {
            set_single_persistent_default_layer(_BEAKL15);
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
        // case QWERTY_MODS:
        //   if (record->event.pressed) {
        //     set_single_persistent_default_layer(_QWERTY_MODS);
        //   }
        //   return false;
        //   break;
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

// ////////////////////////////////////////////////////////////////////////////////
// // Combos
// ////////////////////////////////////////////////////////////////////////////////
// enum combo_events {
//     DFJK_QWERTY_MODS,
//     EUHT_DVORAK_MODS
// };

// const uint16_t PROGMEM dfjk_combo[] = {KC_D, KC_F, KC_J, KC_K, COMBO_END};
// const uint16_t PROGMEM euht_combo[] = {KC_E, KC_U, KC_H, KC_T, COMBO_END};

// combo_t key_combos[COMBO_COUNT] = {
//     [DFJK_QWERTY_MODS] = COMBO_ACTION(dfjk_combo),
//     [EUHT_DVORAK_MODS] = COMBO_ACTION(euht_combo)
//   };



// void process_combo_event(uint16_t combo_index, bool pressed) {
//   switch(combo_index) {
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
// }

