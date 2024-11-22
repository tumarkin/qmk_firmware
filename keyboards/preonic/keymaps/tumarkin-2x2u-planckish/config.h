#pragma once

// The produce name needs to be redefined to work with setleds.
// This statement will cause a conflict with the master config.h
// should that file change. Simply update the master config.h
// to make this work.
#define PRODUCT         Preonic Keyboard

#ifdef AUDIO_ENABLE
    #define STARTUP_SONG SONG(ZELDA_PUZZLE)
    // #define STARTUP_SONG SONG(PREONIC_SOUND)
    // #define STARTUP_SONG SONG(NO_SOUND)

    // #define DEFAULT_LAYER_SONGS { SONG(QWERTY_SOUND), 
    //                               SONG(COLEMAK_SOUND), 
    //                               SONG(DVORAK_SOUND) 
    //                             }
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
#define TAPPING_TERM 200

// Prevent normal rollover on alphas from accidentally triggering mods.
#define IGNORE_MOD_TAP_INTERRUPT

// Enable rapid switch from tap to hold, disables double tap hold auto-repeat.
// #define TAPPING_FORCE_HOLD

// Apply the modifier on keys that are tapped during a short hold of a modtap
#define PERMISSIVE_HOLD

// Mouse key configuration
// #define MK_KINETIC_SPEED
// #define MK_KINETIC_SPEED
// #define MK_COMBINED

// #define MOUSEKEY_BASE_SPEED 200
// #define MOUSEKEY_INTERVAL 15
// #define MOUSEKEY_MOVE_DELTA 1
// #define MOUSEKEY_MAX_SPEED 20
// #define MK_C_INTERVAL_0 15
// #define MK_C_OFFSET_0 5
// #define MOUSEKEY_TIME_TO_MAX 50
// #define KC_MS_ACCEL0 2
// #define MOUSEKEY_BASE_SPEED 2000
// #define MOUSEKEY_INITIAL_SPEED 1

// #define MOUSEKEY_INTERVAL 10
// #define MOUSEKEY_MOVE_DELTA 5
// #define MOUSEKEY_MAX_SPEED 10



#define COMBO_COUNT 9

// The mousekey functions are defined in quantum/mousekey.c

#define MK_KINETIC_SPEED
// Delay between pressing a movement key and cursor movement
#define MOUSEKEY_DELAY 8
// Time between cursor movements in milliseconds
#define MOUSEKEY_INTERVAL 8
// Step size for accelerating from initial to base speed
#define MOUSEKEY_MOVE_DELTA 1
// Maximum cursor speed at which acceleration stops
#define MOUSEKEY_MAX_SPEED 22
// Time until maximum cursor speed is reached
#define MOUSEKEY_TIME_TO_MAX 200
// Initial speed of the cursor in pixel per second
#define MOUSEKEY_INITIAL_SPEED 1
// // Maximum cursor speed at which acceleration stops
// #define MOUSEKEY_BASE_SPEED 60
// // Decelerated cursor speed
#define MOUSEKEY_DECELERATED_SPEED 1
// // Accelerated cursor speed
// #define MOUSEKEY_ACCELERATED_SPEED 250


