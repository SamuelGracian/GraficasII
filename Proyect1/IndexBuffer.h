#pragma once
#include <d3d11.h>
#include <memory>

#include "BufferResource.h"

class Dx11IndexBuffer : public BufferResource
{
public:
	Dx11IndexBuffer() = default;
	~Dx11IndexBuffer()
	{
		CleanUpResources();
	}

	ID3D11Buffer* GetRawBuffer() override
	{
		return m_buffer.get();
	}
	void CleanUpResources() override
	{
		if (m_buffer)
		{
			m_buffer->Release();
			m_buffer.reset();
		}
	}
	void UpdateBuffer() override;

	UINT GetByteWidth() const override
	{
		return m_byteWidth;
	}

	UINT GetBindFlags() const override
	{
		return D3D11_BIND_INDEX_BUFFER;
	}

	UINT GetIndexCount() const { return m_indexCount; }

private:
	std::shared_ptr<ID3D11Buffer> m_buffer;
	UINT m_indexCount = 0;
	UINT m_byteWidth = 0;
};