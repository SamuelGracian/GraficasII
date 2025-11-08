#include "Dx11ConstantBuffer.h"
#define SAFE_RELEASE(x) if (x) {x -> Release(); x = nullptr;}

Dx11ConstatBuffer::Dx11ConstatBuffer()
	: m_buffer(nullptr)
{
}

Dx11ConstatBuffer::~Dx11ConstatBuffer()
{
	SAFE_RELEASE(m_buffer);
}

