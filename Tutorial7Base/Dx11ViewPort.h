#pragma once
#include "d3d11.h"
#include "ViewPort.h"


class Dx11ViewPort : public ViewPort
{
	friend class DX11GRAPI;

public:
	Dx11ViewPort();

	~Dx11ViewPort() = default;

	D3D11_VIEWPORT m_ViewPort;

};