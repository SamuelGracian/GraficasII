#pragma once
#include "PrimitiveTopology.h"

class Dx11Topology : public PrimitiveTopology
{
public:
	Dx11Topology();
	~Dx11Topology();
	void SetTopology(ID3D11DeviceContext* context) const override
	{
		context->IASetPrimitiveTopology(m_topology);
	}
private:
	D3D_PRIMITIVE_TOPOLOGY m_topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
};

