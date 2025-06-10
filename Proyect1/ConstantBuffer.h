#pragma once
#include <d3d11.h>
#include <memory>

#include "BufferResource.h"


class Dx11ConstantBuffer : public BufferResource
{
public:
	Dx11ConstantBuffer() = default;

	~Dx11ConstantBuffer()
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
		return D3D11_BIND_CONSTANT_BUFFER;
	}

protected:
	std::shared_ptr<ID3D11Buffer> m_buffer;
	UINT m_byteWidth = 0;
};


