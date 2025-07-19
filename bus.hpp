#pragma once
#include <cstdint>
#include <expected>
#include <array>
#include "olc6502.hpp"
#include <print>

const std::size_t KB64 = 64 * 1024;

enum class ErrorCodes
{
	IndexOutOfRange
};

struct MemoryError
{
	ErrorCodes code {};
	std::uint16_t address {};
	bool read_only {false} ;

	void printError(){std::println("Memory Error\n Error Code: {}\n MemAddr: {}\n Read Only: {}",
		code,address,read_only);};
};

class Bus
{
public:
	Bus();

	Olc6502 cpu;
	std::array<std::uint16_t, KB64> ram;

	void write(std::uint16_t address, std::uint8_t data);
	std::expected<std::uint8_t, MemoryError> read(std::uint16_t address, bool read_only = {false});
};
