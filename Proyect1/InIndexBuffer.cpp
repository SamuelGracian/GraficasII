
#include "IndexBuffer.h"

Dx11IndexBuffer::Dx11IndexBuffer() :
	m_buffer(nullptr)
{
}

Dx11IndexBuffer::~Dx11IndexBuffer()
{
	CleanUpResources();
}

void Dx11IndexBuffer::CleanUpResources()
{
	RELEASE(m_buffer);
}