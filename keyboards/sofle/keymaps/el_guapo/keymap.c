#include QMK_KEYBOARD_H
#include "alias.h"

enum sofle_layers {
    /* _M_XYZ = Mac Os, _W_XYZ = Win/Linux */
    _QWERTY,
    _DVORAK,
    _HANDSDOWN,
    _PROGRAMMER,
    _LOWER,
    _RAISE,
    _MOVEMENT_L,
    _MOVEMENT_R,
    _ADJUST,
};

enum custom_keycodes {
    KC_QWRTY = SAFE_RANGE,
    KC_DVRK,
    KC_HNDWN,
    KC_LOWER,
    KC_RAISE,
    KC_ADJUST,
    KC_PRVWD,
    KC_NXTWD,
    KC_LSTRT,
    KC_LEND,
    KC_DLINE,
    PROG_ON,
    PROG_OFF,
    TB_SCRL
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * QWERTY
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  `   |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  `   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | TAB  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |  "   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | ESC  |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |Enter |
 * |------+------+------+------+------+------| Mute  |    |  Play |------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |RShift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            |      |      |      |LOWER | /Space  /       \Space \  |RAISE |      |      |      |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */

[_QWERTY] = LAYOUT( \
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC, \
  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_QUOT, \
  KC_ESC,  QWRT_A,  QWRT_S,  QWRT_D,  QWRT_F,  KC_G,                      KC_H,    QWRT_J,  QWRT_K,  QWRT_L,  QWRT_SC, KC_ENT, \
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_MUTE, KC_MPLY, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, \
                 TB_SCRL,  XXXXXXX, XXXXXXX, KC_LOWER, SPC_MVL,    SPC_MVR, KC_RAISE, XXXXXXX,XXXXXXX,XXXXXXX \
),
/*
 * DVORAK
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |   "  |   ,  |   .  |   P  |   Y  |                    |   F  |   G  |   C  |   R  |   L  |  /   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |   A  |   O  |   E  |   U  |   I  |-------.    ,-------|   D  |   H  |   T  |   N  |   S  |      |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |   ;  |   Q  |   J  |   K  |   X  |-------|    |-------|   B  |   M  |   W  |   V  |   Z  |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            |      |      |      |      | /       /       \      \  |      |      |      |      |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */

[_DVORAK] = LAYOUT(
  _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
  _______, KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,                      KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_SLSH,
  _______, DVRK_A,  DVRK_O,  DVRK_E,  DVRK_U,  KC_I,                      KC_D,    DVRK_H,  DVRK_T,  DVRK_N,  DVRK_S,  _______,
  _______, KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,    _______, _______, KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    _______,
                 _______,  _______, _______, _______, _______,      _______, _______,  _______,_______,_______ \
),
/*
 * HANDSDOWN
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |   Q  |   C  |   H  |   P  |   V  |                    |   K  |   Y  |   O  |   J  |   /  |  ;   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |   R  |   S  |   N  |   T  |   G  |-------.    ,-------|   W  |   U  |   E  |   I  |   A  |      |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |   X  |   M  |   L  |   D  |   B  |-------|    |-------|   Z  |   F  |   "  |   ,  |   .  |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            |      |      |      |      | /       /       \      \  |      |      |      |      |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */

[_HANDSDOWN] = LAYOUT(
  _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
  _______, KC_Q,    KC_C,    KC_H,    KC_P,    KC_V,                      KC_K,    KC_Y,    KC_O,    KC_J,    KC_SLSH, KC_SCLN,
  _______, HNDS_R,  HNDS_S,  HNDS_N,  HNDS_T,  KC_G,                      KC_W,    HNDS_U,  HNDS_E,  HNDS_I,  HNDS_A,  _______,
  _______, KC_X,    KC_M,    KC_L,    KC_D,    KC_B,  _______,   _______, KC_Z,    KC_F,    KC_QUOT, KC_COMM, KC_DOT,  _______,
                 _______,  _______, _______, _______, _______,      _______, _______,  _______,_______,_______ \
),
/* Programmer
 * ,----------------------------------------.                    ,-----------------------------------------.
 * |      |   !  |   @  |   #  |   $  |   %  |                    |   ^  |   &  |   *  |   (  |   )  |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------.    ,-------|      |      |      |      |      |      |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      |      |      |      |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            |      |      |      |      | /       /       \      \  |      |      |      |      |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */
[_PROGRAMMER] = LAYOUT(
  _______, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                   KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______,
  _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, 
  _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, 
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, 
                 _______,  _______, _______, _______, _______,      _______, _______,  _______,_______,_______ \
),
/* LOWER
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |  F1  |  F2  |  F3  |  F4  |      |                    |   *  |   7  |   8  |   9  |   /  |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |  F5  |  F6  |  F7  |  F8  |      |-------.    ,-------|   +  |   4  |   5  |   6  |   -  |      |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |  F9  |  F10 |  F11 |  F12 |      |-------|    |-------|   =  |   1  |   2  |   3  |   .  | TAB |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            |      |      |      |      | /       /       \  0   \  |      |      |      |      |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */
[_LOWER] = LAYOUT( \
  _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, 
  _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   _______,                   KC_ASTR, KC_7,    KC_8,    KC_9,    KC_SLSH, _______, \
  _______, KC_F5,   KC_F6,   KC_F7,   KC_F8,   _______,                   KC_PLUS, KC_4,    KC_5,    KC_6,    KC_MINS, _______, \
  _______, KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______, _______, KC_EQL,  KC_1,    KC_2,    KC_3,    KC_DOT,  KC_TAB, \
                       _______, _______, _______, _______, _______,       KC_0, _______, _______, _______, _______\
),
/* RAISE
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |   <  |   >  |      |                    |      |   +  |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |   {  |   }  |   (  |   )  |      |-------.    ,-------|      |   -  |   _  |   =  |   |  |      |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      |   [  |   ]  |      |-------|    |-------|      |      |      |      |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            |      |      |      |      | / BSpc  /       \      \  |      |      |      |      |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
*/
[_RAISE] = LAYOUT( \
  _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, 
  _______, _______, _______, KC_LT,   KC_GT,   _______,                   _______, KC_PLUS, _______, _______, _______, _______, 
  _______, KC_LCBR, KC_RCBR, KC_LPRN, KC_RPRN, _______,                   _______, KC_MINS, KC_UNDS, KC_EQL,  KC_PIPE, _______,
  _______, _______, _______, KC_LBRC, KC_RBRC, _______, _______, _______, _______, _______, _______, _______, KC_BSLS, _______, 
                       _______, _______, _______, _______, KC_BSPC,       _______, _______, _______, _______, _______\
),
/* RAISE - Original
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |   <  |   +  |   >  |      |                    |      |   [  |   =  |   ]  |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |   (  |   -  |   )  |      |-------.    ,-------|      |   {  |   _  |   }  |      |  |   |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      |      |      |      |   \  |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            |      |      |      |      | / BSpc  /       \      \  |      |      |      |      |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
*/
/* [_RAISE] = LAYOUT( \
 *   _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, 
 *   _______, _______, KC_LT,   KC_PLUS, KC_GT,   _______,                   _______, KC_LBRC, KC_EQL,  KC_RBRC, _______, _______, 
 *   _______, _______, KC_LPRN, KC_MINS, KC_RPRN, _______,                   _______, KC_LCBR, KC_UNDS, KC_RCBR, _______, KC_PIPE,
 *   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_BSLS, _______, 
 *                        _______, _______, _______, _______, KC_BSPC,       _______, _______, _______, _______, _______\
 * ),
*/
/* Movement
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                    |      | Home | Pg Dn| Pg Up|  End |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------.    ,-------|      | Left | Down |  Up  | Right|      |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      |      |      |      |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            |      |      |      |      | /       /       \ Del  \  |      |      |      |      |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */
[_MOVEMENT_L] = LAYOUT(
  _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, 
  _______, _______, _______, _______, _______, _______,                   KC_HOME, KC_PGDN, KC_PGUP, KC_END,  _______, _______, 
  _______, _______, _______, _______, _______, _______,                   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______, 
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, 
                 _______,  _______, _______, _______, _______,      KC_DEL, _______,  _______,_______,_______ \
),
/* Movement
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                    |      | Home | Pg Dn| Pg Up|  End |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------.    ,-------|      | Left | Down |  Up  | Right|      |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      |      |      |      |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            |      |      |      |      | /  BSPC /       \      \  |      |      |      |      |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */
[_MOVEMENT_R] = LAYOUT(
  _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, 
  _______, _______, _______, _______, _______, _______,                   KC_HOME, KC_PGDN, KC_PGUP, KC_END,  _______, _______, 
  _______, _______, _______, _______, _______, _______,                   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______, 
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, 
                 _______,  _______, _______, _______, KC_BSPC,      _______, _______,  _______,_______,_______ \
),
/* ADJUST
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | RESET|      |MACWIN|      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |Qwerty|Dvorak|HandDn|      |-------.    ,-------|      |ProgOn|ProgOf| VOLUP|      |      |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      | PREV | PLAY | NEXT |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            |      |      |      |      | /       /       \      \  |      |      |      |      |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */
  [_ADJUST] = LAYOUT( \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  RESET,   XXXXXXX, CG_TOGG, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  XXXXXXX, XXXXXXX, KC_QWRTY,KC_DVRK, KC_HNDWN,XXXXXXX,                   XXXXXXX, PROG_ON, PROG_OFF,KC_VOLU, XXXXXXX, XXXXXXX, \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_MPRV, KC_MPLY, KC_MNXT, XXXXXXX, XXXXXXX, \
                   _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______ \
  )
};

