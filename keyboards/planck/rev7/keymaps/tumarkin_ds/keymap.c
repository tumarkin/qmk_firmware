/* Copyright 2015-2023 Jack Humbert
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
#include "alias.h"
#ifdef AUDIO_ENABLE
    #include "my_songs.h"
#endif

////////////////////////////////////////////////////////////////////////////////
// Audio stuff
////////////////////////////////////////////////////////////////////////////////
float tone_qwerty[][2]             = SONG(QWERTY_SOUND);
float tone_dvorak[][2]             = SONG(DVORAK_SOUND);
float tone_beakl[][2]              = SONG(ZELDA_TREASURE);
float tone_prog_on[][2]            = SONG(MARIO_MUSHROOM);
float tone_prog_off[][2]           = SONG(CLOSE_ENCOUNTERS_5_NOTE);
float tone_caps_lock[][2]          = SONG(COIN_SOUND);
float tone_tenkey_activate[][2]    = SONG(GUITAR_SOUND);
float tone_tenkey_deactivate[][2]  = SONG(GUITAR_SOUND_DOWN);
float tone_mouse_mode_on[][2]      = SONG(TERMINAL_SOUND);


uint8_t mouse_state = 0;

////////////////////////////////////////////////////////////////////////////////
// Layers
////////////////////////////////////////////////////////////////////////////////
enum planck_layers { 
    _QWERTY, 
    _DVORAK, 
    _HANDSDOWN,
    _LOWER, 
    _RAISE, 
    _MOUSE,
    _PLOVER, 
    _TENKEY,
    _FUNCTIONS,
    _ADJUST 
};

enum planck_keycodes { 
    QWERTY = SAFE_RANGE,
    DVORAK,
    HANDDWN,
    PROG_ON,
    PROG_OFF,
    BACKLIT,
    EXIT_MO,
    KC_BTNL,
    KC_BTNR,
    // PLOVER = SAFE_RANGE, 
    PLOVER, 
    // BACKLIT, 
    EXT_PLV };

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

#define QWERTY PDF(_QWERTY)
#define HANDSDOWN PDF(_HANDSDOWN)
#define DVORAK PDF(_DVORAK)

/******************************************************************************/
/* Layers                                                                     */
/******************************************************************************/

/* clang-format off */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  |  "   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |Esc/Mo|   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Brite| Ctrl | Alt  | GUI  | Space/Lower | Space/Raise | Left | Down |  Up  |Right |
 * | Func | Mouse| Btn2 | Btn1 |                           |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_planck_grid(
    TAB_ADJ, KC_Q,    KC_W,    KC_E,    QWRT_R,  KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_QUOT,
    ESC_MO,  QWRT_A,  QWRT_S,  QWRT_D,  QWRT_F,  QWRT_G,  KC_H,    QWRT_J,  QWRT_K,  QWRT_L,  QWRT_SCLN, KC_ENT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_BSPC,
    BACKLIT, KC_LCTL, KC_LALT, KC_LGUI, SPC_LW,  SPC_LW,  SPC_RS,  SPC_RS,  KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
 // FUNCSHN, TD_BALL, KC_BTN2, KC_BTN1, SPC_LW, SPC_LW, SPC_RS, SPC_RS, KC_LEFT, KC_DOWN, KC_UP,     KC_RGHT
),

/* Dvorak
 * ,-----------------------------------------------------------------------------------.
 * |      |   '  |   ,  |   .  |   P  |   Y  |   F  |   G  |   C  |   R  |   L  |  /   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |   A  |   O  |   E  |   U  |   I  |   D  |   H  |   T  |   N  |   S  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |   ;  |   Q  |   J  |   K  |   X  |   B  |   M  |   W  |   V  |   Z  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |             |             |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_DVORAK] = LAYOUT_planck_grid(
    _______, KC_QUOT, KC_COMM, KC_DOT,  DVRK_P,  KC_Y,    KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_SLSH,
    _______, DVRK_A,  DVRK_O,  DVRK_E,  DVRK_U,  DVRK_I,  KC_D,    DVRK_H,  DVRK_T,  DVRK_N,  DVRK_S,  _______,
    _______, KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,    KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),


/* Hands Down (https://https://sites.google.com/alanreiser.com/handsdown)
 * ,-----------------------------------------------------------------------------------.
 * |      |   Q  |   C  |   H  |   P  |   V  |   K  |   Y  |   O  |   J  |   /  | ;    |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |   R  |   S  |   N  |   T  |   G  |   W  |   U  |   E  |   I  |   A  |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |   X  |   M  |   L  |   D  |   B  |   Z  |   F  |   '  |   ,  |   .  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |             |             |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */

