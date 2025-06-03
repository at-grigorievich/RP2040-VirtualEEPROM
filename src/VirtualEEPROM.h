#pragma once

#include <Arduino.h>
#include <cstring> 

class VirtualEEPROM
{
    public:
        static constexpr size_t FLASH_SIZE = 0x200000;                              // Waveshare RP2040-Zero total flash size is 2MB
        static constexpr size_t SECTOR_SIZE = 0x1000;                               // Minimal sector size is 4KB
        static constexpr size_t EEPROM_SIZE = 256;                                  // Required virtual EEPROM size

        static constexpr uintptr_t EEPROM_FLASH_OFFSET = FLASH_SIZE - SECTOR_SIZE;  // EEPROM address is last flash sector

        VirtualEEPROM();

        // loading sector into RAM
        void begin();                                                               

        // byte read
        uint8_t read(size_t addr) const;

        // byte write
        void write(size_t addr, uint8_t value);
     
        // Write the entire buffer back to flash
        bool commit();

        template<typename T>
        void writeStruct(size_t addr, const T& data) {
            if (addr + sizeof(T) > EEPROM_SIZE) return;
            memcpy(buffer + addr, &data, sizeof(T));
        }
        
        template<typename T>
        void readStruct(size_t addr, T& data) const {
            if (addr + sizeof(T) > EEPROM_SIZE) return;
            memcpy(&data, buffer + addr, sizeof(T));
        }

    private:
        uint8_t buffer[SECTOR_SIZE]{};
};
