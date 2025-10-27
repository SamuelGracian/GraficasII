#include "CommandBuffer.h"

CommandBuffer::CommandBuffer()
	: m_isBufferReady(false)
{
	m_constantBufferList = std::vector<std::shared_ptr<ConstantBuffer>>(HIGHER_AVAILABLE_SLOT, nullptr);
	m_PendingConstantBufferData = std::vector<void*>(HIGHER_AVAILABLE_SLOT, nullptr);
}

CommandBuffer::~CommandBuffer()
{
	for (uint8_t i = 0; i < HIGHER_AVAILABLE_SLOT; i++)
	{
		if (m_constantBufferList[i] != nullptr)
		{
			m_constantBufferList[i].reset();
			m_constantBufferList[i] = nullptr;
		}
		if (m_PendingConstantBufferData[i] != nullptr)
		{
			free( m_PendingConstantBufferData[i]);
			m_PendingConstantBufferData[i] = nullptr;
		}
	}
	m_constantBufferList.clear();
	m_PendingConstantBufferData.clear();
}

const bool CommandBuffer::IsbuffReady()
{
	return m_isBufferReady;
}

void CommandBuffer::BindConstBuffer(std::shared_ptr<ConstantBuffer> &buffer)
{

	if (buffer == nullptr || buffer->GetSlot()>=HIGHER_AVAILABLE_SLOT || buffer->GetByteWidth() == 0)
	{
		return;
	}

	if (m_constantBufferList[buffer->GetSlot()])
	{
		delete m_PendingConstantBufferData[buffer->GetSlot()];
	}

	if (m_PendingConstantBufferData[buffer->GetSlot()] != nullptr)
	{
		free(m_PendingConstantBufferData[buffer->GetSlot()]);
	}

	void* PendingData = malloc(buffer->GetByteWidth());

	m_constantBufferList[buffer->GetSlot()] = buffer;
	m_PendingConstantBufferData[buffer->GetSlot()] = PendingData;
	m_isBufferReady = false;
}

const bool CommandBuffer::IsBufferReady() const
{
	return m_isBufferReady;
}