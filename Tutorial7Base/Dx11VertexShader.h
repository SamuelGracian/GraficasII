#pragma once
#include "VertexShader.h"

class Dx11VertexShader : public VertexShader
{
public:
	Dx11VertexShader()
		: m_shader(nullptr)

	{};
	~Dx11VertexShader() = default; 

	ID3D11VertexShader* m_shader;
};