[_HANDSDOWN] = LAYOUT_planck_grid(
  _______, KC_Q,    KC_C,    KC_H,    HNDS_P,  KC_V,    KC_K,    KC_Y,    KC_O,    KC_J,    KC_SLSH, KC_SCLN,    
  _______, HNDS_R,  HNDS_S,  HNDS_N,  HNDS_T,  HNDS_G,  KC_W,    HNDS_U,  HNDS_E,  HNDS_I,  HNDS_A,  _______, 
  _______, KC_X,    KC_M,    KC_L,    KC_D,    KC_B,    KC_Z,    KC_F,    KC_QUOT, KC_COMM, KC_DOT,  _______,  
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
 ),

// /* Lower
//  * ,-----------------------------------------------------------------------------------.
//  * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Bksp |
//  * |------+------+------+------+------+------+------+------+------+------+------+------|
//  * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   _  |   +  |   {  |   }  |  |   |
//  * |------+------+------+------+------+------+------+------+------+------+------+------|
//  * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |ISO ~ |ISO | | Home | End  |      |
//  * |------+------+------+------+------+------+------+------+------+------+------+------|
//  * |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
//  * `-----------------------------------------------------------------------------------'
//  */
// [_LOWER] = LAYOUT_planck_grid(
//     KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR,    KC_ASTR,    KC_LPRN, KC_RPRN, KC_BSPC,
//     KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_UNDS,    KC_PLUS,    KC_LCBR, KC_RCBR, KC_PIPE,
//     _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  S(KC_NUHS), S(KC_NUBS), KC_HOME, KC_END,  _______,
//     _______, _______, _______, _______, _______, _______, _______, _______,    KC_MNXT,    KC_VOLD, KC_VOLU, KC_MPLY
// ),

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |      | Back | Fwd  | Prev | Next |      | Home | Pg Dn| Pg Up| End  |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      | Left | Down |  Up  |Right |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |Hy-F15| Btn2 | Btn1 |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |             |     Del     |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_planck_grid(
  _______, KC_BACK, KC_FWD,  KC_PREV, KC_NEXT, _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END,  _______, _______, 
  _______, _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______, 
  _______, _______, HYP_F15, KC_BTN2, KC_BTN1, _______, _______, _______, _______, _______, _______, _______, 
  _______, _______, _______, _______, _______, _______, KC_DEL,  KC_DEL,  _______, _______, _______, _______ 
  // _______, _______, _______, _______, _______, _______, DEL_AD,  DEL_AD,  _______, _______, _______, _______ 
),


// /* Raise
//  * ,-----------------------------------------------------------------------------------.
//  * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
//  * |------+------+------+------+------+------+------+------+------+------+------+------|
//  * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   -  |   =  |   [  |   ]  |  \   |
//  * |------+------+------+------+------+------+------+------+------+------+------+------|
//  * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |ISO # |ISO / |Pg Up |Pg Dn |      |
//  * |------+------+------+------+------+------+------+------+------+------+------+------|
//  * |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
//  * `-----------------------------------------------------------------------------------'
//  */
// [_RAISE] = LAYOUT_planck_grid(
//     KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
//     KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
//     _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_NUHS, KC_NUBS, KC_PGUP, KC_PGDN, _______,
//     _______, _______, _______, _______, _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY
// ),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   !  |   @  |  #   |  $   |  %   |  ^   |  &   |  *   |  +   |  =   |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |   <  |   >  |   (  |   )  |      |      |   -  |   _  |  \   |  =   |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |   {  |   }  |   [  |   ]  |      |      |   {  |   }  |      |  |   |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |     Bksp    |             |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */

 
[_RAISE] = LAYOUT_planck_grid(
  KC_GRV,  KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_PLUS, KC_EQL,  _______,
  _______, KC_LT,   KC_GT,   KC_LPRN, KC_RPRN, _______, _______, KC_MINS, KC_UNDS, KC_BSLS, KC_EQL,  _______, 
  _______, KC_LCBR, KC_RCBR, KC_LBRC, KC_RBRC, _______, _______, KC_LCBR, KC_RCBR, _______, KC_PIPE, _______,
  _______, _______, _______, _______, KC_BSPC, KC_BSPC, _______, _______, _______, _______, _______, _______
),

