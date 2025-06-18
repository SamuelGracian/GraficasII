#pragma once

#include "BufferResource.h"

class ConstantBuffer : public BufferResource
{
public:
	ConstantBuffer():
	m_slot(0)
	{};

	virtual ~ConstantBuffer () = default;

	uint32_t m_slot;
};

class Dx11ConstantBuffer  final : public ConstantBuffer
{
	friend class Dx11GraphicsAPI;

public:
	Dx11ConstantBuffer();

	~Dx11ConstantBuffer();

	virtual void CleanUpResources() override;

	ID3D11Buffer* m_buffer;
};


