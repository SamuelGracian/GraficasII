#include "Dx11Topology.h"

Dx11Topology::Dx11Topology()
	: m_dx11Topology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST)
{
    switch (m_type)
    {
    case Topology::Type::TriangleList:
        m_dx11Topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
        break;
    case Topology::Type::TriangleStrip:
        m_dx11Topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;
        break;
    case Topology::Type::LineList:
        m_dx11Topology = D3D11_PRIMITIVE_TOPOLOGY_LINELIST;
        break;
    case Topology::Type::PointList:
        m_dx11Topology = D3D11_PRIMITIVE_TOPOLOGY_POINTLIST;
        break;
    default:
        m_dx11Topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
        break;
    }
}

Dx11Topology::~Dx11Topology()
{
}

D3D11_PRIMITIVE_TOPOLOGY Dx11Topology::GetDx11Topology() const
{
    return m_dx11Topology;
}