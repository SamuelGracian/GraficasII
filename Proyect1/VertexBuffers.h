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


/// <summary>
/// Interface for DirectX 11 vertex buffers
/// </summary>
class InterDx11VertexBuffers
{
	friend  GraphicsAPI;

public:
	InterDx11VertexBuffers() = default;
	virtual ~InterDx11VertexBuffers() = default;

protected:

	virtual void CleanUpResources () override;

	const std::uint32_t GetSlot()
	{
		return m_slot;
	}

	std::uint32_t m_slot;

private:
	
	ID3D11Buffer* m_buffer = nullptr; // DirectX 11 buffer for vertex data
};

