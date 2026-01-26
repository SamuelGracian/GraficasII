#pragma once
#include <cstdint>
#include <cassert>

class BaseBuffer
{
public:
	BaseBuffer();

	virtual ~BaseBuffer();

	void SetByteWidth(const uint32_t bytewidth = 0);

	const uint32_t GetByteWidth()const;

protected:
	uint32_t m_byteWidth;

};