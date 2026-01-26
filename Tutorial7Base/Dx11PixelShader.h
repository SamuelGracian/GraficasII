#pragma once
#include "PixelShader.h"
#include <d3d11.h>

class Dx11PixelShader : public PixelShader
{
public:
	Dx11PixelShader();

	~Dx11PixelShader() = default;

//private:

	ID3D11PixelShader* m_shader;
};