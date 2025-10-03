#include "ConstantBuffer.h"

#define HIGHER_AVAILABLE_SLOT 8

ConstantBuffer::ConstantBuffer()
	:m_slot(0)
{
}

ConstantBuffer ::~ConstantBuffer()
{
	m_slot = 0;
}

void ConstantBuffer::SetSlot(const uint32_t slot)
{
	assert(slot < HIGHER_AVAILABLE_SLOT);
	m_slot = slot;
}
