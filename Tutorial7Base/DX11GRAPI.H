#pragma once
#include <d3d11.h>
#include <vector>
#include <memory>

//_______________________________________________________________
#include "GRAPI.h"
#include "ConstantBuffer.h"

class Dx11GraphicsAPI : public GRAPI
{
public:
	Dx11GraphicsAPI();
	~Dx11GraphicsAPI();

	//Clean up function
	void CleanUpResources()override;

	bool CreateSwapChain(HWND hwnd = nullptr, uint32_t width= 0, uint32_t height = 0 ) override;

	//Buffer functions
	std::shared_ptr<ConstanBuffer> CreateConstantBuffer(const uint32_t bytewidth,const uint32_t slot, void* data) override;

	bool SetConstantBuffer() override;

//private:
	ID3D11Device* m_device;
	ID3D11DeviceContext* m_immediateContext;
	IDXGISwapChain* m_swapChain;
};