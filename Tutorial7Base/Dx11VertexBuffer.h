#pragma once
#include "Vertexbuffer.h"

class Dx11VertexBuffer : public VertexBuffer
{
public:
	Dx11VertexBuffer()
		: m_buffer (nullptr)
	{};

	~Dx11VertexBuffer() = default;

	ID3D11Buffer* m_buffer;
};