#pragma once
class GRAPI
{
public:
	GRAPI() = default;

	virtual ~GRAPI() = default;

	virtual void CleanUpResources() = 0;

	//Buffer functions

	virtual bool CreateSwapChain(HWND hwnd) = 0;

	virtual std::shared_ptr<ConstanBuffer> CreateConstantBuffer(const uint32_t bytewidth = 0, const uint32_t slot = 0, void* data = nullptr) = 0;

	virtual bool SetConstantBuffer() = 0;
};

