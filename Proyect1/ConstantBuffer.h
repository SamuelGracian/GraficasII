#pragma once


#include "BufferResource.h"

class ConstantBuffer : public BufferResource
{
public:
	ConstantBuffer():
	m_stride (0)
	,m_offset(0)
	,m_slot(0)
	{};

	virtual ~ConstantBuffer () = default;

	uint32_t GetStride() { return m_stride; }

	uint32_t GetOffset() { return m_offset; }

protected:
	uint32_t m_stride;
	uint32_t m_offset;
	uint32_t m_slot;
};

class Dx11ConstantBuffer  final : public ConstantBuffer
{
	friend class Dx11GraphicsAPI;

public:
	Dx11ConstantBuffer();

	~Dx11ConstantBuffer();

	virtual void CleanUpResources() override;

protected:
	ID3D11Buffer* m_buffer;

};


