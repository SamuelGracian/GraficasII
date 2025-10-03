#pragma once
#include "Basebuffers.h"

class ConstantBuffer : public BaseBuffer
{
public:
	ConstantBuffer();

	virtual ~ConstantBuffer();

	void SetSlot(const uint32_t slot);
	
private:
	uint32_t m_slot;
};