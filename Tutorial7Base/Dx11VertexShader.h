#pragma once
#include "VertexShader.h"
#include <d3d11.h>

class Dx11VertexShader : public VertexShader
{
public:
	Dx11VertexShader();
	~Dx11VertexShader() = default; 

	ID3D11VertexShader* GetShader() const;

private:

	ID3D11VertexShader* m_shader;
};