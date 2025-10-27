#include "CommandBuffer.h"

CommandBuffer::CommandBuffer()
	: m_isBufferReady(false)
{
	m_constantBufferList = std::vector<std::shared_ptr<ConstantBuffer>>(HIGHER_AVAILABLE_SLOT, nullptr);
}

CommandBuffer::~CommandBuffer()
{
	m_constantBufferList.clear();
}

const bool CommandBuffer::IsbuffReady()
{
	return m_isBufferReady;
}

void CommandBuffer::BindConstBuffer(std::shared_ptr<ConstantBuffer> &buffer)
{
	m_isBufferReady = false;
	if (buffer == nullptr || buffer->GetSlot()>=HIGHER_AVAILABLE_SLOT)
	{
		return;
	}

	m_constantBufferList[buffer->GetSlot()] = buffer;
}

const bool CommandBuffer::IsBufferReady() const
{
	return m_isBufferReady;
}