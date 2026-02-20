#pragma once
#include <memory>
#include <d3d11.h>
#include<iostream>
////Buffers
#include "ConstantBuffer.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"
//Shaders
#include "PixelShader.h"
#include "VertexShader.h"
//Depth stencil
#include "DepthStencilView.h"
#include "SwapChain.h"
//topology
#include "Topology.h"
//Render Pass
#include "Pass.h"

//view Port
#include "ViewPort.h"

#include "GRAPIGenerals.h"

class IndexBuffer;
class  VertexBuffer;
class ConstantBuffer;
class VertexShader;
class VertexShader;
class PixelShader;
class CommandBuffer;
class Topology;
class Pass;

class GRAPI
{
public:

	GRAPI() = default;

	virtual ~GRAPI() = default;

	//Clean up function
	virtual void CleanUpResources() = 0;

	//Swap chain function
	virtual std::shared_ptr<SwapChain> CreateSwapChain(HWND hwnd = nullptr, uint32_t width = 0, uint32_t height = 0, GAPI_FORMAT::K = GAPI_FORMAT::FORMAT_UNKNOWN) = 0;
	
	//Buffer functions

	//Create buffers
	virtual std::shared_ptr<ConstantBuffer> CreateConstantBuffer(const uint32_t bytewidth = 0, 
		const uint32_t slot = 0, 
		void* data = nullptr) = 0;

	virtual std::shared_ptr<IndexBuffer> CreateIndexBuffer(const uint32_t bytewidth = 0,
		void* data = nullptr,
		uint32_t indexcount = 0) = 0;

	virtual std::shared_ptr<VertexBuffer> CreateVertexBuffer(const uint32_t bytewidth = 0, 
		const void* vertices = nullptr) = 0;

	//Set buffers
	virtual void SetConstantBuffer(std::weak_ptr<ConstantBuffer> buffer ) = 0;

	//Update buffers
	virtual void UpdateConstantBuffer(std::weak_ptr<ConstantBuffer> buffer, const uint32_t bytewidth, void* Data = nullptr) = 0;

	// Topology
	virtual std::shared_ptr<Topology> CreateTopology(Topology::Type type = Topology::Type::TriangleList) = 0;
	virtual void SetTopology(std::weak_ptr<Topology> topology) = 0;

	//Command buffers
	virtual std::shared_ptr<CommandBuffer> CreateCommandBuffer() = 0;

	virtual void DispatchCommandBufer(std::weak_ptr<CommandBuffer> buffer) = 0;

	//Pass

	virtual std::shared_ptr<Pass> CreatePass() = 0;

	virtual void RenderPass(std::weak_ptr<Pass> pase) = 0;

	//Shader functions
	virtual std::shared_ptr<VertexShader> CreateVertexShader(const std::string& shaderCode ,  const std::string& entrypoint, std::vector<std::string> Defines) = 0;

	virtual std::shared_ptr<PixelShader> CreatePixelShader(const std::string& shaderCode,  const std::string& entrypoint,
		const std::vector< std::string>& Defines = std::vector<std::string>()) = 0;

	virtual void SetVertexShader(std::weak_ptr<VertexShader> shader) = 0;

	//DepthStencil
	virtual std::shared_ptr<DepthStencilView> CreateDepthStencil(uint32_t width = 0, uint32_t height = 0, const GAPI_FORMAT::K format = GAPI_FORMAT::FORMAT_UNKNOWN) = 0;

	virtual void CreateRenderTarget() = 0;

	virtual void SetRenderTarget(const std::weak_ptr <DepthStencilView>& depthStencil ) = 0;

	//View Port
	virtual std::shared_ptr<ViewPort> CreateViewPort(float width, float height, float minDepth, float maxDepth, float topLeftX, float topLeftY) = 0;

protected:
	uint32_t m_shaderModel;

};

/// TO DO
/// Set y update functions
/// 