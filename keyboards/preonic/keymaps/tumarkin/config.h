#pragma once

#ifdef AUDIO_ENABLE
    #define STARTUP_SONG SONG(PREONIC_SOUND)
    // #define STARTUP_SONG SONG(NO_SOUND)

    #define DEFAULT_LAYER_SONGS { SONG(QWERTY_SOUND), \
                                  SONG(COLEMAK_SOUND), \
                                  SONG(DVORAK_SOUND) \
                                }
#endif

#define MUSIC_MASK (keycode != KC_NO)

/*
 * MIDI options
 */

/* enable basic MIDI features:
   - MIDI notes can be sent when in Music mode is on
*/

#define MIDI_BASIC

/* enable advanced MIDI features:
   - MIDI notes can be added to the keymap
   - Octave shift and transpose
   - Virtual sustain, portamento, and modulation wheel
   - etc.
*/
//#define MIDI_ADVANCED

/* override number of MIDI tone keycodes (each octave adds 12 keycodes and allocates 12 bytes) */
//#define MIDI_TONE_KEYCODE_OCTAVES 2


// Mod-tap settings
// From: https://precondition.github.io/home-row-mods
// Configure the global tapping term (default: 200ms)
// 
// Defining the TAPPING_TERM here seems to conflict with
// that in tmk_core/common/action_tapping.h
// 
// Defining it at both locaitons.
#define TAPPING_TERM 200

// Prevent normal rollover on alphas from accidentally triggering mods.
#define IGNORE_MOD_TAP_INTERRUPT

// Enable rapid switch from tap to hold, disables double tap hold auto-repeat.
// #define TAPPING_FORCE_HOLD

// Apply the modifier on keys that are tapped during a short hold of a modtap
#define PERMISSIVE_HOLD

// Mouse key configuration
#define MK_KINETIC_SPEED
#define MK_COMBINED

#define MOUSEKEY_INTERVAL 15
#define MOUSEKEY_MOVE_DELTA 1
#define MOUSEKEY_MAX_SPEED 33
// #define MK_C_INTERVAL_0 15
// #define MK_C_OFFSET_0 5
// #define MOUSEKEY_TIME_TO_MAX 50
// #define KC_MS_ACCEL0 2
// #define MOUSEKEY_BASE_SPEED 2000
// #define MOUSEKEY_INITIAL_SPEED 1

// #define MOUSEKEY_INTERVAL 10
// #define MOUSEKEY_MOVE_DELTA 5
// #define MOUSEKEY_MAX_SPEED 10
