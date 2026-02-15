#include "Dx11ConstantBuffer.h"
#define SAFE_RELEASE(x) if (x) {x -> Release(); x = nullptr;}

Dx11ConstantBuffer::Dx11ConstantBuffer()
	: m_buffer(nullptr)
{
}

Dx11ConstantBuffer::~Dx11ConstantBuffer()
{
	SAFE_RELEASE(m_buffer);
}