/* Mouse
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |S-Btn2|S-Btn1|      |      | Btn1 |  Up  | Btn2 | Spd1 |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Exit |      |      | Btn2 | Btn1 |      |      | Left | Down | Right| Spd0 |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |O-Btn2|O-Btn1|O-Btn1|      |      |      |      |      | Spd2 |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |S-Btn2|S-Btn1|      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_MOUSE] = LAYOUT_planck_grid(
  _______, _______, _______, SH_BTN2, SH_BTN1, _______, _______, KC_BTN1, KC_MS_U, KC_BTN2, KC_MS_ACCEL1, _______, 
  EXIT_MO, _______, HYP_F15, KC_BTN2, KC_BTN1, _______, _______, KC_MS_L, KC_MS_D, KC_MS_R, KC_MS_ACCEL0, _______, 
  _______, _______, OP_BTN2, OP_BTN1, OP_BTN1, _______, _______, _______, _______, _______, KC_MS_ACCEL2, _______, 
  _______, _______, SH_BTN2, SH_BTN1, _______, _______, _______, _______, _______, _______, _______, _______ 
),


/* Plover layer (http://opensteno.org)
 * ,-----------------------------------------------------------------------------------.
 * |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |   S  |   T  |   P  |   H  |   *  |   *  |   F  |   P  |   L  |   T  |   D  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |   S  |   K  |   W  |   R  |   *  |   *  |   R  |   B  |   G  |   S  |   Z  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Exit |      |      |   A  |   O  |             |   E  |   U  |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_PLOVER] = LAYOUT_planck_grid(
    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1   ,
    XXXXXXX, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC,
    XXXXXXX, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    EXT_PLV, XXXXXXX, XXXXXXX, KC_C,    KC_V,    XXXXXXX, XXXXXXX, KC_N,    KC_M,    XXXXXXX, XXXXXXX, XXXXXXX
),

/* Tenkey
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |  /   |  7   |  8   |  9   |  *   |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |  -   |  4   |  5   |  6   |  +   |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |  =   |  1   |  2   |  3   |  .   | TAB  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |             |      0      |      |  .   |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_TENKEY] = LAYOUT_planck_grid(
  _______, _______, _______, _______, _______, _______, KC_SLSH, KC_7,     KC_8,    KC_9,    KC_ASTR, _______, 
  _______, _______, _______, _______, _______, _______, KC_MINS, KC_4,     KC_5,    KC_6,    KC_PLUS, _______, 
  _______, _______, _______, _______, _______, _______, KC_EQL,  KC_1,     KC_2,    KC_3,    KC_DOT,  KC_TAB, 
  _______, _______, _______, _______, _______, _______, KC_0,    KC_0,     _______, KC_DOT,  _______, _______ 
),

/* Functions
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |      |      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |      |      |      | Vol+ | Mute |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Prev | Next | Vol- | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_FUNCTIONS] = LAYOUT_planck_grid(
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, 
  _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   _______, _______, _______, _______, _______,
  _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______, _______, KC_VOLU, KC_MUTE,
  _______, _______, _______, _______, _______, _______, _______, _______, KC_MPRV, KC_MNXT, KC_VOLD, KC_MPLY
),
/* Adjust (Lower + Raise)
 *                      v------------------------RGB CONTROL--------------------v
 * ,-----------------------------------------------------------------------------------.
 * |      |      |Debug | RGB  |RGBMOD| HUE+ | HUE- | SAT+ | SAT- |BRGTH+|BRGTH-| Reset|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |MUSmod|Aud on|Audoff|AGnorm|AGswap|Qwerty|HDown |Dvorak|Plover|      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |Voice-|Voice+|Mus on|Musoff|MIDIon|MIDIof|      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_planck_grid(
    _______, _______, DB_TOGG, UG_TOGG, UG_NEXT, UG_HUEU, UG_HUED, UG_SATU, UG_SATD, UG_SPDU, UG_SPDD, QK_BOOT,
    _______, EE_CLR,  MU_NEXT, AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, QWERTY,  HANDSDOWN, DVORAK,  PLOVER,  _______,
    _______, AU_PREV, AU_NEXT, MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
)

};

#ifdef ENCODER_MAP_ENABLE
/* Rotary Encoders
 */
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    /* Qwerty
     *    v- (index) Clockwise / Counter Clockwise                        v- (index) Clockwise / Counter Clockwise
     * ,---------------------------------------------------------------------------------------.
     * | (0) Vol-    / Vol+    |   |   |   |   |   |   |   |   |   |   | (4) Vol-    / Vol+    |
     * |-----------------------+---+---+---+---+---+---+---+---+---+---+-----------------------|
     * | (1) KC_MNXT / KC_MPRV |   |   |   |   |   |   |   |   |   |   | (5) KC_MNXT / KC_MPRV |
     * |-----------------------+---+---+---+---+---+---+---+---+---+---+-----------------------|
     * | (2) KC_WBAK / KC_WFWD |   |   |   |   |   |   |   |   |   |   | (6) KC_SPC  / KC_ENT  |
     * |-----------------------+---+---+---+---+---+---+---+---+---+---+-----------------------|
     * | (3) KC_LEFT / KC_RGHT |   |   |   |   |       |   |   |   |   | (7) KC_DOWN / KC_UP   |
     * `---------------------------------------------------------------------------------------'
     */
    [_QWERTY] = {
        // LEFT SIDE (index 0 to 3)
        ENCODER_CCW_CW(KC_VOLU, KC_VOLD),
        ENCODER_CCW_CW(KC_MNXT, KC_MPRV),
        ENCODER_CCW_CW(KC_WBAK, KC_WFWD),
        ENCODER_CCW_CW(KC_LEFT, KC_RGHT),
        // RIGHT SIDE (index 4 to 7)
        ENCODER_CCW_CW(KC_VOLU, KC_VOLD),
        ENCODER_CCW_CW(KC_MNXT, KC_MPRV),
        ENCODER_CCW_CW(KC_SPC,  KC_ENT),
        ENCODER_CCW_CW(KC_DOWN, KC_UP)
    },

    /* Adjust (Lower + Raise)
     *    v- (index) Clockwise / Counter Clockwise                        v- (index) Clockwise / Counter Clockwise
     * ,---------------------------------------------------------------------------------------.
     * | (0) _______ / _______ |   |   |   |   |   |   |   |   |   |   | (4) _______ / _______ |
     * |-----------------------+---+---+---+---+---+---+---+---+---+---+-----------------------|
     * | (1) _______ / _______ |   |   |   |   |   |   |   |   |   |   | (5) _______ / _______ |
     * |-----------------------+---+---+---+---+---+---+---+---+---+---+-----------------------|
     * | (2) UG_NEXT / UG_PREV |   |   |   |   |   |   |   |   |   |   | (6) SAT- / SAT+       |
     * |-----------------------+---+---+---+---+---+---+---+---+---+---+-----------------------|
     * | (3) UG_VALD / UG_VALU |   |   |   |   |       |   |   |   |   | (7) HUE- / HUE+       |
     * `---------------------------------------------------------------------------------------'
     */
    [_ADJUST] = {
        // LEFT SIDE (index 0 to 3)
        ENCODER_CCW_CW(_______, _______),
        ENCODER_CCW_CW(_______, _______),
        ENCODER_CCW_CW(UG_NEXT, UG_PREV),
        ENCODER_CCW_CW(UG_VALD, UG_VALU),
        // RIGHT SIDE (index 4 to 7)
        ENCODER_CCW_CW(_______, _______),
        ENCODER_CCW_CW(_______, _______),
        ENCODER_CCW_CW(UG_SATD,  UG_SATU),
        ENCODER_CCW_CW(UG_HUEU,  UG_HUED)
    }
};
#endif
/* clang-format on */

