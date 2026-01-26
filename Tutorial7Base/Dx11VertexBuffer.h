#pragma once
#include "Vertexbuffer.h"
#include "d3d11.h"

class Dx11VertexBuffer : public VertexBuffer
{
	friend class Dx11GraphicsAPI;

public:
	Dx11VertexBuffer();

	~Dx11VertexBuffer() = default;

//private:

	ID3D11Buffer* m_buffer;
};