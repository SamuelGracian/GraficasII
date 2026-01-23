#pragma once
#include "VertexShader.h"

class Dx11VertexShader : public VertexShader
{
public:
	Dx11VertexShader();
	~Dx11VertexShader() = default; 

	ID3D11VertexShader* m_shader;
};