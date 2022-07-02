#include QMK_KEYBOARD_H
#include <stdio.h>
#include "sendstring_us_international.h"
// #include "keymap_us_international.h"

#ifdef PIMORONI_TRACKBALL_ENABLE
#include "drivers/sensors/pimoroni_trackball.h"
#include "pointing_device.h"
#endif

#define _LAYER0 0
#define _LAYER1 1
#define _LAYER2 2
#define _LAYER3 3

enum crkbd_layers {
    LAYER0 = SAFE_RANGE,
    LAYER1,
    LAYER2,
    LAYER3
};

enum custom_keycodes {
    N_MACRO = SAFE_RANGE
};

enum trackball_keycodes {
   BALL_LC = SAFE_RANGE,
   BALL_RC,
   BALL_SCR
};
;
// todo: formatear layouts con el template
// todo: agregar scrolling y left click al trackball
// fixme: oled driver -> probar usar el repo old con cambios para soporte del driver trackball
// fixme: rgb driver -> no tiene los modes

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_LAYER0] = LAYOUT(KC_ESC, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSPC, KC_LCTL, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_LGUI, MO(1), KC_SPC, KC_ENT, MO(2), KC_RALT),

[_LAYER1] = LAYOUT(KC_TAB, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_BSPC, KC_LCTL, KC_LALT, KC_LGUI, LCA(KC_NO), LCAG(KC_NO), KC_PGUP, KC_HOME, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_END, KC_LSFT, KC_F1, KC_F2, KC_F3, KC_F4, KC_PGDN, N_MACRO, KC_F7, KC_F8, KC_F9, KC_F10, KC_CAPS, KC_LGUI, KC_TRNS, KC_SPC, KC_ENT, MO(3), KC_RALT),

[_LAYER2] = LAYOUT(KC_TAB, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC, KC_MUTE, KC_VOLD, KC_VOLU, KC_MRWD, KC_MFFD, KC_F12, KC_MINS, KC_EQL, KC_LBRC, KC_RBRC, KC_BSLS, KC_GRV, KC_LSFT, KC_MPLY, KC_MSTP, KC_BRID, KC_BRIU, KC_F11, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, KC_TILD, KC_LGUI, MO(3), KC_SPC, KC_ENT, KC_TRNS, KC_RALT),

[_LAYER3] = LAYOUT(KC_TAB, KC_PWR, KC_SLEP, KC_WAKE, KC_MPRV, KC_MNXT, KC_F6, KC_P7, KC_P8, KC_P9, KC_F12, KC_BSPC, KC_EJCT, RGB_RMOD, RGB_MOD, RGB_VAD, RGB_VAI, RGB_TOG, KC_F5, KC_P4, KC_P5, KC_P6, KC_F11, EEP_RST, KC_LSFT, RGB_HUD, RGB_HUI, RGB_SAD, RGB_SAI, RGB_M_P, KC_P0, KC_P1, KC_P2, KC_P3, KC_ESC, RESET, KC_LGUI, KC_TRNS, KC_SPC, KC_ENT, KC_TRNS, KC_RALT)

};

/* Template
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |BackSP|
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |LShift|   A  |   S  |   D  |   F  |   G  |                    |   H  |   J  |   K  |   L  |   Ñ  | ´¨{  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |LCTRL |   Z  |   X  |   C  |   V  |   B  |--------.   .-------|   N  |   M  |  ,;  |  .:  |  -_  |AltGr |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                          | LGUI |LOWER | /Space  /       \Enter \  |HIGHER| LAlt |
 *                          |      |      |/       /         \      \ |      |      |
 *                          `---------------------'           '------''-------------'
 */

void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
    layer_on(layer3);
  } else {
    layer_off(layer3);
  }
}

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master()) {
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  }
  return rotation;
}

void oled_render_layer_state(void) {
    oled_write_P(PSTR("Layer: "), false);
    switch (get_highest_layer(layer_state)) {
    case _LAYER0:
        oled_write_ln_P(PSTR("Base"), false);
        break;
    case _LAYER1:
        oled_write_ln_P(PSTR("Navigation"), false);
        break;
    case _LAYER2:
        oled_write_ln_P(PSTR("Symbols"), false);
        break;
    case _LAYER3:
        oled_write_ln_P(PSTR("Adjust"), false);
        break;
    default:
        oled_write_ln_P(PSTR(""), false);
        break;
    }
}

