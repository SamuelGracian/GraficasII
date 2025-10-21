#pragma once
#include "BaseShaders.h"
#include <d3d11_1.h>

class VertexShader
{
public:
	VertexShader() = default;
	~VertexShader() = default;

	ID3D11VertexShader* m_shader;
};