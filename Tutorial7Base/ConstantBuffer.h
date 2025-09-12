#pragma once
#include "Basebuffers.h"

class ConstanBuffer : public BaseBufer
{
public:
	ConstanBuffer()
		: m_slot(0) 
	{};

	virtual ~ConstanBuffer() = default;

	uint32_t m_slot;
};