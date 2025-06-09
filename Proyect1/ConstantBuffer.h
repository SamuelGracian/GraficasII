#pragma once
#include <d3d11.h>
#include <memory>

#include "BufferResource.h"


class Dx11ConstantBuffer : public 
{
public:
    Dx11ConstantBuffer(ID3D11Device* device, size_t size);
    ID3D11Buffer* GetRawBuffer() override { return m_buffer.get(); }

private:
    struct BufferDeleter {
        void operator()(ID3D11Buffer* p) const { if (p) p->Release(); }
    };

    std::shared_ptr<ID3D11Buffer> m_buffer;
};




//#pragma once
//#include <d3d11.h>
//#include <wrl/client.h>  // Para ComPtr
//#include <cstdint>
//#include <stdexcept>
//
//#include "GraphicsAPI.h"
//#include "GapiBuffer.h"
//#include "GapiRenderResources.h"
//
///// <summary>
///// Interface for constant buffers
///// </summary>
//
//namespace wrl = Microsoft::WRL;
//
//class InterDx11ConstantBuffer : public GapiBuffer, public GapiRenderResources {
//    friend class GraphicsAPI;
//
//public:
//    InterDx11ConstantBuffer() = default;
//    virtual ~InterDx11ConstantBuffer() = default;
//
//    //______Métodos Públicos______
//    void UpdateBuffer(const void* data, size_t dataSize);
//    void SetSlot(uint32_t slot) { m_slot = slot; }
//    uint32_t GetSlot() const { return m_slot; }
//
//protected:
//    virtual void CleanUpResources() override {
//        m_buffer.Reset();
//    }
//
//private:
//    wrl::ComPtr<ID3D11Buffer> m_buffer; 
//    uint32_t m_slot = 0;
//};
