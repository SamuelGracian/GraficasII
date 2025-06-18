#include "VertexBuffer.h"

Dx11VertexBuffer::Dx11VertexBuffer():
	m_buffer(nullptr)
{ 
}

Dx11VertexBuffer::~Dx11VertexBuffer()
{
	CleanUpResources();
}

void Dx11VertexBuffer::CleanUpResources()
{
	RELEASE(m_buffer);
}
