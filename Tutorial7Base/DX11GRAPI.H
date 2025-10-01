#pragma once
#include <d3d11.h>
#include <vector>
#include <memory>

//_______________________________________________________________
#include "GRAPI.h"
#include "ContainerFiles.h"

class Dx11GraphicsAPI : public GRAPI
{
public:
	Dx11GraphicsAPI();
	~Dx11GraphicsAPI();

	//Clean up function
	void CleanUpResources() override;

	void CreateSwapChain(HWND hwnd = nullptr, uint32_t width = 0, uint32_t height = 0 ) override;

	//Buffer functions
	std::shared_ptr<ConstanBuffer> CreateConstantBuffer(const uint32_t bytewidth = 0,
		const uint32_t slot = 0,
		void* data = nullptr) override;

	std::shared_ptr<IndexBuffer> CreateIndexBuffer(const uint32_t bytewidth = 0,
		void* data = nullptr,
		uint32_t indexcount = 0) override;

	std::shared_ptr<VertexBuffer> CreateVertexBuffer(const uint32_t bytewidth = 0,
		const void* vertices = nullptr) override;


//private:
	ID3D11Device* m_device;
	ID3D11DeviceContext* m_immediateContext;
	IDXGISwapChain* m_swapChain;
};