char keylog_str[24] = {};

const char code_to_name[60] = {
    ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
    'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
    'R', 'E', 'B', 'T', '_', '-', '=', '[', ']', '\\',
    '#', ';', '\'', '`', ',', '.', '/', ' ', ' ', ' '};

void set_keylog(uint16_t keycode, keyrecord_t *record) {
  char name = ' ';
    if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) ||
        (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX)) { keycode = keycode & 0xFF; }
  if (keycode < 60) {
    name = code_to_name[keycode];
  }

  // update keylog
  snprintf(keylog_str, sizeof(keylog_str), "%dx%d, k%2d : %c",
           record->event.key.row, record->event.key.col,
           keycode, name);
}

void oled_render_keylog(void) {
    oled_write(keylog_str, false);
}

void render_bootmagic_status(bool status) {
    /* Show Ctrl-Gui Swap options */
    static const char PROGMEM logo[][2][3] = {
        {{0x97, 0x98, 0}, {0xb7, 0xb8, 0}},
        {{0x95, 0x96, 0}, {0xb5, 0xb6, 0}},
    };
    if (status) {
        oled_write_ln_P(logo[0][0], false);
        oled_write_ln_P(logo[0][1], false);
    } else {
        oled_write_ln_P(logo[1][0], false);
        oled_write_ln_P(logo[1][1], false);
    }
}

void oled_render_logo(void) {
    static const char PROGMEM crkbd_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
        0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4,
        0};
    oled_write_P(crkbd_logo, false);
}

bool oled_task_user(void) {
    if (!is_keyboard_master()) {
        oled_render_layer_state();
        oled_render_keylog();
    } else {
        oled_render_logo();
    }
    return true;
}
#endif


void keyboard_post_init_user(void) {
#ifdef PIMORONI_TRACKBALL_ENABLE
    pimoroni_trackball_set_rgbw(0,0,0,80);
#endif
}

bool set_scrolling = false;
report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    if (set_scrolling) {
        mouse_report.h = mouse_report.x;
        mouse_report.v = mouse_report.y;
        mouse_report.x = mouse_report.y = 0;
    }
    return mouse_report;
}


bool process_record_user(uint16_t keycode, keyrecord_t *record){
  switch (keycode){
// #ifdef PIMORONI_TRACKBALL_ENABLE
//     case BALL_RC:
//         record->event.pressed?register_code(KC_BTN2):unregister_code(KC_BTN2);
//         break;
//     case BALL_LC:
//         record->event.pressed?register_code(KC_BTN1):unregister_code(KC_BTN1);
//         break;
//     case BALL_SCR:
//         if(record->event.pressed){
//             set_scrolling = true;
//         // trackball_set_scrolling(true);
//         } else{
//             set_scrolling = false;
//         // trackball_set_scrolling(false);
//         }
//         break;
// #endif
    // case LOWER:
    //     if (record->event.pressed) {
    //         layer_on(_LOWER);
    //         update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
    //     } else {
    //         layer_off(_LOWER);
    //         update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
    //     }
    //     return false;
    // case RAISE:
    //     if (record->event.pressed) {
    //         layer_on(_RAISE);
    //         update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
    //     } else {
    //         layer_off(_RAISE);
    //         update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
    //     }
    //     return false;
    // case ADJUST:
    //     if (record->event.pressed) {
    //         layer_on(_ADJUST);
    //     } else {
    //         layer_off(_ADJUST);
    //     }
    //     return false;
    // break;
  default:
    if (record->event.pressed) {
        if (keycode == N_MACRO) {
            SEND_STRING(SS_LALT("n"));
            SEND_STRING("n");
        }
    }
#ifdef OLED_ENABLE
    if (record->event.pressed) {
        set_keylog(keycode, record);
    }
#endif
    break;
  }
  return true;
}


#ifdef PIMORONI_TRACKBALL_ENABLE
layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
    case _LAYER0:
        pimoroni_trackball_set_rgbw(0,0,0,80);
        break;
    case _LAYER1:
        pimoroni_trackball_set_rgbw(0,153,95,0);
        break;
    case _LAYER2:
        pimoroni_trackball_set_rgbw(153,113,0,0);
        break;
    case _LAYER3:
        pimoroni_trackball_set_rgbw(53,113,150,0);
        break;
    default:
        pimoroni_trackball_set_rgbw(0,0,0,80);
        break;
    }
  return state;
}
#endif
