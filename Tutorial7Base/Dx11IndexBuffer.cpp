#include "Dx11IndexBuffer.h"

Dx11IndexBuffer::Dx11IndexBuffer()
	: m_buffer (nullptr)
{}

ID3D11Buffer* Dx11IndexBuffer::GetBuffer() const
{
	return m_buffer;
}