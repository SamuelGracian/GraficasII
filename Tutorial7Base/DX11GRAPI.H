#pragma once
#include <d3d11.h>
#include <vector>
#include <memory>

//_______________________________________________________________
//includes
#include "GRAPI.h"
//Buffers
#include "Dx11ConstantBuffer.h"
#include "Dx11indexBuffer.h"
#include "Dx11VertexBuffer.h"
//Shaders
#include "Dx11PixelShader.h"
#include "Dx11VertexShader.h"
#include "Dx11SwapChain.h"
//_______________________________________________________________

class IndexBuffer;
class  VertexBuffer;
class ConstantBuffer;
class VertexShader;
class PixelShader;

class DepthStencil;

class Dx11GraphicsAPI : public GRAPI
{

public:
	Dx11GraphicsAPI();
	~Dx11GraphicsAPI();

	//Clean up function
	void CleanUpResources() override;

	void CreateSwapChain(HWND hwnd = nullptr, uint32_t width = 0, uint32_t height = 0 ) override;

	std::shared_ptr<Dx11SwapChain>GetSwapChain();

	//Buffer functions
	std::shared_ptr<ConstantBuffer> CreateConstantBuffer(const uint32_t bytewidth = 0,
		const uint32_t slot = 0,
		void* data = nullptr) override;

	std::shared_ptr<IndexBuffer> CreateIndexBuffer(const uint32_t bytewidth = 0,
		void* data = nullptr,
		uint32_t indexcount = 0) override;

	std::shared_ptr<VertexBuffer> CreateVertexBuffer(const uint32_t bytewidth = 0,
		const void* vertices = nullptr) override;

	//Shaders functions
	std::shared_ptr<VertexShader> CreateVertexShader(const void* shaderBytecode, uint32_t bytecodeLenght, ID3D11ClassLinkage* classLink, ID3D11VertexShader* shader) override;

	std::shared_ptr<PixelShader> CreatePixelShader(const void* shaderBytecode, uint32_t bytecodeLenght, ID3D11ClassLinkage* classLink, ID3D11PixelShader* shader) override;

	//DepthStencil
	std::shared_ptr<DepthStencil> CreateDepthStencil(uint32_t width = 0, uint32_t height = 0) override;

	ID3D11Device* m_device;
	ID3D11DeviceContext* m_immediateContext;
//private:
	IDXGISwapChain* m_swapChain;
};