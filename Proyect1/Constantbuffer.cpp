#include "ConstantBuffer.h"

Dx11ConstantBuffer::Dx11ConstantBuffer():
    m_buffer(nullptr)
{
}

Dx11ConstantBuffer::~Dx11ConstantBuffer()
{
    CleanUpResources();
}

void Dx11ConstantBuffer::CleanUpResources()
{
    RELEASE(m_buffer);
}