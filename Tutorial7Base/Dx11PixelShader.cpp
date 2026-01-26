#include "Dx11PixelShader.h"

Dx11PixelShader::Dx11PixelShader()
	: m_shader (nullptr)
{}

ID3D11PixelShader* Dx11PixelShader::GetShader() const
{
	return m_shader;
}