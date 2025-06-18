#pragma once

#include "BufferResource.h"

class VertexBuffer : public BufferResource
{
public:
	VertexBuffer()
		: m_stride(0), 
		m_offset(0)	
	{ 
	}
	uint32_t GetOffSet() { return m_offset; }
	uint32_t GetStride() { return m_stride; }

	virtual ~VertexBuffer() = default;


	uint32_t m_stride;
	uint32_t m_offset;
};

class Dx11VertexBuffer final : public VertexBuffer
{
	friend class Dx11GraphicsAPI;
public:
	Dx11VertexBuffer();

	~Dx11VertexBuffer();

	void CleanUpResources() override;

	ID3D11Buffer* m_buffer;
};