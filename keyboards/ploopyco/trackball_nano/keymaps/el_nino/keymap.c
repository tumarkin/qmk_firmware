/* Copyright 2021 Colin Lam (Ploopy Corporation)
 * Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
 * Copyright 2019 Sunjun Kim
 * Copyright 2019 Hiroyuki Okada
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

// safe range starts at `PLOOPY_SAFE_RANGE` instead.

// placeholder file so it will compile

// Soft reset and scroll from:
//   https://www.reddit.com/r/ploopy/comments/ojvhru/led_trick_on_macos_making_nano_versatile_as/


uint8_t reset_state = 0;
uint8_t lock_state = 0;
int16_t delta_x = 0;
int16_t delta_y = 0;

// uint8_t keyboard_mouse_mode = 0;
// uint8_t keyboard_trigger_sensitivity = 100;
// uint8_t keyboard_trigger_x = 0;
// uint8_t keyboard_trigger_y = 0;

void keyboard_post_init_user(void) {
    reset_state = host_keyboard_led_state().caps_lock;
    lock_state = host_keyboard_led_state().num_lock; 
}

bool led_update_user(led_t led_state) { 
    if (led_state.caps_lock != reset_state) { 
        reset_keyboard(); 
    } 
    if (led_state.num_lock != lock_state) { 
        delta_x = 0; 
        delta_y = 0; 
    } 

    lock_state = led_state.num_lock; 
    return true; 
}

void process_mouse_user(report_mouse_t *mouse_report, int16_t x, int16_t y) {
    if (lock_state == 1) { 
        delta_x += x; delta_y += y;
        if (delta_x > 60) { mouse_report->h = 1; delta_x = 0; }
        else if (delta_x < -60) { mouse_report->h = -1; delta_x = 0; }
        if (delta_y > 15) { mouse_report->v = -1; delta_y = 0; }
        else if (delta_y < -15) { mouse_report->v = 1; delta_y = 0; } 
    }
    else { 
        mouse_report->x = x; 
        mouse_report->y = y; 

        // keyboard_trigger_x += x;
        // keyboard_trigger_y += y;

        // if ((abs(keyboard_trigger_x + keyboard_trigger_y) > keyboard_trigger_sensitivity) && keyboard_mouse_mode == 0) {
        //     keyboard_trigger_x = 0;
        //     keyboard_trigger_y = 0;
        //     register_mods(mod_config(MOD_LCTL));
        //     register_code(KC_F14);
        //     unregister_code(KC_F14);
        //     unregister_mods(mod_config(MOD_LCTL));
        // }
    } 
}