#ifdef AUDIO_ENABLE
float plover_song[][2]    = SONG(PLOVER_SOUND);
float plover_gb_song[][2] = SONG(PLOVER_GOODBYE_SOUND);
#endif

bool play_encoder_melody(uint8_t index, bool clockwise);

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef ENCODER_MAP_ENABLE
    if (IS_ENCODEREVENT(record->event) && record->event.pressed) {
        play_encoder_melody(record->event.key.col, record->event.type == ENCODER_CCW_EVENT);
    }
#endif
    switch (keycode) {
        case QWERTY:
          if (record->event.pressed) {
            // set_single_persistent_default_layer(_QWERTY);
            // default_layer_set(_QWERTY);
            layer_off(_DVORAK);
            layer_off(_HANDSDOWN);
            #ifdef AUDIO_ENABLE
                PLAY_SONG(tone_qwerty);
            #endif //AUDIO_ENABLE
          }
          return false;
          break;
        case DVORAK:
          if (record->event.pressed) {
            layer_on(_DVORAK);
            layer_off(_HANDSDOWN);
            #ifdef AUDIO_ENABLE
                PLAY_SONG(tone_dvorak);
            #endif //AUDIO_ENABLE
          }
          return false;
          break;
        case HANDDWN:
          if (record->event.pressed) {
            layer_off(_DVORAK);
            layer_on(_HANDSDOWN);
            #ifdef AUDIO_ENABLE
                PLAY_SONG(tone_beakl);
            #endif //AUDIO_ENABLE
          }
          return false;
          break;
        case BACKLIT:
            if (record->event.pressed) {
                register_code(KC_RSFT);
            } else {
                unregister_code(KC_RSFT);
            }
            return false;
            break;
        case PLOVER:
            if (record->event.pressed) {
#ifdef AUDIO_ENABLE
                stop_all_notes();
                PLAY_SONG(plover_song);
#endif
                layer_off(_RAISE);
                layer_off(_LOWER);
                layer_off(_ADJUST);
                layer_on(_PLOVER);
                if (!eeconfig_is_enabled()) {
                    eeconfig_init();
                }
                keymap_config.raw  = eeconfig_read_keymap();
                keymap_config.nkro = 1;
                eeconfig_update_keymap(keymap_config.raw);
            }
            return false;
            break;
        case EXT_PLV:
            if (record->event.pressed) {
#ifdef AUDIO_ENABLE
                PLAY_SONG(plover_gb_song);
#endif
                layer_off(_PLOVER);
            }
            return false;
            break;
        case KC_BTNL:
          if (record->event.pressed) {
              if (IS_LAYER_OFF(_MOUSE)) {
                register_code(KC_BTN1);
              } else {
                register_mods(mod_config(MOD_LSFT));
                register_code(KC_BTN1);
              }
          } else {
              if (IS_LAYER_OFF(_MOUSE)) {
                unregister_code(KC_BTN1);

              } else {
                unregister_code(KC_BTN1);
                unregister_mods(mod_config(MOD_LSFT));
              }
          }
          return false;
          break;
        case KC_BTNR:
          if (record->event.pressed) {
              if (IS_LAYER_OFF(_MOUSE)) {
                register_code(KC_BTN2);
              } else {
                register_mods(mod_config(MOD_LSFT));
                register_code(KC_BTN2);
              }
          } else {
              if (IS_LAYER_OFF(_MOUSE)) {
                unregister_code(KC_BTN2);

              } else {
                unregister_code(KC_BTN2);
                unregister_mods(mod_config(MOD_LSFT));
              }
          }
          return false;
          break;
        case EXIT_MO:
          if (record->event.pressed) {
            register_mods(mod_config(MOD_LCTL));
            register_code(KC_F15);
            layer_off(_MOUSE);
          } else {
            unregister_mods(mod_config(MOD_LCTL));
            unregister_code(KC_F15);
          }
          return false;
          break;
    }
    return true;
}

