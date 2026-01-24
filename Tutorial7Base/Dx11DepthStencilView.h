#pragma once
#include "DepthStencil.h"
#include "d3d11.h"

class Dx11DepthStencilView : public DepthStencil
{
public:
	Dx11DepthStencilView();

	~Dx11DepthStencilView() = default;

	ID3D11DepthStencilView* m_depthStencilView;
};