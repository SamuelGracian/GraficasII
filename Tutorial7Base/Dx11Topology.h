#pragma once

#include <d3d11.h>
#include "Topology.h"

class Dx11Topology : public Topology
{
	friend class Dx11GraphicsAPI;

public:
	Dx11Topology();
	~Dx11Topology();

	D3D11_PRIMITIVE_TOPOLOGY GetDx11Topology() const;

private:
	D3D11_PRIMITIVE_TOPOLOGY m_dx11Topology;
};

