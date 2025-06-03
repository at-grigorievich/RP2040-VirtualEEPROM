#include "VirtualEEPROM.h"
#include <hardware/sync.h>
#include <hardware/flash.h>

VirtualEEPROM::VirtualEEPROM() {}

void VirtualEEPROM::begin() {
    memcpy(buffer, (const void*)(XIP_BASE + EEPROM_FLASH_OFFSET), SECTOR_SIZE);
}

uint8_t VirtualEEPROM::read(size_t addr) const {
    if (addr >= EEPROM_SIZE) return 0xFF;
    return buffer[addr];
}

void VirtualEEPROM::write(size_t addr, uint8_t value) {
    if (addr >= EEPROM_SIZE) return;
    buffer[addr] = value;
}

bool VirtualEEPROM::commit() {
    uint32_t ints = save_and_disable_interrupts();

    flash_range_erase(EEPROM_FLASH_OFFSET, SECTOR_SIZE);
    flash_range_program(EEPROM_FLASH_OFFSET, buffer, SECTOR_SIZE);

    restore_interrupts(ints);
    return true;
}