#ifdef OLED_DRIVER_ENABLE

static void render_logo(void) {
    static const char PROGMEM qmk_logo[] = {
        0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
        0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
        0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,0
    };

    oled_write_P(qmk_logo, false);
}

static void print_status_narrow(void) {
    // Print current mode
    oled_write_P(PSTR("\n\n"), false);
    oled_write_ln_P(PSTR("MODE"), false);
    if (IS_LAYER_ON(_DVORAK)) {
        oled_write_ln_P(PSTR("Dvrk"), false);
    } else if (IS_LAYER_ON(_HANDSDOWN)) {
        oled_write_ln_P(PSTR("Hand"), false);
    } else {
        oled_write_ln_P(PSTR("Qwrt"), false);
    }

    if (IS_LAYER_ON(_PROGRAMMER)) {
        oled_write_ln_P(PSTR("Prg"), false);
    } else {
        oled_write_ln_P(PSTR("Num"), false);
    }
    // oled_write_ln_P(PSTR(""), false);
    // if (keymap_config.swap_lctl_lgui) {
    //     oled_write_ln_P(PSTR("MAC"), false);
    // } else {
    //     oled_write_ln_P(PSTR("WIN"), false);
    // }

    // switch (get_highest_layer(default_layer_state)) {
    //     case _QWERTY:
    //         oled_write_ln_P(PSTR("Qwrt"), false);
    //         break;
    //     case _DVORAK:
    //         oled_write_ln_P(PSTR("Dvrk"), false);
    //         break;
    //     case _HANDSDOWN:
    //         oled_write_ln_P(PSTR("Hands"), false);
    //         break;
    //     default:
    //         oled_write_P(PSTR("Undef"), false);
    // }
    oled_write_P(PSTR("\n\n"), false);
    // Print current layer
    oled_write_ln_P(PSTR("LAYER"), false);
    switch (get_highest_layer(layer_state)) {
        case _HANDSDOWN:
        case _DVORAK:
        case _QWERTY:
            oled_write_P(PSTR("Base\n"), false);
            break;
        case _RAISE:
            oled_write_P(PSTR("Raise"), false);
            break;
        case _LOWER:
            oled_write_P(PSTR("Lower"), false);
            break;
        case _ADJUST:
            oled_write_P(PSTR("Adj\n"), false);
            break;
        case _MOVEMENT_L:
        case _MOVEMENT_R:
            oled_write_P(PSTR("Move\n"), false);
            break;
        default:
            oled_write_ln_P(PSTR("Undef"), false);
    }
    oled_write_P(PSTR("\n\n"), false);
    led_t led_usb_state = host_keyboard_led_state();
    oled_write_ln_P(PSTR("CPSLK"), led_usb_state.caps_lock);
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_keyboard_master()) {
        return OLED_ROTATION_270;
    }
    return rotation;
}

