#pragma once
#include "ConstantBuffer.h"
#include "DX11GRAPI.h"

class Dx11ConstatBuffer : public ConstanBuffer
{
	friend class Dx11GraphicsAPI;

public:
	Dx11ConstatBuffer();

	~Dx11ConstatBuffer();

//private:
	ID3D11Buffer* m_buffer;
};