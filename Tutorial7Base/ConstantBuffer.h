#pragma once
#include "Basebuffers.h"

class ConstanBuffer : public BaseBuffer
{
public:
	ConstanBuffer();

	virtual ~ConstanBuffer();
	
private:
	uint32_t m_slot;
};