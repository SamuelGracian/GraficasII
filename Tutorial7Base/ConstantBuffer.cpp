#include "ConstantBuffer.h"

#define HIGHER_AVAILABLE_SLOT 8

ConstantBuffer::ConstantBuffer()
	:m_slot(0),
	m_rawData(nullptr),
	m_isUpdatePending(false)
{
}

ConstantBuffer ::~ConstantBuffer()
{
	m_slot = 0;
	std::free(m_rawData);
	m_rawData = nullptr;
	m_isUpdatePending = false;
}

void ConstantBuffer::SetSlot(const uint32_t slot)
{
	assert(slot < HIGHER_AVAILABLE_SLOT);
	m_slot = slot;
}

const bool ConstantBuffer::GetUpdatePending() const
{
	return m_isUpdatePending;
}

void ConstantBuffer::SetByteWidth(const uint32_t bytewidth)
{
	assert(bytewidth != 0);

	m_byteWidth = bytewidth;

	CreateRawDataBuffer();
}

void ConstantBuffer::UpdateData(const void* data , const uint32_t byteWidth)
{
	if (data == nullptr || byteWidth != GetByteWidth())
	{
		return;
	}

	memcpy(m_rawData, data, byteWidth);

	m_isUpdatePending = true;
}

const void* ConstantBuffer::GetRawData() const
{
	return m_rawData;
}

void ConstantBuffer::CreateRawDataBuffer()
{
	if (m_rawData != nullptr)
	{
		std::free(m_rawData);
		m_rawData = nullptr;
	}
	m_rawData = std::malloc(m_byteWidth);
}
