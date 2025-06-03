# RP2040-VirtualEEPROM
 This library provides a simple emulation of the EEPROM in the last sector of the flash memory of the RP2040 microcontroller (e.g. Raspberry Pi Pico, Waveshare RP2040-Zero, etc.).  It simulates the behavior of the EEPROM, allowing data to be saved and read between reboots.

---

## 🔧 Features
- Reading and writing individual bytes
- Working with data structures (struct)
- Simple API
- PlatformIO and Arduino support

## 📌 Important to know
- The last 4KB sector of flash memory is used (by default).
- The size of the "virtual EEPROM" is 256 bytes (you can change the value of VirtualEEPROM.h -> EEPROM_SIZE, but not more than 4KB).
- Changes are not saved to flash until commit() is called.

