#pragma once
#include "Basebuffers.h"

class VertexBuffer : public BaseBuffer
{
public:
	VertexBuffer() = default;

	~VertexBuffer() = default;

	void SetVetices(const uint32_t vertices);

	uint32_t GetVertices() const;

private:
	uint32_t m_Vertices;

};
///TO DO
/// Return Num Vertices
/// Get / set vertices