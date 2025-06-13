#pragma once
#include <d3d11.h>
#include <memory>

#include "BufferResource.h"

class IndexBuffer : public RenderResource
{
public:

	UINT GetIndexCount() const { return m_indexCount; }

private:
	std::shared_ptr<ID3D11Buffer> m_buffer;
	UINT m_indexCount = 0;
	UINT m_byteWidth = 0;
};

class Dx11IndexBuffer final : public IndexBuffer
{
public:
	Dx11IndexBuffer() = default;
	~Dx11IndexBuffer() override = default;
	void CleanUpResources() override
	{
		if (m_buffer)
		{
			m_buffer->Release();
			m_buffer.reset();
		}
	}
private:
	std::shared_ptr<ID3D11Buffer> m_buffer;
};