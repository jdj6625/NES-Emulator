#include "bus.hpp"

Bus::Bus()
{
   cpu.connectBus(this);
}

void Bus::write(std::uint16_t address, std::uint8_t data)
{
   if (0x0000 <= address && address <= 0xFFFF)
      ram[address] = data;
}

std::expected<std::uint8_t, MemoryError> Bus::read(std::uint16_t address, bool read_only)
{
   if (0x0000 <= address && address < 0xFFFF)
      return ram[address];
   else
   {
      return std::unexpected(MemoryError{ErrorCodes::IndexOutOfRange, address, read_only});
   }
}
