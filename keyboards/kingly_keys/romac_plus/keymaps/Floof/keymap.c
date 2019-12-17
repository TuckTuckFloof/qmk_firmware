/* Copyright 2018 Jack Humbert
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

#define BASE 0
#define DIRECTIONAL 1
#define ARROW 2
#define ETCHASKETCH 3

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	[BASE] = LAYOUT(
		KC_F1, KC_F2, KC_F3,
		KC_F4, KC_F5, KC_F6,
		KC_F7, KC_F8, KC_F9,
		KC_TRNS, TG(1), TG(2)
  ),
  
	[DIRECTIONAL] = LAYOUT(
		KC_PSCR, KC_HOME, KC_PGUP,
		KC_INS, KC_END, KC_PGDN,
		KC_DEL, KC_SLEP, KC_WAKE,
	  KC_TRNS, KC_TRNS, TG(3)
	),

  [ARROW] = LAYOUT(
    KC_TRNS, KC_UP, KC_TRNS,
		KC_LEFT, KC_DOWN, KC_RIGHT,
		KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS
  ),

  [ETCHASKETCH] = LAYOUT(
    KC_TRNS, KC_TRNS, KC_ACL2,
		KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_MS_BTN1, KC_TRNS
  )
};

// OLED Stuff
#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_270;  // flips the display 180 degrees if offhand
}

void oled_task_user(void) {
  // Host Keyboard Layer Status
  oled_write_P(PSTR("FloofMac \n\n"), false);
  switch (get_highest_layer(layer_state)) {
    case BASE:
      oled_write_ln_P(PSTR(""), false);
      break;
    case DIRECTIONAL:
      oled_write_ln_P(PSTR("NAV\nCLUST"), false);
      break;
    case ARROW:
      oled_write_ln_P(PSTR("ARROW KEYS"), false);
      break;
    case ETCHASKETCH:
      oled_write_ln_P(PSTR("ETCH-\nA-\nSKET-\nCH"), false);
      break;
    default:
      // Or use the write_ln shortcut over adding '\n' to the end of your string
      oled_write_ln_P(PSTR("Undef"), false);
  }

  // Host Keyboard LED Status
  uint8_t led_usb_state = host_keyboard_leds();
  oled_write_P(IS_LED_ON(led_usb_state, USB_LED_NUM_LOCK) ? PSTR("NLCK ") : PSTR("     "), false);
  oled_write_P(IS_LED_ON(led_usb_state, USB_LED_CAPS_LOCK) ? PSTR("CAPS ") : PSTR("       "), false);
  oled_write_P(IS_LED_ON(led_usb_state, USB_LED_SCROLL_LOCK) ? PSTR("SCRLK") : PSTR("       "), false);
}
#endif

// Rotary Encoder stuff
void encoder_update_user(uint8_t index, bool clockwise) {
  if (index == 0) { /* First encoder */
    if (clockwise) {
      tap_code(KC_MS_LEFT);
    } else {
      tap_code(KC_MS_RIGHT);
    }
  }
}