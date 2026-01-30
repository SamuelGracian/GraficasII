#pragma once
#include "d3d11.h"
#include "ViewPort.h"

class Dx11ViewPort : public ViewPort
{
public:
	Dx11ViewPort();
	~Dx11ViewPort();

	D3D11_VIEWPORT* m_ViewPort;

};