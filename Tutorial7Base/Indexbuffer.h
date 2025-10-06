#pragma once
#include "Basebuffers.h"

class IndexBuffer : public BaseBuffer
{
public:
	IndexBuffer() = default;

	~IndexBuffer() = default;

private:
	uint32_t m_Vertices;
};
///TO DO
/// num indices
/// format