void oled_task_user(void) {
    if (is_keyboard_master()) {
        print_status_narrow();
    } else {
        render_logo();
    }
}

#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_QWRTY:
            if (record->event.pressed) {
                layer_off(_DVORAK);
                layer_off(_HANDSDOWN);
                // set_single_persistent_default_layer(_QWERTY);
            }
            return false;
        case KC_DVRK:
            if (record->event.pressed) {
                layer_on(_DVORAK);
                layer_off(_HANDSDOWN);
                // set_single_persistent_default_layer(_DVORAK);
            }
            return false;
        case KC_HNDWN:
            if (record->event.pressed) {
                layer_off(_DVORAK);
                layer_on(_HANDSDOWN);
                // set_single_persistent_default_layer(_HANDSDOWN);
            }
            return false;
        case KC_LOWER:
            if (record->event.pressed) {
                layer_on(_LOWER);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            } else {
                layer_off(_LOWER);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            }
            return false;
        case KC_RAISE:
            if (record->event.pressed) {
                layer_on(_RAISE);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            } else {
                layer_off(_RAISE);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            }
            return false;
        case KC_ADJUST:
            if (record->event.pressed) {
                layer_on(_ADJUST);
            } else {
                layer_off(_ADJUST);
            }
            return false;
        case KC_PRVWD:
            if (record->event.pressed) {
                if (keymap_config.swap_lctl_lgui) {
                    register_mods(mod_config(MOD_LALT));
                    register_code(KC_LEFT);
                } else {
                    register_mods(mod_config(MOD_LCTL));
                    register_code(KC_LEFT);
                }
            } else {
                if (keymap_config.swap_lctl_lgui) {
                    unregister_mods(mod_config(MOD_LALT));
                    unregister_code(KC_LEFT);
                } else {
                    unregister_mods(mod_config(MOD_LCTL));
                    unregister_code(KC_LEFT);
                }
            }
            break;
        case KC_NXTWD:
             if (record->event.pressed) {
                if (keymap_config.swap_lctl_lgui) {
                    register_mods(mod_config(MOD_LALT));
                    register_code(KC_RIGHT);
                } else {
                    register_mods(mod_config(MOD_LCTL));
                    register_code(KC_RIGHT);
                }
            } else {
                if (keymap_config.swap_lctl_lgui) {
                    unregister_mods(mod_config(MOD_LALT));
                    unregister_code(KC_RIGHT);
                } else {
                    unregister_mods(mod_config(MOD_LCTL));
                    unregister_code(KC_RIGHT);
                }
            }
            break;
        case KC_LSTRT:
            if (record->event.pressed) {
                if (keymap_config.swap_lctl_lgui) {
                     //CMD-arrow on Mac, but we have CTL and GUI swapped
                    register_mods(mod_config(MOD_LCTL));
                    register_code(KC_LEFT);
                } else {
                    register_code(KC_HOME);
                }
            } else {
                if (keymap_config.swap_lctl_lgui) {
                    unregister_mods(mod_config(MOD_LCTL));
                    unregister_code(KC_LEFT);
                } else {
                    unregister_code(KC_HOME);
                }
            }
            break;
        case KC_LEND:
            if (record->event.pressed) {
                if (keymap_config.swap_lctl_lgui) {
                    //CMD-arrow on Mac, but we have CTL and GUI swapped
                    register_mods(mod_config(MOD_LCTL));
                    register_code(KC_RIGHT);
                } else {
                    register_code(KC_END);
                }
            } else {
                if (keymap_config.swap_lctl_lgui) {
                    unregister_mods(mod_config(MOD_LCTL));
                    unregister_code(KC_RIGHT);
                } else {
                    unregister_code(KC_END);
                }
            }
            break;
        case KC_DLINE:
            if (record->event.pressed) {
                register_mods(mod_config(MOD_LCTL));
                register_code(KC_BSPC);
            } else {
                unregister_mods(mod_config(MOD_LCTL));
                unregister_code(KC_BSPC);
            }
            break;
        case KC_COPY:
            if (record->event.pressed) {
                register_mods(mod_config(MOD_LCTL));
                register_code(KC_C);
            } else {
                unregister_mods(mod_config(MOD_LCTL));
                unregister_code(KC_C);
            }
            return false;
        case KC_PASTE:
            if (record->event.pressed) {
                register_mods(mod_config(MOD_LCTL));
                register_code(KC_V);
            } else {
                unregister_mods(mod_config(MOD_LCTL));
                unregister_code(KC_V);
            }
            return false;
        case KC_CUT:
            if (record->event.pressed) {
                register_mods(mod_config(MOD_LCTL));
                register_code(KC_X);
            } else {
                unregister_mods(mod_config(MOD_LCTL));
                unregister_code(KC_X);
            }
            return false;
            break;
        case KC_UNDO:
            if (record->event.pressed) {
                register_mods(mod_config(MOD_LCTL));
                register_code(KC_Z);
            } else {
                unregister_mods(mod_config(MOD_LCTL));
                unregister_code(KC_Z);
            }
            return false;
        case TB_SCRL:
            if (record->event.pressed) {
                led_t led_usb_state = host_keyboard_led_state();
                if (!led_usb_state.caps_lock) {
                    register_code(KC_CAPS);
                }
            } else {
                register_code(KC_CAPS);
            }
            return false;
        case PROG_ON:
          layer_on(_PROGRAMMER);
          return false;
          break;
        case PROG_OFF:
          layer_off(_PROGRAMMER);
          return false;
          break;
           
    }
    return true;
}

