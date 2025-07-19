#pragma once
#include "bus.hpp"
#include <expected>
#include <vector>

class Olc6502 {
public:
   Olc6502();
   void connectBus(const Bus& bus);

   enum class Operation
   {
      SET = 1,
      CLEAR = 0
   };

   enum FLAGS6502
   {
      C = (1 << 0),	// Carry Bit
      Z = (1 << 1),	// Zero
      I = (1 << 2),	// Disable Interrupts
      D = (1 << 3),	// Decimal Mode (unused in this implementation)
      B = (1 << 4),	// Break
      U = (1 << 5),	// Unused
      V = (1 << 6),	// Overflow
      N = (1 << 7),	// Negative
   };

   // Registers
   std::uint8_t a {0x00};
   std::uint8_t x {0x00};
   std::uint8_t y {0x00};
   std::uint8_t stack_ptr {0x00};
   std::uint16_t pc {0x0000};
   std::uint8_t status {0x00};

private:
   // Member Variables
   Bus* bus = nullptr;

   void clock();
   void reset();
   void irq();
   void nmi();
   std::uint8_t fetch() const;
   std::uint8_t fetched_data {0x00};
   std::uint16_t addr_absolute {0x0000};
   std::uint16_t addr_relative {0x0000};
   std::uint8_t opcode {0x00};
   std::uint8_t cycles {0x00};

   std::expected<std::uint8_t, MemoryError> read(std::uint16_t address) const;
   void write(std::uint16_t address, std::uint8_t data);
   std::uint8_t getFlag(FLAGS6502 flag) const;
   void setFlag(FLAGS6502 flag, Operation op);

   struct Instruction
   {
      std::string    name;
      std::uint8_t   (Olc6502::*operate )(void) = nullptr;
      std::uint8_t   (Olc6502::*addrmode)(void) = nullptr;
      std::uint8_t   cycles = 0;
   };

   std::vector<Instruction> lookup;

   // Addressing modes
   std::uint8_t IMP();	std::uint8_t IMM();
   std::uint8_t ZP0();	std::uint8_t ZPX();
   std::uint8_t ZPY();	std::uint8_t REL();
   std::uint8_t ABS();	std::uint8_t ABX();
   std::uint8_t ABY();	std::uint8_t IND();
   std::uint8_t IZX();	std::uint8_t IZY();

   // Opcodes
   std::uint8_t ADC();	std::uint8_t AND();	std::uint8_t ASL();	std::uint8_t BCC();
   std::uint8_t BCS();	std::uint8_t BEQ();	std::uint8_t BIT();	std::uint8_t BMI();
   std::uint8_t BNE();	std::uint8_t BPL();	std::uint8_t BRK();	std::uint8_t BVC();
   std::uint8_t BVS();	std::uint8_t CLC();	std::uint8_t CLD();	std::uint8_t CLI();
   std::uint8_t CLV();	std::uint8_t CMP();	std::uint8_t CPX();	std::uint8_t CPY();
   std::uint8_t DEC();	std::uint8_t DEX();	std::uint8_t DEY();	std::uint8_t EOR();
   std::uint8_t INC();	std::uint8_t INX();	std::uint8_t INY();	std::uint8_t JMP();
   std::uint8_t JSR();	std::uint8_t LDA();	std::uint8_t LDX();	std::uint8_t LDY();
   std::uint8_t LSR();	std::uint8_t NOP();	std::uint8_t ORA();	std::uint8_t PHA();
   std::uint8_t PHP();	std::uint8_t PLA();	std::uint8_t PLP();	std::uint8_t ROL();
   std::uint8_t ROR();	std::uint8_t RTI();	std::uint8_t RTS();	std::uint8_t SBC();
   std::uint8_t SEC();	std::uint8_t SED();	std::uint8_t SEI();	std::uint8_t STA();
   std::uint8_t STX();	std::uint8_t STY();	std::uint8_t TAX();	std::uint8_t TAY();
   std::uint8_t TSX();	std::uint8_t TXA();	std::uint8_t TXS();	std::uint8_t TYA();

   // NOP
   std::uint8_t XXX();

};
