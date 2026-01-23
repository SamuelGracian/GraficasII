#pragma once
#include "PixelShader.h"

class Dx11PixelShader : public PixelShader
{
public:
	Dx11PixelShader();

	~Dx11PixelShader() = default;

	ID3D11PixelShader* m_shader;
};