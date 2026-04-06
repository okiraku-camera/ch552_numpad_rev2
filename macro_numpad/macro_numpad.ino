/**
 * macro_numpad.ino main sketch of Numeric or Macro Keypad program using ch552g.
 * Copyright (c)  Takeshi Higasa, okiraku-camera.tokyo
 * 
 * This software is released under the MIT License.
 * http://opensource.org/licenses/mit-license.php
 * 
 */
#include "USB_hid_composite.h"
#include "hid_keycode.h"
#include "ch552_watchdog.h"
#include "nvm_keymap.h"	

#include "hardware_config.h"	// for hardware dependent constants.

#define numlock_led  11
const uint8_t cols[] = {14, 15, 16, 17};
const uint8_t rows[] = {30, 31, 32, 33, 34};
const uint8_t row_masks[] = {1, 2, 4, 8, 0x10};

// NumLock led connected to P1.1 
#define NUMLOCK_LED_MASK  2

// Initial layout of Numeric keypad.
// This layout is written to NVM on first boot and reset command. User can change the layout by writing to NVM.
const uint16_t text_scan_to_hid[NUM_KEYS] = {
	HID_KEYPAD_NUMLOCK,
	HID_KEYPAD_SLASH,
	HID_KEYPAD_ASTERISK,
	HID_KEYPAD_MINUS,
	HID_KEYPAD_7,
	HID_KEYPAD_8,
	HID_KEYPAD_9,
	HID_KEYPAD_PLUS,
	HID_KEYPAD_4,
	HID_KEYPAD_5,
	HID_KEYPAD_6,
	0,
	HID_KEYPAD_1,
	HID_KEYPAD_2,
	HID_KEYPAD_3,
	HID_KEYPAD_ENTER,
	HID_KEYPAD_0,
	0,
	HID_KEYPAD_PERIOD,
	0
};

// true if sw0 contains numLock code, it means this keyboard is numeric keypad. if false, it is macro keypad. 
bool numeric_keypad = true;

int8_t current_layer = 0;	// 0 or 1. this is used for macropad layer switching.


void write_code_callback(uint8_t sw, uint8_t layer, uint16_t code) {
	if (sw == 0 && code == HID_KEYPAD_NUMLOCK)	// if sw0 is set to numLock code, it is numeric keypad. this is used for initial layout check.
		numeric_keypad = true;
	else if (sw == 0 && code != HID_KEYPAD_NUMLOCK)	// if sw0 is set to other than numLock code, it is macro keypad.
		numeric_keypad = false;
}


// called from USBhandler
void USBStartSuspend() {
	P1 &= ~NUMLOCK_LED_MASK;
}

uint8_t active_macro = 0;	// 0 means no active macro. 1～MACRO_KEY_COUNT means active macro index. this is set when macro key is pressed, and reset when macro code is sent.
uint8_t macro_index = 0;	// Index tracking the current position within the macro sequence referenced by activa_macro.
int8_t macro_delay_count = 0;	// Counter for tracking delay steps in macro execution, used when processing delay codes within a macro sequence.

void key_event(uint8_t switch_num, uint8_t state) {
	if (switch_num < 1 || switch_num > NUM_KEYS )
		return;

	if (active_macro) {
		if (state) {
			macro_index = 0;
			macro_delay_count = 0;
			active_macro = 0;
			kbd_releaseAll();
		}
		return;
	}	
	// get a assigned code of switch_num.
	uint16_t hidcode = read_nvm_code(switch_num - 1, current_layer);
	// 
	if (hidcode != 0) {
		uint8_t code = (uint8_t)hidcode & 0xff;
		uint8_t mod = (hidcode >> 8) & 0xff; 
		if ((code == HID_X_FN1) && state) {	// layer switch key. this is not sent to host, but used for layer switching.
			current_layer ^= 1;
			return;
		}
		if (IS_MACRO_KEYCODE(code)) {
			if (state) {
				active_macro = hidcode - MACRO_KEYCODE_BASE;
				if (macro_ptrs[active_macro] == 0) {	// no macro code.
					active_macro = 0;
					return;
				}
				active_macro++;
				macro_index = 0;
				macro_delay_count = 0;
			}
		} else {
			if (mod && state) {
				send_modifiers(mod, 1);
				delay(20);
			}
			send_key(code, state);
			if (mod && !state) {
				delay(20);
				send_modifiers(mod, 0);
			}
		}
	}
}

#define scan_bytes 3
static uint8_t last_stable[scan_bytes];
static uint8_t last_scan[scan_bytes];
void scan() {
	__data uint8_t keys[scan_bytes];
	__data uint8_t key = 0;
	for(uint8_t row = 0; row < sizeof(rows); row++) {
		P3 &= ~row_masks[row];		// select a row.
		if (row & 1)
			keys[key++] |= (~P1 & 0xf0);
		else
			keys[key] = (~P1 >> 4) & 0x0f;
		P3 |= row_masks[row];		// unselect a row.
		delayMicroseconds(30);		// wait for signal to settle. may be needed for stable scan result.
	}
	
	uint8_t n = 0;
	for(uint8_t i = 0; i < sizeof(keys); i++) {
		// check if current and prev scan results are match.
		if (last_scan[i] != keys[i])
			n++;
		last_scan[i] = keys[i];		// save current result as prev result.
	}
	if (n)
		return;	// no match. may be bounced.

	for(key = 0; key < sizeof(keys); key++, n += 8) {
		uint8_t changes = keys[key] ^ last_stable[key];
		last_stable[key] = keys[key];	// save last-stable state.
		if (changes) {
			uint8_t mask = 1;
			for (uint8_t i = 0; i < 8; i++, mask <<=1 )
				if (changes & mask) key_event(n + i + 1, keys[key] & mask ? 1 : 0);
		}
	}
}

