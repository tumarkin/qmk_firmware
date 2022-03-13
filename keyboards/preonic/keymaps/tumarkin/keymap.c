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
enum preonic_layers {
  _QWERTY,
  _DVORAK,
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
  DVORAK,
  HANDDWN,
  PROG_ON,
  PROG_OFF,
  LOWER,
  RAISE,
  BACKLIT,
  // TB_SCRL,
  EXIT_MO,
  KC_BTNL,
  KC_BTNR,
};

/// Tap dance keycodes, states, and functions
enum td_keycodes {
  TB_UTIL
};

typedef enum {
  TD_NONE,
  TD_UNKNOWN,
  TD_SINGLE_TAP,
  TD_SINGLE_HOLD
} td_state_t;

static td_state_t td_state;

td_state_t cur_dance(qk_tap_dance_state_t *state);
void tb_util_finished (qk_tap_dance_state_t *state, void *user_data);
void tb_util_reset    (qk_tap_dance_state_t *state, void *user_data);



/******************************************************************************/
/* Layers                                                                     */
/******************************************************************************/
    

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
 * | Func | Mouse| Btn2 | Btn1 |Lower | Space/Arrow |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
// KC_DEL: DE
// BACKLIT: Brite

[_QWERTY] = LAYOUT_preonic_grid(
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,   KC_5,   KC_6,   KC_7,   KC_8,    KC_9,    KC_0,      KC_BSPC,
  KC_TAB,  KC_Q,    KC_W,    KC_E,    QWRT_R, KC_T,   KC_Y,   KC_U,   KC_I,    KC_O,    KC_P,      KC_QUOT, 
  ESC_MO,  QWRT_A,  QWRT_S,  QWRT_D,  QWRT_F, QWRT_G, KC_H,   QWRT_J, QWRT_K,  QWRT_L,  QWRT_SCLN, KC_ENT,
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM, KC_DOT,  KC_SLSH,   KC_RSFT,
  FUNCSHN, TD_BALL, KC_BTN2, KC_BTN1, LOWER,  SPC_MV, SPC_MV, RAISE,  KC_LEFT, KC_DOWN, KC_UP,     KC_RGHT
),
/* Dvorak
   ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |   "  |   ,  |   .  |   P  |   Y  |   F  |   G  |   C  |   R  |   L  | /    |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |   A  |   O  |   E  |   U  |   I  |   D  |   H  |   T  |   N  |   S  |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |   ;  |   Q  |   J  |   K  |   X  |   B  |   M  |   W  |   V  |   Z  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */

[_DVORAK] = LAYOUT_preonic_grid(
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  _______, KC_QUOT, KC_COMM, KC_DOT,  DVRK_P,  KC_Y,    KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_SLSH,
  _______, DVRK_A,  DVRK_O,  DVRK_E,  DVRK_U,  DVRK_I,  KC_D,    DVRK_H,  DVRK_T,  DVRK_N,  DVRK_S,  _______,
  _______, KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,    KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),
/* Hands Down (https://https://sites.google.com/alanreiser.com/handsdown)
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |   Q  |   C  |   H  |   P  |   V  |   K  |   Y  |   O  |   J  |   /  | ;    |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |   R  |   S  |   N  |   T  |   G  |   W  |   U  |   E  |   I  |   A  |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |   X  |   M  |   L  |   D  |   B  |   Z  |   F  |   '  |   ,  |   .  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */

