#include "Basebuffers.h"

BaseBuffer::BaseBuffer()
	:m_byteWidth (0)
{
}

BaseBuffer::~BaseBuffer()
{
	m_byteWidth = 0;
}

const uint32_t BaseBuffer::GetByteWidth() const
{
	return m_byteWidth;
}

void BaseBuffer::SetByteWidth(const uint32_t bytewidth)
{
	assert(bytewidth != 0);

	m_byteWidth = bytewidth;
}