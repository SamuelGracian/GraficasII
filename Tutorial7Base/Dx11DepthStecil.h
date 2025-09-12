#pragma once

#include "DepthStecil.h"

class Dx11DepthStencil : public DepthStecil
{
public:
	Dx11DepthStencil()
		: m_depthStencil(nullptr)
	{
	};

	~Dx11DepthStencil() = default;

	ID3D11Texture2D* m_depthStencil;
};