/* clang-format off */
float melody[8][2][2] = {
    {{440.0f, 8}, {440.0f, 24}},
    {{440.0f, 8}, {440.0f, 24}},
    {{440.0f, 8}, {440.0f, 24}},
    {{440.0f, 8}, {440.0f, 24}},
    {{440.0f, 8}, {440.0f, 24}},
    {{440.0f, 8}, {440.0f, 24}},
    {{440.0f, 8}, {440.0f, 24}},
    {{440.0f, 8}, {440.0f, 24}},
};
/* clang-format on */

#define JUST_MINOR_THIRD 1.2
#define JUST_MAJOR_THIRD 1.25
#define JUST_PERFECT_FOURTH 1.33333333
#define JUST_TRITONE 1.42222222
#define JUST_PERFECT_FIFTH 1.33333333

#define ET12_MINOR_SECOND 1.059463
#define ET12_MAJOR_SECOND 1.122462
#define ET12_MINOR_THIRD 1.189207
#define ET12_MAJOR_THIRD 1.259921
#define ET12_PERFECT_FOURTH 1.33484
#define ET12_TRITONE 1.414214
#define ET12_PERFECT_FIFTH 1.498307

deferred_token tokens[8];

uint32_t reset_note(uint32_t trigger_time, void *note) {
    *(float*)note = 440.0f;
    return 0;
}

