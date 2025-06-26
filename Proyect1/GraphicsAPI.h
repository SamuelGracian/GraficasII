#pragma once

#include "Base.h"
//Buffers

#include "IndexBuffer.h"
#include "VertexBuffer.h"

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


	ID3D11Buffer* BuildBuffer(uint32_t byteWidth = 0, const void* initData = nullptr, uint32_t bindFlag =0);

	std::vector<std::shared_ptr<RenderResource>> RendeResourceList;

	//________________

	HWND							m_wWnd;
	ID3D11Device*					m_device;
	ID3D11DeviceContext*			m_immediateContext;
	IDXGISwapChain*					m_swapChain;
};
