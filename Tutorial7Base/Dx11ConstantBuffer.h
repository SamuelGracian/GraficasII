#pragma once
#include "ConstantBuffer.h"
#include "DX11GRAPI.h"

class Dx11ConstantBuffer : public ConstantBuffer
{
	friend class Dx11GraphicsAPI;

public:
	Dx11ConstantBuffer();

	~Dx11ConstantBuffer();

//private:
	ID3D11Buffer* m_buffer;
};