
#pragma once
#include <d3d11.h>
#include <memory>

#include "Gapibuffer.h"

class Dx11IndexBuffer : public GapiBufferResource
{
public:
    Dx11IndexBuffer(ID3D11Device* device, const void* data, size_t size);
    void* GetRawBuffer() override { return m_buffer.get(); }

private:
    struct BufferDeleter {
        void operator()(ID3D11Buffer* p) const { if (p) p->Release(); }
    };

    std::shared_ptr<ID3D11Buffer> m_buffer;
};





//namespace wrl = Microsoft::WRL;
//
//class InterDx11IndexBuffer : public GapiRenderResources {
//    friend class GraphicsAPI;
//
//public:
//    InterDx11IndexBuffer() = default;
//    virtual ~InterDx11IndexBuffer() = default;
//
//    //______Public methots______
//    void Bind() const;  
//    uint32_t GetIndexCount() const { return m_indexCount; }
//    DXGI_FORMAT GetFormat() const { return m_format; }
//
//protected:
//    virtual void CleanUpResources() override {
//        m_buffer.Reset();
//        m_indexCount = 0;
//    }
//
//private:
//    wrl::ComPtr<ID3D11Buffer> m_buffer;
//    uint32_t m_indexCount = 0;
//    DXGI_FORMAT m_format = DXGI_FORMAT_R16_UINT;
//};
