#pragma once
#include <d3d11_1.h>
#include "DepthStencil.h"

class Dx11DepthStencil : public DepthStencil 
{
public:
	Dx11DepthStencil();

	~Dx11DepthStencil() = default;

	ID3D11Texture2D* m_depthStencil;
};