#include "muse.h"
#ifdef AUDIO_ENABLE
    #include "audio.h"
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




/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      | Debug|      |      |      |      |TermOf|TermOn|      |      |Reset |  
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
  _______, _______,   DEBUG,   KC_LSCR, KC_SLCK, _______, _______, TERM_ON, TERM_OFF, _______, _______, RESET,
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

