#pragma once
class GRAPI
{
public:
	GRAPI() = default;

	virtual ~GRAPI() = default;

	virtual void CleanUpResources() = 0;

	virtual void CreateSwapChain(HWND hwnd = nullptr , uint32_t width = 0, uint32_t height = 0) = 0;
	
	//Buffer functions

	virtual std::shared_ptr<ConstanBuffer> CreateConstantBuffer(const uint32_t bytewidth = 0, const uint32_t slot = 0, void* data = nullptr) = 0;

};

