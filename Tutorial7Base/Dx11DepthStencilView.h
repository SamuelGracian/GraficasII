#pragma once
#include "DepthStencilView.h"
#include "d3d11.h"

class Dx11DepthStencilView : public DepthStencilView
{
	friend class Dx11GraphicsAPI;

public:
	Dx11DepthStencilView();

	~Dx11DepthStencilView() = default;

private:
	ID3D11DepthStencilView* m_depthStencilView;
};