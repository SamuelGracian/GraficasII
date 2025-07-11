#pragma once

#include "Base.h"

class PrimitiveTopology
{
public:
	PrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY topology)
		: m_topology (topology){ }

	~PrimitiveTopology();

	virtual void SetTopology(ID3D11DeviceContext* context) const
	{
		context->IASetPrimitiveTopology(m_topology);
	}

protected:
	D3D_PRIMITIVE_TOPOLOGY m_topology;
};
