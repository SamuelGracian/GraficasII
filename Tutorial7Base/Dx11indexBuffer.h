#pragma once
#include "d3d11.h"
#include "Indexbuffer.h"

class Dx11IndexBuffer : public IndexBuffer
{
public:
	Dx11IndexBuffer();

	~Dx11IndexBuffer() = default;

private:

	ID3D11Buffer* m_buffer;
};