bool play_encoder_melody(uint8_t index, bool clockwise) {
    cancel_deferred_exec(tokens[index]);
    if (clockwise) {
        melody[index][1][0] = melody[index][1][0] * ET12_MINOR_SECOND;
        melody[index][0][0] = melody[index][1][0] / ET12_PERFECT_FIFTH;
        audio_play_melody(&melody[index], 2, false);
    } else {
        melody[index][1][0] = melody[index][1][0] / ET12_MINOR_SECOND;
        melody[index][0][0] = melody[index][1][0] * ET12_TRITONE;
        audio_play_melody(&melody[index], 2, false);
    }
    tokens[index] = defer_exec(1000, reset_note, &melody[index][1][0]);
    return false;
}

bool encoder_update_user(uint8_t index, bool clockwise) {
    return play_encoder_melody(index, clockwise);
}

bool dip_switch_update_user(uint8_t index, bool active) {
    switch (index) {
        case 0: {
#ifdef AUDIO_ENABLE
            static bool play_sound = false;
#endif
            if (active) {
#ifdef AUDIO_ENABLE
                if (play_sound) {
                    PLAY_SONG(plover_song);
                }
#endif
                layer_on(_ADJUST);
            } else {
#ifdef AUDIO_ENABLE
                if (play_sound) {
                    PLAY_SONG(plover_gb_song);
                }
#endif
                layer_off(_ADJUST);
            }
#ifdef AUDIO_ENABLE
            play_sound = true;
#endif
            break;
        }
    }
    return true;
}

////////////////////////////////////////////////////////////////////////////////
// Combos
////////////////////////////////////////////////////////////////////////////////
enum combos {
    SHIFTS_QWERTY,
    SHIFTS_DVORAK,
    SHIFTS_HANDS,
    TENKEY_QWERTY,
    C_PIPE,
    C_EXPOSE,
};



const uint16_t PROGMEM shifts_querty_combo[] = {KC_Z, KC_X, COMBO_END};
const uint16_t PROGMEM shifts_dvorak_combo[] = {KC_SCLN, KC_Q, COMBO_END};
const uint16_t PROGMEM shifts_hands_combo[]  = {KC_X, KC_M, COMBO_END};
const uint16_t PROGMEM tenkey_querty_combo[] = {KC_Z, KC_C, COMBO_END};
const uint16_t PROGMEM pipe_combo[]          = {KC_COMM, KC_SLSH, COMBO_END};
const uint16_t PROGMEM expose_combo[]        = {KC_BTN1, KC_BTN2, COMBO_END};


combo_t key_combos[COMBO_COUNT] = {
    [SHIFTS_QWERTY] = COMBO_ACTION(shifts_querty_combo),
    [SHIFTS_DVORAK] = COMBO_ACTION(shifts_dvorak_combo),
    [SHIFTS_HANDS]  = COMBO_ACTION(shifts_hands_combo),
    [TENKEY_QWERTY] = COMBO_ACTION(tenkey_querty_combo),
    [C_PIPE]        = COMBO(pipe_combo, KC_PIPE),
    [C_EXPOSE]      = COMBO_ACTION(expose_combo),
};

void process_combo_event(uint16_t combo_index, bool pressed) {
    switch(combo_index) {
        case SHIFTS_QWERTY:
        case SHIFTS_DVORAK:
        case SHIFTS_HANDS:
        if (pressed) {
            #ifdef AUDIO_ENABLE
                PLAY_SONG(tone_caps_lock);
            #endif //AUDIO_ENABLE
            tap_code_delay(KC_CAPS,100);
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

        case C_EXPOSE:
          if (pressed) {
              register_code(KC_LCTL);
              if (IS_LAYER_OFF(_MOUSE)) {
                  tap_code_delay(KC_UP, 100);
              } else {
                  tap_code_delay(KC_DOWN, 100);
              }
              unregister_code(KC_LCTL);
          }
          break;
           
               
    }
}

