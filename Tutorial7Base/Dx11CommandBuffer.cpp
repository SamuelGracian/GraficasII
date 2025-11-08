#include "Dx11CommandBuffer.h"
#include <algorithm>
#define SAFE_RELEASE(x) if (x) {x -> Release(); x = nullptr;}
#define HIGHER_AVAILABLE_SLOT 8

Dx11CommandBuffer::Dx11CommandBuffer()
	: m_context(nullptr),
	m_commandList(nullptr)
{
	m_bufferList = std::vector<ID3D11Buffer*>(HIGHER_AVAILABLE_SLOT, nullptr);
}

Dx11CommandBuffer::~Dx11CommandBuffer()
{
	m_bufferList.clear();
	SAFE_RELEASE(m_context);
	SAFE_RELEASE(m_commandList);
}

void Dx11CommandBuffer::BeginCommandBuffer()
{
	assert(m_context != nullptr);

	m_context->ClearState();

	SAFE_RELEASE(m_commandList);

	m_isBufferReady = false;
}


void Dx11CommandBuffer::UpdateConstBuffer(uint32_t Slot, uint32_t bytewidt, const void* data)
{
	if (data == nullptr || Slot >= HIGHER_AVAILABLE_SLOT)
	{
		return;
	}

	if (Slot >= m_constantBufferList.size())
	{
		return;
	}

	auto pbuffer = m_constantBufferList[Slot];

	if (pbuffer == nullptr || pbuffer->GetByteWidth() != bytewidt)
	{
		return;
	}

	pbuffer->UpdateData(data, bytewidt);
	m_isBufferReady = false;
}

void Dx11CommandBuffer::DispatchCommandBufer(std::weak_ptr<CommandBuffer> buffer)
{
	if (m_context == nullptr || buffer.expired())
	{
		return;
	}
	auto Pbuffer = std::static_pointer_cast<Dx11CommandBuffer>(buffer.lock());

	if (Pbuffer == nullptr || Pbuffer->m_commandList == nullptr)
	{
		return;
	}
	m_context->ExecuteCommandList(Pbuffer->m_commandList, false);
}

void Dx11CommandBuffer::CleanState()
{
	assert(m_context != nullptr);

	m_context->ClearState();

	SAFE_RELEASE(m_commandList);

	m_isBufferReady = false;
}

/// <summary>
/// Antes era el DrawRenderElement
/// </summary>
/// <param name="element"></param>
void Dx11CommandBuffer::BindRenderElement(const std::shared_ptr<RenderElement>& element)
{
	if (element == nullptr)
		return;

	auto it = std::find(m_renderElementList.begin(), m_renderElementList.end(), element);
	if (it == m_renderElementList.end())
	{
		m_renderElementList.push_back(element);
		m_isBufferReady = false;
	}
}

void Dx11CommandBuffer::RecordCommandList()
{
	assert(m_context != nullptr);

	if (m_isBufferReady)
	{
		return;
	}

	/// Aqui van todas las instrucciones que se tienen que asignar

	for (uint8_t i = 0; i < HIGHER_AVAILABLE_SLOT; i++)
	{
		auto pbuffer = m_constantBufferList[i];

		if (pbuffer == nullptr)
		{
			continue;
		}
		auto pDX11buffer = std::static_pointer_cast<Dx11ConstatBuffer>(pbuffer);

		if (pDX11buffer == nullptr || pDX11buffer->m_buffer == nullptr || pbuffer->GetSlot() >= HIGHER_AVAILABLE_SLOT)
		{
			continue;
		}

		if (pbuffer->GetUpdatePending())
		{
			m_context->UpdateSubresource(pDX11buffer->m_buffer, 0, nullptr, pbuffer->GetRawData(), 0, 0);
		}

		m_context->VSSetConstantBuffers(pDX11buffer->GetSlot(), 1, &pDX11buffer->m_buffer);
		m_context->PSSetConstantBuffers(pDX11buffer->GetSlot(), 1, &pDX11buffer->m_buffer);
	}


	for (auto& element : m_renderElementList)
	{
		for (uint8_t i = 0; i < HIGHER_AVAILABLE_SLOT; i++)
		{
			auto pbuffer = element->m_constantBufferList[i];

			if (pbuffer == nullptr)
			{
				continue;
			}
			auto pDX11buffer = std::static_pointer_cast<Dx11ConstatBuffer>(pbuffer);

			if (pDX11buffer == nullptr || pDX11buffer->m_buffer == nullptr || pbuffer->GetSlot() >= HIGHER_AVAILABLE_SLOT)
			{
				continue;
			}

			if (pbuffer->GetUpdatePending())
			{
				m_context->UpdateSubresource(pDX11buffer->m_buffer, 0, nullptr, pbuffer->GetRawData(), 0, 0);
			}

			m_context->VSSetConstantBuffers(pDX11buffer->GetSlot(), 1, &pDX11buffer->m_buffer);
			m_context->PSSetConstantBuffers(pDX11buffer->GetSlot(), 1, &pDX11buffer->m_buffer);
		}
	}

	if (FAILED(m_context->FinishCommandList(false, &m_commandList)))
	{
		return;
	}

	m_isBufferReady = true;
}
