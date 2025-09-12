#pragma once
#include "ConstantBuffer.h"

class Dx11ConstatBuffer : public ConstanBuffer
{
public:
	Dx11ConstatBuffer()
		: m_buffer(nullptr)
	{};

	~Dx11ConstatBuffer() = default;

	ID3D11Buffer* m_buffer;
};