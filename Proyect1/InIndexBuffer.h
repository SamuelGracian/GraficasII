#include <d3d11.h>
#include "GraphicsAPI.h"

class IndexBuffers
{
public:
	IndexBuffers() = default;
	virtual void CleanUp() = 0;
	virtual void UpdateBuffer() = 0;
protected:

};


class Dx11IndexBuffer : public IndexBuffers
{
	friend class GraphicsAPI;
public:

	Dx11IndexBuffer() = default;

	void CreateBuffer(ID3D11Device* device, UINT indexCount)
	{
		m_indexCount = indexCount;
		D3D11_BUFFER_DESC bufferDesc = {};
		bufferDesc.Usage = D3D11_USAGE_DEFAULT;
		bufferDesc.ByteWidth = sizeof(UINT) * indexCount;
		bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bufferDesc.CPUAccessFlags = 0;
		HRESULT hr = device->CreateBuffer(&bufferDesc, nullptr, &m_buffer);
		if (FAILED(hr))
			throw std::runtime_error("Failed to create index buffer");
	}

	void CleanUp() override
	{
		if (m_buffer)
		{
			m_buffer->Release();
			m_buffer = nullptr;
		}
	}

	void UpdateBuffer() override
	{
		// Something will go here  some day
	}

protected:
	ID3D11Buffer* m_buffer = nullptr;
	UINT m_indexCount = 0;
	UINT m_offset = 0;
	UINT m_stride = sizeof(UINT);

};