#ifdef ENCODER_ENABLE

void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    } else if (index == 1) {
        if (clockwise) {
            tap_code(KC_PGDOWN);
        } else {
            tap_code(KC_PGUP);
        }
    }
}

#endif



////////////////////////////////////////////////////////////////////////////////
// Combos
////////////////////////////////////////////////////////////////////////////////
enum combos {
    C_SHIFTS_QWERTY,
    // SHIFTS_DVORAK,
    // TENKEY_QWERTY,
    C_BACKSLASH,
    C_PIPE,
};

const uint16_t PROGMEM shifts_querty_combo[] = {KC_Z, KC_X, COMBO_END};
// const uint16_t PROGMEM shifts_dvorak_combo[] = {KC_SCLN, KC_Q, COMBO_END};
// const uint16_t PROGMEM tenkey_querty_combo[] = {KC_Z, KC_C, COMBO_END};
const uint16_t PROGMEM backslash_combo[]     = {KC_COMM, KC_SLSH, COMBO_END};
const uint16_t PROGMEM pipe_combo[]          = {KC_DOT, KC_SLSH, COMBO_END};



combo_t key_combos[COMBO_COUNT] = {
    [C_SHIFTS_QWERTY] = COMBO(shifts_querty_combo, KC_CAPS),
    // [SHIFTS_DVORAK] = COMBO_ACTION(shifts_dvorak_combo),
    // [SHIFTS_BEKL]   = COMBO_ACTION(shifts_bekl_combo),
    // [TENKEY_QWERTY] = COMBO_ACTION(tenkey_querty_combo),
    [C_BACKSLASH]   = COMBO(backslash_combo, KC_BSLS),
    [C_PIPE]        = COMBO(pipe_combo, KC_PIPE),
};

// void process_combo_event(uint16_t combo_index, bool pressed) {
//     switch(combo_index) {
//         case SHIFTS_QWERTY:
//         case SHIFTS_DVORAK:
//         case SHIFTS_BEKL:
//         if (pressed) {
//             #ifdef AUDIO_ENABLE
//                 PLAY_SONG(tone_caps_lock);
//             #endif //AUDIO_ENABLE
//             tap_code_delay(KC_CAPS,500);
//             // SEND_STRING(SS_TAP(KC_CAP));
//             }
//         break;

//         case TENKEY_QWERTY:
//             if (pressed) {
//                 layer_invert(_TENKEY);
//                 #ifdef AUDIO_ENABLE
//                     if (IS_LAYER_ON(_TENKEY))
//                         PLAY_SONG(tone_tenkey_activate);
//                     else
//                         PLAY_SONG(tone_tenkey_deactivate);
//                 #endif //AUDIO_ENABLE
//             }
//         break;
               
//     }
// }

