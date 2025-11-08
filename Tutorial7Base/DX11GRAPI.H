#pragma once
#include <d3d11.h>
#include <vector>
#include <memory>
#include <string>

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
//Depth stencil
#include "Dx11DepthStecil.h"
//command buffer
#include "Dx11CommandBuffer.h"
//Pass
#include "Pass.h"

#if defined (DEBUG) || defined (_DEBUG)

#if !defined(ASSIGN_DEBUG_NAME)
#   define ASSIGN_DEBUG_NAME(t, a)                                                                  \
   if (a)                                                                                          \
    {                                                                                               \
        std::string n = typeid(t).name();                                                                \
        a->SetPrivateData(WKPDID_D3DDebugObjectName, static_cast<uint32_t>(n.size()), n.c_str());     \
    }
#endif

#else 

#if !defined(ASSIGN_DEBUG_NAME)
#   define ASSIGN_DEBUG_NAME(s, a)                                                                  \

#endif

#endif // DEBUG



//_______________________________________________________________

class IndexBuffer;
class  VertexBuffer;
class ConstantBuffer;
class VertexShader;
class PixelShader;
class DepthStencil;
class CommandBuffer;

class Dx11GraphicsAPI : public GRAPI
{

public:
	Dx11GraphicsAPI();
	~Dx11GraphicsAPI();

	//Clean up function
	void CleanUpResources() override;

	void CreateSwapChain(HWND hwnd = nullptr, uint32_t width = 0, uint32_t height = 0) override;

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

	//Setbuffers
	void SetConstantBuffer(std::weak_ptr<ConstantBuffer> buffer) override;

	//update buffers
	void UpdateConstantBuffer(std::weak_ptr<ConstantBuffer> buffer, const uint32_t bytewidth, void* Data = nullptr) override;

	//Command Buffers
	virtual std::shared_ptr<CommandBuffer> CreateCommandBuffer() override; 

	virtual  void DispatchCommandBufer(std::weak_ptr<CommandBuffer> buffer) override;

	virtual void RenderPass(std::weak_ptr<Pass> pase) override;

	//Shaders functions
	//Create shaders
	std::shared_ptr<VertexShader> CreateVertexShader(const void* shaderBytecode, uint32_t bytecodeLenght) override;

	std::shared_ptr<PixelShader> CreatePixelShader(const void* shaderBytecode, uint32_t bytecodeLenght) override;

	//Set shaders
	void SetVertexShader(std::weak_ptr<VertexShader> shader) override;

	//DepthStencil
	std::shared_ptr<DepthStencil> CreateDepthStencil(uint32_t width = 0, uint32_t height = 0) override;

	ID3D11Device* m_device;

	ID3D11DeviceContext* m_immediateContext;

private:
	IDXGISwapChain* m_swapChain;
};