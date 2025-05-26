#pragma once
#include <d3d11.h>
#include <directxmath.h>
#include <stdexcept>

#include "GraphicsAPI.h"

// Define the SimpleVertex structure
struct SimpleVertex
{
	DirectX::XMFLOAT3 Position; // 3D position of the vertex
	DirectX::XMFLOAT3 Normal;   // Normal vector for lighting calculations
	DirectX::XMFLOAT2 TexCoord; // Texture coordinates
};


class InterDx11VertexBuffers
{
	friend  GraphicsAPI;

public:
	InterDx11VertexBuffers() = default;
	virtual ~InterDx11VertexBuffers() = default;

protected:

	virtual void CleanUpResources () override;

private:
	
	ID3D11Buffer* m_buffer = nullptr; // DirectX 11 buffer for vertex data
};



class DX11VertexBuffers : public InterDx11VertexBuffers
{
public:

	DX11VertexBuffers() = default;
	~DX11VertexBuffers() = default;

private:
	const std::uint32_t GetSlot() const
	{
		return m_slot;
	}
protected:
	std::uint32_t m_slot;

};

//
//ID3D11Buffer* m_buffer = nullptr;
//UINT m_byteWidth = 0;
//UINT m_stride = 0;
//UINT m_offset = 0;
//UINT m_vertexCount = 0;
//UINT m_indexCount = 0;
//};
//