#pragma once
#include <d3d11.h>
#include <directxmath.h>
#include <stdexcept>

class VertexBuffers
{
public:
	VertexBuffers() = default;
	virtual void CleanUp() = 0;
	virtual void UpdateBuffer() = 0;

protected:
	ID3D11Buffer* m_buffer = nullptr;
	UINT m_byteWidth = 0;
	UINT m_stride = 0;
	UINT m_offset = 0;
	UINT m_vertexCount = 0;
	UINT m_indexCount = 0;
};

// Define the SimpleVertex structure
struct SimpleVertex
{
	DirectX::XMFLOAT3 Position; // 3D position of the vertex
	DirectX::XMFLOAT3 Normal;   // Normal vector for lighting calculations
	DirectX::XMFLOAT2 TexCoord; // Texture coordinates
};


class DX11VertexBuffers : public VertexBuffers
{
public:
	DX11VertexBuffers(ID3D11Device* device, UINT vertexCount, UINT indexCount)
		: m_vertexCount(vertexCount), m_indexCount(indexCount)
	{
		SimpleVertex* vertices = new SimpleVertex[vertexCount];
		D3D11_BUFFER_DESC bufferDesc = {};
		bufferDesc.Usage = D3D11_USAGE_DEFAULT;
		bufferDesc.ByteWidth = sizeof(SimpleVertex) * vertexCount;
		bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bufferDesc.CPUAccessFlags = 0;
		D3D11_SUBRESOURCE_DATA initData = {};
		initData.pSysMem = vertices;
		HRESULT hr = device->CreateBuffer(&bufferDesc, &initData, &m_buffer);
		if (FAILED(hr))
			throw std::runtime_error("Failed to create vertex buffer");
	}
	virtual void CleanUp() override
	{
		if (m_buffer)
			m_buffer->Release();
	}

protected:
	ID3D11Buffer* m_buffer = nullptr;
	UINT m_byteWidth = 0;
	UINT m_stride = 0;
	UINT m_offset = 0;
	UINT m_vertexCount = 0;
	UINT m_indexCount = 0;
};