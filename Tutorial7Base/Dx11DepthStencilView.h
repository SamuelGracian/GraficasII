#pragma once
#include "DepthStencil.h"

class Dx11DepthStencilView : public DepthStencil
{
public:
	Dx11DepthStencilView()
		: m_depthStencilView(nullptr)
	{};
	~Dx11DepthStencilView() = default;

	ID3D11DepthStencilView* m_depthStencilView;
};