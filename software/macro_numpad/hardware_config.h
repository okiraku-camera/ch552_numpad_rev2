// macro_numpad.ino main sketch of Numeric or Macro Keypad program using ch552g.
// Copyright (c)  Takeshi Higasa, okiraku-camera.tokyo
// This software is released under the MIT License.
// http://opensource.org/licenses/mit-license.php   

// Hardware dependent constants are defined in this file, such as the number of rows and columns, the eeprom memory map, etc. 
// These constants are used in multiple files, so they are defined in a separate header file.    

#ifndef HARDWARE_CONFIG_H
#define HARDWARE_CONFIG_H

// EEPROM memory map

#define EEPROM_START    0   // start address of EEPROM
#define EEPROM_END      127  // end address of EEPROM. Do not write beyond this.

#define COLS 5
#define ROWS 4
#define NUM_KEYS (COLS * ROWS)
#define NUM_LAYERS 2

#define KEYMAP_START    2   // programable keymap starts at EEPROM_START. After EEPROM_KEYMAP_VALID1 and 2.
#define KEYMAP_SIZE     80  // (NUM_KEYS * NUM_LAYERS * 2) // size of keymap. 2bytes a key.    
#define MACRO_START	    82  // (KEYMAP_START + KEYMAP_SIZE) // macros start after keymap.
#define MACRO_SIZE	    45  // (MACRO_END - MACRO_START)  	  // size of macro storage in bytes.
#define MACRO_END       127 // (EEPROM_END)					  // end of macro storage. Do not write beyond this.
#define RE_COUNT 0	// No RE
#define RE_START 128        // Start address of RE data. After macro code.
// RE data is stored in the order of CW(2bytes), CCW(2bytes) for each RE. 1 RE takes 4 bytes.
// RE that can be pressed is treated as a regular   key switch.  
#endif  // HARDWARE_CONFIG_H