[_HANDSDOWN] = LAYOUT_preonic_grid(
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  _______, KC_Q,    KC_C,    KC_H,    HNDS_P,  KC_V,    KC_K,    KC_Y,    KC_O,    KC_J,    KC_SLSH, KC_SCLN,    
  _______, HNDS_R,  HNDS_S,  HNDS_N,  HNDS_T,  HNDS_G,  KC_W,    HNDS_U,  HNDS_E,  HNDS_I,  HNDS_A,  _______, 
  _______, KC_X,    KC_M,    KC_L,    KC_D,    KC_B,    KC_Z,    KC_F,    KC_QUOT, KC_COMM, KC_DOT,  _______,  
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
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
 * |      |      |      |   <  |   >  |      |   /  |   7  |   8  |   9  |   *  |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |   {  |   }  |   (  |   )  |      |   -  |   4  |   5  |   6  |   +  |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |   [  |   ]  |      |   =  |   1  |   2  |   3  |   .  | Tab  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      0      |  Del |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_preonic_grid(
  _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______, _______, 
  _______, _______, _______, KC_LT,   KC_GT,   _______, KC_SLSH, KC_7,     KC_8,    KC_9,    KC_ASTR, _______, 
  _______, KC_LCBR, KC_RCBR, KC_LPRN, KC_RPRN, _______, KC_MINS, KC_4,     KC_5,    KC_6,    KC_PLUS, _______, 
  _______, _______, _______, KC_LBRC, KC_RBRC, _______, KC_EQL,  KC_1,     KC_2,    KC_3,    KC_DOT,  KC_TAB,  
  _______, _______, _______, _______, _______, KC_0,    KC_0,    KC_DEL,   _______, _______, _______, _______ 
),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |   <  |   >  |      |      |   +  |   =  |  *   |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |   {  |   }  |   (  |   )  |      |      |   -  |   _  |  \   |  |   |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |   [  |   ]  |      |      |      |      |      |  \   |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |    Bksp     |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
 
[_RAISE] = LAYOUT_preonic_grid(
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, KC_LT,   KC_GT,   _______, _______, KC_PLUS, KC_EQL,  KC_ASTR, _______, _______, 
  _______, KC_LCBR, KC_RCBR, KC_LPRN, KC_RPRN, _______, _______, KC_MINS, KC_UNDS, KC_BSLS, KC_PIPE, _______, 
  _______, _______, _______, KC_LBRC, KC_RBRC, _______, _______, _______, _______, _______, KC_BSLS, _______,
  _______, _______, _______, _______, _______, KC_BSPC, KC_BSPC, _______, _______, _______, _______, _______
),




/* Movement
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | Back | Fwd  | Prev | Next |      | Home | Pg Dn| Pg Up| End  |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      | Left | Down |  Up  |Right |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |Hy-F15| Btn2 | Btn1 |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_MOVEMENT] = LAYOUT_preonic_grid(
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, 
  _______, KC_BACK, KC_FWD,  KC_PREV, KC_NEXT, _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END,  _______, _______, 
  _______, _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______, 
  _______, _______, HYP_F15, KC_BTN2, KC_BTN1, _______, _______, _______, _______, _______, _______, _______, 
  _______, _______, _______, _______, _______, _______, _______, KC_DEL, _______, _______, _______, _______ 
),

/* Tenkey
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |  /   |  7   |  8   |  9   |  *   |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |  -   |  4   |  5   |  6   |  +   |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |  =   |  1   |  2   |  3   |  .   | TAB  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      0      |  0   |  0   |  .   |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_TENKEY] = LAYOUT_preonic_grid(
  _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______, _______, 
  _______, _______, _______, _______, _______, _______, KC_SLSH, KC_7,     KC_8,    KC_9,    KC_ASTR, _______, 
  _______, _______, _______, _______, _______, _______, KC_MINS, KC_4,     KC_5,    KC_6,    KC_PLUS, _______, 
  _______, _______, _______, _______, _______, _______, KC_EQL,  KC_1,     KC_2,    KC_3,    KC_DOT,  KC_TAB, 
  _______, _______, _______, _______, _______, KC_0,    KC_0,    KC_0,     KC_0,    KC_DOT,  _______, _______ 
),

/* Mouse
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |S-Btn2|S-Btn1|      |      | Btn1 |  Up  | Btn2 | Spd1 |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Exit |      |      | Btn2 | Btn1 |      |      | Left | Down | Right| Spd0 |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |O-Btn2|O-Btn1|O-Btn1|      |      |      |      |      | Spd2 |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |S-Btn2|S-Btn1|      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_MOUSE] = LAYOUT_preonic_grid(
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,      _______, 
  _______, _______, _______, SH_BTN2, SH_BTN1, _______, _______, KC_BTN1, KC_MS_U, KC_BTN2, KC_MS_ACCEL1, _______, 
  EXIT_MO, _______, HYP_F15, KC_BTN2, KC_BTN1, _______, _______, KC_MS_L, KC_MS_D, KC_MS_R, KC_MS_ACCEL0, _______, 
  _______, _______, OP_BTN2, OP_BTN1, OP_BTN1, _______, _______, _______, _______, _______, KC_MS_ACCEL2, _______, 
  _______, _______, SH_BTN2, SH_BTN1, _______, _______, _______, _______, _______, _______, _______, _______ 
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
 * |      |      |Aud cy|Aud on|AudOff|AGnorm|AGswap|Qwerty|Dvorak| Hands|      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |Voice-|Voice+|Mus on|MusOff|MidiOn|MidOff|PrgOn |PrgOff|      |Backlt|      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_preonic_grid(
  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,    KC_F10,  KC_F11,  KC_F12,
  _______, RESET,   DEBUG,   KC_LSCR, KC_SLCK, _______, _______, TERM_ON, TERM_OFF, _______, _______, _______,
  _______, _______, MU_MOD,  AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, QWERTY,  DVORAK,   HANDDWN, _______, _______,
  _______, MUV_DE,  MUV_IN,  MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  PROG_ON, PROG_OFF, _______, BACKLIT, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______
),

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
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
        // case KC_CAPS:
        //   #ifdef AUDIO_ENABLE
        //     PLAY_SONG(tone_caps_lock);
        //   #endif
        //   return true;
        //   break;
        // case TB_SCRL:
        //   if (record->event.pressed) {
        //     led_t led_usb_state = host_keyboard_led_state();
        //     if (!led_usb_state.caps_lock) {
        //       register_code(KC_CAPS);
        //     }
        //   } else {
        //       register_code(KC_CAPS);
        //   }
        //   return false;
        //   break;
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
};

// bool muse_mode = false;
// uint8_t last_muse_note = 0;
// uint16_t muse_counter = 0;
// uint8_t muse_offset = 70;
// uint16_t muse_tempo = 50;

// void encoder_update_user(uint8_t index, bool clockwise) {
//   if (muse_mode) {
//     if (IS_LAYER_ON(_RAISE)) {
//       if (clockwise) {
//         muse_offset++;
//       } else {
//         muse_offset--;
//       }
//     } else {
//       if (clockwise) {
//         muse_tempo+=1;
//       } else {
//         muse_tempo-=1;
//       }
//     }
//   } else {
//     if (clockwise) {
//       register_code(KC_PGDN);
//       unregister_code(KC_PGDN);
//     } else {
//       register_code(KC_PGUP);
//       unregister_code(KC_PGUP);
//     }
//   }
// }

// void dip_switch_update_user(uint8_t index, bool active) {
//     switch (index) {
//         case 0:
//             if (active) {
//                 layer_on(_ADJUST);
//             } else {
//                 layer_off(_ADJUST);
//             }
//             break;
//         case 1:
//             if (active) {
//                 muse_mode = true;
//             } else {
//                 muse_mode = false;
//             }
//     }
// }


// void matrix_scan_user(void) {
// #ifdef AUDIO_ENABLE
//     if (muse_mode) {
//         if (muse_counter == 0) {
//             uint8_t muse_note = muse_offset + SCALE[muse_clock_pulse()];
//             if (muse_note != last_muse_note) {
//                 stop_note(compute_freq_for_midi_note(last_muse_note));
//                 play_note(compute_freq_for_midi_note(muse_note), 0xF);
//                 last_muse_note = muse_note;
//             }
//         }
//         muse_counter = (muse_counter + 1) % muse_tempo;
//     } else {
//         if (muse_counter) {
//             stop_all_notes();
//             muse_counter = 0;
//         }
//     }
// #endif
// }



// bool music_mask_user(uint16_t keycode) {
//   switch (keycode) {
//     case RAISE:
//     case LOWER:
//       return false;
//     default:
//       return true;
//   }
// }

////////////////////////////////////////////////////////////////////////////////
// Combos
////////////////////////////////////////////////////////////////////////////////
enum combos {
    SHIFTS_QWERTY,
    SHIFTS_DVORAK,
    // SHIFTS_BEKL,
    MOUSE_QWERTY,
    TENKEY_QWERTY,
    // C_EQUALS,
    C_BACKSLASH,
    C_PIPE,
    C_EXPOSE,
};

const uint16_t PROGMEM shifts_querty_combo[] = {KC_Z, KC_X, COMBO_END};
const uint16_t PROGMEM shifts_dvorak_combo[] = {KC_SCLN, KC_Q, COMBO_END};
const uint16_t PROGMEM shifts_bekl_combo[]   = {KC_J, KC_SLSH, COMBO_END};
// const uint16_t PROGMEM mouse_qwerty_combo[]  = {KC_Q, KC_W, COMBO_END};
const uint16_t PROGMEM tenkey_querty_combo[] = {KC_Z, KC_C, COMBO_END};
// const uint16_t PROGMEM equals_combo[]        = {KC_4, KC_PLUS, COMBO_END};
const uint16_t PROGMEM backslash_combo[]     = {KC_J, KC_SCLN, COMBO_END};
const uint16_t PROGMEM pipe_combo[]          = {KC_COMM, KC_SLSH, COMBO_END};
const uint16_t PROGMEM expose_combo[]        = {KC_BTN1, KC_BTN2, COMBO_END};


combo_t key_combos[COMBO_COUNT] = {
    [SHIFTS_QWERTY] = COMBO_ACTION(shifts_querty_combo),
    [SHIFTS_DVORAK] = COMBO_ACTION(shifts_dvorak_combo),
    // [MOUSE_QWERTY]  = COMBO_ACTION(mouse_qwerty_combo),
    // [SHIFTS_BEKL]   = COMBO_ACTION(shifts_bekl_combo),
    [TENKEY_QWERTY] = COMBO_ACTION(tenkey_querty_combo),
    // [C_EQUALS]      = COMBO(equals_combo, KC_EQL),
    [C_BACKSLASH]   = COMBO(backslash_combo, KC_BSLS),
    [C_PIPE]        = COMBO(pipe_combo, KC_PIPE),
    [C_EXPOSE]      = COMBO_ACTION(expose_combo),
};

void process_combo_event(uint16_t combo_index, bool pressed) {
    switch(combo_index) {
        case SHIFTS_QWERTY:
        case SHIFTS_DVORAK:
        // case SHIFTS_BEKL:
        if (pressed) {
            #ifdef AUDIO_ENABLE
                PLAY_SONG(tone_caps_lock);
            #endif //AUDIO_ENABLE
            tap_code_delay(KC_CAPS,100);
            // SEND_STRING(SS_TAP(KC_CAP));
            }
        break;

        // case MOUSE_QWERTY:
        // if (pressed) {
        //     #ifdef AUDIO_ENABLE
        //       if (IS_LAYER_OFF(_MOUSE)) 
        //         PLAY_SONG(tone_mouse_mode_on);
        //     #endif //AUDIO_ENABLE
        //    layer_invert(_MOUSE);
        // }
        // break;

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

//////////////////////////////////////////////////////////////////////////////////
// Tap dance functions
//////////////////////////////////////////////////////////////////////////////////
// Determine the tapdance state to return
td_state_t cur_dance(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return TD_SINGLE_TAP;
        else return TD_SINGLE_HOLD;
    }
    else return TD_UNKNOWN; // Any number higher than the maximum state value you return above
}

// Handle the possible states for each tapdance keycode you define:
void tb_util_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case TD_SINGLE_TAP:
            register_mods(KC_LALT);
            register_mods(KC_LSFT);
            register_mods(KC_LCTL);
            register_code16(KC_F15);
            break;
        case TD_SINGLE_HOLD:
            layer_on(_MOUSE);
            break;
        case TD_UNKNOWN:
        case TD_NONE:
            break;
    }
}

void tb_util_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case TD_SINGLE_TAP:
            unregister_code16(KC_F15);
            unregister_mods(KC_LCTL);
            unregister_mods(KC_LSFT);
            unregister_mods(KC_LALT);
            break;
        case TD_SINGLE_HOLD:
            layer_off(_MOUSE);
            break;
        case TD_UNKNOWN:
        case TD_NONE:
            break;
    }
}

// Define `ACTION_TAP_DANCE_FN_ADVANCED()` for each tapdance keycode, passing in `finished` and `reset` functions
qk_tap_dance_action_t tap_dance_actions[] = {
        [TB_UTIL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, tb_util_finished, tb_util_reset)
};

// bool led_update_user(led_t led_state) {
//     #ifdef AUDIO_ENABLE
//     static uint8_t caps_state = 0;
//     if (caps_state != led_state.caps_lock) {
//         led_state.caps_lock ? PLAY_SONG(caps_on) : PLAY_SONG(caps_off); //         caps_state = led_state.caps_lock;
//     }
//     #endif
//     return true;
// }


// bool led_update_user(led_t led_state) { 
//     if (led_state.num_lock != mouse_state) { 
//         layer_on(_MOUSE);
//         // register_code(KC_X);
//         // unregister_code(KC_X);
//         // led_state.num_lock = 0;
//     } 

//     // PLAY_SONG(tone_mouse_mode_on);

//     mouse_state = led_state.num_lock; 
//     return true; 
// }