// boot loader entry address is defined in ch5xx.h
void enter_bootloader_mode() {
#if defined(BOOT_LOAD_ADDR)
	digitalWrite(numlock_led, 0);
	USB_CTRL = 0;
	EA = 0; // Disabling all interrupts is required.
	TMOD = 0;
	delay(10);
	__asm__("lcall #0x3800"); // Jump to bootloader code
	for(;;) {}
#endif
}

void build_initial_layout() {
	// build initial layout. this is used when nvm is not valid.
	for(int8_t i = 0; i < NUM_KEYS ; i++) {	
		uint16_t code = text_scan_to_hid[i];
		nvm_write_word(KEYMAP_START + (i << 1), code);				// レイヤー0はテンキー
		nvm_write_word(KEYMAP_START + NUM_KEYS * 2 + (i << 1), 0);	// レイヤー1はすべて0
	}
}

// type_macro_strings() is called repeatedly from loop() by 10msec.  
// When a modifier keycode appears in the macro, send the corresponding modifier-on event.
// When the macro reaches its end, if any modifiers were turned on, send modifier-off events for all of them.
// Modifier-off events at the end are sent regardless of the physical modifier state.
void type_macro_strings() {
	static uint8_t mod = 0;
	static uint8_t seg_start_index = 0xff;	// this is used for tracking the start index of a segment when processing segment start and goto codes in macro. 0xff means no segment start encountered yet.	

	if (macro_delay_count > 0) {
		macro_delay_count--;
		return ;
	}

	if (macro_index == 0)
		seg_start_index = 0xff;

	uint16_t macro_base = macro_ptrs[active_macro - 1];
	if (macro_base == 0) {	// no macro code.
		active_macro = 0;
		macro_delay_count = 0;
		seg_start_index = 0xff;
		return ;
	}
	uint8_t code = eeprom_read_byte(macro_base + macro_index);
	if (code == 0) {	// end of macro code.
		active_macro = 0;
		macro_index = 0;
		macro_delay_count = 0;
		mod = 0;
		seg_start_index = 0xff;
		kbd_releaseAll();
		return ;
	}

	if (code == HID_M_SEGSTART) {
		if (seg_start_index == 0xff) {
			seg_start_index = macro_index;
		}
		macro_index++;
		return ;
	}

	if (code == HID_M_GOTO_SEG) {
		macro_index = (seg_start_index == 0xff) ? 0 : seg_start_index;
		return ;
	}

	if (IS_MACRO_DELAY_CODE(code)) {
		switch (code) {
		case HID_M_DELAY100:
			macro_delay_count = 10;	// set delay count for 100ms.
			break;
		case HID_M_DELAY500:
			macro_delay_count = 50;	// set delay count for 500ms.
			break;
		case HID_M_DELAY1000:
			macro_delay_count = 100;	// set delay count for 1000ms.
			break;
		default:
			macro_delay_count = 0;
		}
		macro_index++;
		return ;
	}

	if (IS_MODIFIER_KEYCODE(code)) { 
		mod |= (1 << ((code - HID_MODIFIERS) & 0x7));	// 0～7 for left mods.
		if ((mod & modifiers) & mod) {	// if some modifiers are already on, send the new modifiers state.	
			send_modifiers(mod, false);
		} else {
			send_modifiers(mod, true);
		}
		delay(20);
	} else {
		send_key(code, 1);
		delay(10);
		send_key(code, 0);
	}
		macro_index++;
	return ;
}

// Clarity is important
void setup() {
	usbhid_init();
	pinMode(numlock_led, OUTPUT);
	digitalWrite(numlock_led, 0);
	for(uint8_t i = 0; i < sizeof(cols); i++)
		pinMode(cols[i], INPUT_PULLUP);
	for(uint8_t i = 0; i < sizeof(rows); i++) {
		pinMode(rows[i], OUTPUT);
		digitalWrite(rows[i], 1);
	}
	init_nvm_keymap();
	if (read_nvm_code(0, 0) != HID_KEYPAD_NUMLOCK)	
		numeric_keypad = false;
	wdt_enable(WDT_TIMEOUT);
}


void loop() {
	static uint8_t led_counter = 0;
	wdt_update();
	if (active_macro)
		type_macro_strings();
	scan();
	delay(10);	// scan interval.
	if (numeric_keypad) {
		if (get_hid_ledstate() & HID_LED_NUMLOCK)
			P1 |= NUMLOCK_LED_MASK;
		else
			P1 &= ~NUMLOCK_LED_MASK;
	} else {
		if (current_layer == 1)	// Fn layer on, light NumLock LED as indicator.
			P1 |= NUMLOCK_LED_MASK;
		else
			P1 &= ~NUMLOCK_LED_MASK;	
	}
}
