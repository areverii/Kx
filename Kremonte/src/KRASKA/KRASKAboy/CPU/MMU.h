#pragma once

#include "Address.h"
#include "../Base/Options.h"
#include "../Cartridge/Cartridge.h"

#include <vector>
#include <memory>

class KRASKAboy;

class MMU {
public:
    MMU(KRASKAboy& inGb, Options& options);

    auto read(const Address& address) const -> u8;
    void write(const Address& address, u8 byte);

private:
    auto boot_rom_active() const -> bool;

    auto read_io(const Address& address) const -> u8;
    void write_io(const Address& address, u8 byte);

    auto unmapped_io_read(const Address& address) const -> u8;
    void unmapped_io_write(const Address& address, u8 byte);

    void dma_transfer(u8 byte);

    KRASKAboy& gb;
    Options& options;

    std::vector<u8> work_ram;
    std::vector<u8> oam_ram;
    std::vector<u8> high_ram;

    ByteRegister disable_boot_rom_switch;

    friend class Debugger;
};
