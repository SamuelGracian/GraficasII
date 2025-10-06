#include "Vertexbuffer.h"

void VertexBuffer::SetVetices(const uint32_t vertices)
{
	m_Vertices = vertices;
}

uint32_t VertexBuffer::GetVertices() const
{
	return m_Vertices;
}
