#pragma once

#include "Base.h"

#include "RasterizerDesc.h"

class RenderResource;

class ConstantBuffer;

class VertexBuffer;

class IndexBuffer;

class ShaderResourceTexture;

class DepthStencilTexture;

class RenderTarget;

class Shaders;

class Sampler;

class PixelShader;

class VertexShader;

class ViewPort;

class Pase;

class RasterizerState;

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

	virtual std::weak_ptr<ShaderResourceTexture> CreateShaderResource(const uint32_t width = 0,
		const uint32_t height = 0,
		const uint32_t mipLevels = 1,
		const void* initData = nullptr) = 0;

	virtual std::weak_ptr<DepthStencilTexture> CreateDepthStencil(const uint32_t width = 0,
		const uint32_t height = 0,
		const uint32_t mipLevels = 1,
		const void* initData = nullptr) = 0;

	virtual std::weak_ptr<RenderTarget> CreateRenderTarget(const uint32_t width = 0,
		const uint32_t height = 0,
		const uint32_t mipLevels = 1,
		const void* initData = nullptr) = 0;
	
	virtual std::weak_ptr<VertexShader> CreateVertexShader(const uint32_t byteWidth = 0,
		const void* shaderBytecode = nullptr,
		const void* vertices = nullptr,
		const uint32_t stride = 0,
		const uint32_t offset = 0) = 0;

	virtual std::weak_ptr<PixelShader> CreatePixelShader(const uint32_t byteWidth,
		const uint32_t stride,
		const uint32_t offset) = 0;

	virtual std::weak_ptr<Sampler> CreateSampler() = 0;

	virtual std::weak_ptr <ViewPort> CreateViewPort(int x, int y, int width, int height) = 0;

	virtual void RenderPase(Pase& pase) = 0;

	virtual std::weak_ptr<RasterizerState> CreateRasterizer(D3D11_FillMode fillMode, D3D11_CullMode cullMode) = 0;
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
	std::weak_ptr<ShaderResourceTexture> CreateShaderResource(const uint32_t width = 0,
		const uint32_t height = 0,
		const uint32_t mipLevels = 1,
		const void* initData = nullptr) override;


	//depth mask writting and reading texture
	std::weak_ptr<DepthStencilTexture> CreateDepthStencil(const uint32_t width = 0,
		const uint32_t height = 0,
		const uint32_t mipLevels = 1,
		const void* initData = nullptr) override;

	//writing and reading texture 
	std::weak_ptr<RenderTarget> CreateRenderTarget(const uint32_t width = 0,
		const uint32_t height = 0,
		const uint32_t mipLevels = 1,
		const void* initData = nullptr) override;

	std::weak_ptr<VertexShader> CreateVertexShader(const uint32_t byteWidth = 0,
		const void* shaderBytecode = nullptr,
		const void* vertices = nullptr,
		const uint32_t stride = 0,
		const uint32_t offset = 0) override;

	std::weak_ptr <PixelShader> CreatePixelShader(const uint32_t byteWidth,
		const uint32_t stride,
		const uint32_t offset) override;

	std::weak_ptr<Sampler> CreateSampler() override;

	std::weak_ptr<ViewPort> CreateViewPort(int x, int y, int width, int height)  override;

	virtual void RenderPase(Pase& pase) override;

	void SetViewPort(const std::shared_ptr<ViewPort>& viewport);

	std::weak_ptr<RasterizerState> CreateRasterizer(D3D11_FillMode fillMode, D3D11_CullMode cullMode) override;

private:
	ID3D11Buffer* BuildBuffer(uint32_t byteWidth = 0, const void* initData = nullptr, uint32_t bindFlag =0);

	HRESULT CompileShaderFromFile(const WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut);

public:
	//_________________________
	std::vector<std::shared_ptr<RenderResource>> m_renderResourceList;

	//________________________

	HWND							m_wWnd;
	ID3D11Device*					m_device;
	ID3D11DeviceContext*			m_immediateContext;
	IDXGISwapChain*					m_swapChain;

	//_________________________
	std::vector<ID3D11Buffer*> m_constantBuffers;
	std::vector<ID3D11ShaderResourceView*> m_shaderResourceViews;
	std::vector<ID3D11RenderTargetView*> m_renderTargetViews;
	std::vector <ID3D11SamplerState*> m_samplerStates;
};
