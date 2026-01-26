#include "Dx11VertexBuffer.h"

Dx11VertexBuffer::Dx11VertexBuffer()
	:  m_buffer(nullptr)
{}

ID3D11Buffer* Dx11VertexBuffer::GetBuffer() const
{
	return m_buffer;
}
