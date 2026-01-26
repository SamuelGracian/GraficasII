#pragma once
#include "Vertexbuffer.h"
#include "d3d11.h"

class Dx11VertexBuffer : public VertexBuffer
{
public:
	Dx11VertexBuffer();

	~Dx11VertexBuffer() = default;

protected:

	ID3D11Buffer* GetBuffer() const;

private:

	ID3D11Buffer* m_buffer;
};