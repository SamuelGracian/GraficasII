#pragma once

#include "DepthStencil.h"

class Dx11DepthStencil : public DepthStencil 
{
public:
	Dx11DepthStencil()
		: m_depthStencil(nullptr)
	{
	};

	~Dx11DepthStencil() = default;

	ID3D11Texture2D* m_depthStencil;
};