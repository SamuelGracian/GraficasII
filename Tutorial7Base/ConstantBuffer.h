#pragma once
#include "Basebuffers.h"
#include "GRAPI.h"

class ConstantBuffer : public BaseBuffer
{
	friend class GraphicsAPI;
public:
	ConstantBuffer();

	virtual ~ConstantBuffer();

	void SetSlot(const uint32_t slot);

	uint32_t GetSlot() const { return m_slot; }

	const bool GetUpdatePending() const;

	void SetByteWidth(const uint32_t bytewidth);

	void UpdateData(const void* data = nullptr , const uint32_t byteWidth);

	const void* GetRawData() const;
	
private:

	void CreateRawDataBuffer();

private:
	uint32_t m_slot;
	void* m_rawData;
	bool m_isUpdatePending;
};
