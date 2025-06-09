#pragma once
#include <d3d11.h>
#include <memory>

#include "BufferResource.h"


class Dx11VertexBuffer : public BufferResource
{
public:
    Dx11VertexBuffer(ID3D11Device* device, const void* data, size_t size, UINT stride);

    ID3D11Buffer* GetRawBuffer() override { return m_buffer.get(); }

private:
    struct BufferDeleter 
    {
        void operator()(ID3D11Buffer* p) const { if (p) p->Release(); }
    };

    std::shared_ptr<ID3D11Buffer> m_buffer;
    UINT m_vertexSize; // Size of each vertex in bytes
};

//// Define the SimpleVertex structure
//struct SimpleVertex
//{
//	DirectX::XMFLOAT3 Position; // 3D position of the vertex
//	DirectX::XMFLOAT3 Normal;   // Normal vector for lighting calculations
//	DirectX::XMFLOAT2 TexCoord; // Texture coordinates
//};


/// <summary>
/// Interface for DirectX 11 vertex buffers
/// </summary>
class InterDx11VertexBuffers
{
	friend class GraphicsAPI;

public:
	InterDx11VertexBuffers() = default;
	virtual ~InterDx11VertexBuffers() = default;

protected:

	const std::uint32_t GetSlot()
	{
		return m_slot;
	}

	std::uint32_t m_slot;

private:
	
	ID3D11Buffer* m_buffer = nullptr; // DirectX 11 buffer for vertex data
};

