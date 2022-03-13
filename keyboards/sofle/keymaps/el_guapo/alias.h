#ifndef alias_h_INCLUDED
#define alias_h_INCLUDED

// QWERTY HOME ROW ALIASES
// Left-hand home row mods
#define QWRT_A  LCTL_T(KC_A)
#define QWRT_S  LALT_T(KC_S)
#define QWRT_D  LGUI_T(KC_D)
#define QWRT_F  LSFT_T(KC_F)
// Right-hand home row mods
#define QWRT_J  RSFT_T(KC_J)
#define QWRT_K  RGUI_T(KC_K)
#define QWRT_L  LALT_T(KC_L)
#define QWRT_SC RCTL_T(KC_SCLN)
// // 10 key toggles
// #define QWRT_G LT(_TENKEY, KC_G)
// #define QWRT_R LT(_TENKEY, KC_R)


// DVORAK HOME ROW ALIASES
// Left-hand home row mods
#define DVRK_A LCTL_T(KC_A)
#define DVRK_O LALT_T(KC_O)
#define DVRK_E LGUI_T(KC_E)
#define DVRK_U LSFT_T(KC_U)
// Right-hand home row mods
#define DVRK_H RSFT_T(KC_H)
#define DVRK_T RGUI_T(KC_T)
#define DVRK_N LALT_T(KC_N)
#define DVRK_S RCTL_T(KC_S)
// // 10 key toggles
// #define DVRK_P LT(_TENKEY, KC_P)
// #define DVRK_I LT(_TENKEY, KC_I)

// HANDS DOWN HOME ROW ALIASES
// Left-hand home row mods
#define HNDS_R LCTL_T(KC_R)
#define HNDS_S LALT_T(KC_S)
#define HNDS_N LGUI_T(KC_N)
#define HNDS_T LSFT_T(KC_T)
// Right-hand home row mods
#define HNDS_U RSFT_T(KC_U)
#define HNDS_E RGUI_T(KC_E)
#define HNDS_I LALT_T(KC_I)
#define HNDS_A RCTL_T(KC_A)
// // 10 key toggles
// #define HNDS_G LT(_TENKEY, KC_G)
// #define HNDS_P LT(_TENKEY, KC_P)

// Mouse key aliases
#define MS_AC_0 KC_MS_ACCEL0
#define MS_AC_1 KC_MS_ACCEL1
#define MS_AC_2 KC_MS_ACCEL2
#define HYP_F15 HYPR(KC_F15)
#define SH_BTN1 S(KC_BTN1)
#define SH_BTN2 S(KC_BTN2)
#define OP_BTN1 G(KC_BTN1)
#define OP_BTN2 G(KC_BTN2)

// Custom key shortcuts
// #define PROG_TG TG(_PROGRAMMER)
// #define FUNC_MO MO(_FUNCTIONS)
// #define MOUS_MO MO(_MOUSE)
#define SPC_MVL  LT(_MOVEMENT_L, KC_SPC)
#define SPC_MVR  LT(_MOVEMENT_R, KC_SPC)
// #define ESC_MO  LT(_MOUSE, KC_ESC)


#endif // alias_h_INCLUDED

// Navigation
#define KC_BACK G(KC_LBRC)
#define KC_FWD  G(KC_RBRC)
#define KC_PREV G(KC_LCBR)
#define KC_NEXT G(KC_RCBR)

// Buttons
#define SH_BTN1 S(KC_BTN1)
#define SH_BTN2 S(KC_BTN2)
#define OP_BTN1 G(KC_BTN1)
#define OP_BTN2 G(KC_BTN2)
#define HYP_F15 HYPR(KC_F15)

#define TD_BALL TD(TB_UTIL)
