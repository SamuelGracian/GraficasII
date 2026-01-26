#include "Dx11VertexShader.h"

Dx11VertexShader::Dx11VertexShader()
	: m_shader(nullptr)
{}

ID3D11VertexShader* Dx11VertexShader::GetShader() const
{
	return m_shader;
}
