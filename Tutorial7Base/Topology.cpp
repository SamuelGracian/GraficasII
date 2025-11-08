#include "Topology.h"

Topology::Topology()
	: m_type(Type::TriangleList)
{
}

void Topology::SetType(Type type)
{
	m_type = type;
}

Topology::Type Topology::GetType() const
{
	return m_type;
}