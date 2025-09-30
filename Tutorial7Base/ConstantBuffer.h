#pragma once
#include "Basebuffers.h"

class ConstanBuffer : public BaseBuffer
{
public:
	ConstanBuffer();

	virtual ~ConstanBuffer();

	void SetSlot(const uint32_t slot);
	
private:
	uint32_t m_slot;
};