#include "ConstantBuffer.h"

#define HIGHER_AVAILABLE_SLOT 8

ConstanBuffer::ConstanBuffer()
	:m_slot(0)
{
}

ConstanBuffer ::~ConstanBuffer()
{
	m_slot = 0;
}

void ConstanBuffer::SetSlot(const uint32_t slot)
{
	assert(slot < HIGHER_AVAILABLE_SLOT);
	m_slot = slot;
}
