#pragma once
#include <d3d11.h>
#include <memory>
#include <DirectXMath.h>

#include "BufferResource.h"

using namespace DirectX;

// Define the SimpleVertex structure
struct SimpleVertex
{
	DirectX::XMFLOAT3 Position; // 3D position of the vertex
	DirectX::XMFLOAT3 Normal;   // Normal vector for lighting calculations
	DirectX::XMFLOAT2 TexCoord; // Texture coordinates
};

class Dx11vertexBuffer : public BufferResource
{
public:
	Dx11vertexBuffer() = default;
	~Dx11vertexBuffer()
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
		return D3D11_BIND_VERTEX_BUFFER;
	}

	UINT GetVertexCount() const { return m_vertexCount; }
private:

	std::shared_ptr<ID3D11Buffer> m_buffer;;
	UINT m_vertexCount = 0;
	UINT m_byteWidth = 0;

};