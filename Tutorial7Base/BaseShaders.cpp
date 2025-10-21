#include "BaseShaders.h"

BaseShaders::BaseShaders()
	: m_BytecodeLength(0)
{
}

BaseShaders::~BaseShaders()
{
	m_BytecodeLength = 0;
}

void BaseShaders::SetBytercodeLength(const uint32_t bytecodeLength)
{
	m_BytecodeLength = bytecodeLength;
}

uint32_t BaseShaders::GetBytecodeLength() const
{
	return m_BytecodeLength;
}