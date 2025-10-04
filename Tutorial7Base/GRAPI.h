#pragma once
#include <memory>
#include <d3d11.h>
////Buffers
#include "ConstantBuffer.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"
//Shaders
#include "PixelShader.h"
#include "VertexShader.h"
//Depth stencil
#include "DepthStecil.h"
#include "SwapChain.h"

class IndexBuffer;

class  VertexBuffer;

class ConstantBuffer;

class VertexShader;


class GRAPI
{
public:

	GRAPI() = default;

	virtual ~GRAPI() = default;

	//Clean up function
	virtual void CleanUpResources() = 0;

	//Swap chain function
	virtual void CreateSwapChain(HWND hwnd = nullptr, uint32_t width = 0, uint32_t height = 0) = 0;
	
	//Buffer functions

	virtual std::shared_ptr<ConstantBuffer> CreateConstantBuffer(const uint32_t bytewidth = 0, 
		const uint32_t slot = 0, 
		void* data = nullptr) = 0;

	virtual std::shared_ptr<IndexBuffer> CreateIndexBuffer(const uint32_t bytewidth = 0,
		void* data = nullptr,
		uint32_t indexcount = 0) = 0;

	virtual std::shared_ptr<VertexBuffer> CreateVertexBuffer(const uint32_t bytewidth = 0, 
		const void* vertices = nullptr) = 0;

	//Shader functions
	virtual std::shared_ptr<VertexShader> CreateVertexShader(const void * shaderBytecode, uint32_t bytecodeLenght, ID3D11ClassLinkage* classLInk, ID3D11VertexShader* shader) = 0;

	virtual std::shared_ptr<PixelShader> CreatePixelShader(const void* shaderBytecode, uint32_t bytecodeLenght, ID3D11ClassLinkage* classLink, ID3D11PixelShader* shader) = 0;

	//DepthStencil
	virtual std::shared_ptr<DepthStencil> CreateDepthStencil(uint32_t width = 0, uint32_t height = 0) = 0;
};

