#pragma once
#include <cstdint>

class BaseShaders
{
	BaseShaders();
	virtual ~BaseShaders();

	void SetBytercodeLength(const uint32_t bytecodeLength);
	uint32_t GetBytecodeLength() const;

private:
	uint32_t m_BytecodeLength;
};