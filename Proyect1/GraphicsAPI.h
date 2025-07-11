#pragma once

#include "Base.h"
#include<d3dcompiler.h>
//Buffers

#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "texture.h"
#include "Sampler.h"

#include "Dx11texture.h"
#include "Dx11Shaders.h"
#include "Dx11Sampler.h"

class ConstantBuffer;

static const uint32_t AvailableSlots = 8;

/// <summary>
/// Base class for graphics API.
/// </summary>
class GraphicsAPI 
{
public:
	GraphicsAPI() = default;

	virtual ~GraphicsAPI() = default;

	virtual void CleanUpResources() = 0;

	virtual std::weak_ptr<ConstantBuffer> CreateConstanBuffer(const uint32_t byteWidth = 0 , 
		const void* initData = nullptr, 
		const uint32_t slot = UINT32_MAX) = 0;

	virtual std::weak_ptr<IndexBuffer> CreateIndexBuffer(const uint32_t byteWidth = 0,
		const void* initData = nullptr,
		uint32_t indexCount=0) = 0;

	virtual std::weak_ptr<VertexBuffer> CreateVertexBuffer(const uint32_t byteWidth = 0,
		const void* vertices = nullptr,
		const uint32_t stride = 0,
		const uint32_t offset =0) = 0;

	virtual std::weak_ptr<Texture> CreateShaderResource(const uint32_t width = 0,
		const uint32_t height = 0,
		const uint32_t mipLevels = 1,
		const void* initData = nullptr) = 0;

	virtual std::weak_ptr<Texture> CreateDepthStencil(const uint32_t width = 0,
		const uint32_t height = 0,
		const uint32_t mipLevels = 1,
		const void* initData = nullptr) = 0;

	virtual std::weak_ptr<Texture> CreateRenderTarget(const uint32_t width = 0,
		const uint32_t height = 0,
		const uint32_t mipLevels = 1,
		const void* initData = nullptr) = 0;
	
	virtual std::weak_ptr<Shader> CreateVertexShader(const uint32_t byteWidth = 0,
		const void* shaderBytecode = nullptr,
		const void* vertices = nullptr,
		const uint32_t stride = 0,
		const uint32_t offset = 0) = 0;

	virtual std::weak_ptr<Shader> CreatePixelShader(const uint32_t byteWidth,
		const uint32_t stride,
		const uint32_t offset) = 0;

	virtual std::weak_ptr<Sampler> CreateSampler() = 0;

	virtual void RenderPase() = 0;
};

/// <summary>
/// API for Dx11
/// </summary>

class Dx11GraphicsAPI : public GraphicsAPI
{
public:
	Dx11GraphicsAPI(HWND windowHandler);

	virtual ~Dx11GraphicsAPI();

	void CleanUpResources() override;

	std::weak_ptr<ConstantBuffer> CreateConstanBuffer(const uint32_t byteWidth = 0, 
		const void* initData = nullptr, 
		const uint32_t slot = UINT32_MAX) override;

	std::weak_ptr<IndexBuffer> CreateIndexBuffer(const uint32_t byteWidth =0,
		const void* initData = nullptr,
		uint32_t indexCount = 0) override;

	std::weak_ptr<VertexBuffer> CreateVertexBuffer(const uint32_t byteWidth = 0,
		const void* vertices = nullptr,
		const uint32_t stride = 0,
		const uint32_t offset = 0
		) override;

	//only reading
	std::weak_ptr<Texture> CreateShaderResource(const uint32_t width = 0,
		const uint32_t height = 0,
		const uint32_t mipLevels = 1,
		const void* initData = nullptr) override;


	//depth mask writting and reading texture
	std::weak_ptr<Texture> CreateDepthStencil(const uint32_t width = 0,
		const uint32_t height = 0,
		const uint32_t mipLevels = 1,
		const void* initData = nullptr) override;

	//writting and reading texture 
	std::weak_ptr<Texture> CreateRenderTarget(const uint32_t width = 0,
		const uint32_t height = 0,
		const uint32_t mipLevels = 1,
		const void* initData = nullptr) override;

	std::weak_ptr<Shader> CreateVertexShader(const uint32_t byteWidth = 0,
		const void* shaderBytecode = nullptr,
		const void* vertices = nullptr,
		const uint32_t stride = 0,
		const uint32_t offset = 0) override;

	std::weak_ptr <Shader> CreatePixelShader(const uint32_t byteWidth,
		const uint32_t stride,
		const uint32_t offset) override;

	std::weak_ptr<Sampler> CreateSampler() override;

	ID3D11Buffer* BuildBuffer(uint32_t byteWidth = 0, const void* initData = nullptr, uint32_t bindFlag =0);

	std::vector<std::shared_ptr<RenderResource>> m_renderResourceList;

	//________________

	HWND							m_wWnd;
	ID3D11Device*					m_device;
	ID3D11DeviceContext*			m_immediateContext;
	IDXGISwapChain*					m_swapChain;
};
