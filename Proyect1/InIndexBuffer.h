#pragma once
#include <d3d11.h>
#include <wrl/client.h>  // Para ComPtr
#include <cstdint>
#include <vector>

#include "GraphicsAPI.h"
#include "GapiRenderResources.h"

namespace wrl = Microsoft::WRL;

class InterDx11IndexBuffer : public GapiRenderResources {
    friend class GraphicsAPI;

public:
    InterDx11IndexBuffer() = default;
    virtual ~InterDx11IndexBuffer() = default;

    //______Public methots______
    void Bind() const;  
    uint32_t GetIndexCount() const { return m_indexCount; }
    DXGI_FORMAT GetFormat() const { return m_format; }

protected:
    virtual void CleanUpResources() override {
        m_buffer.Reset();
        m_indexCount = 0;
    }

private:
    wrl::ComPtr<ID3D11Buffer> m_buffer;
    uint32_t m_indexCount = 0;
    DXGI_FORMAT m_format = DXGI_FORMAT_R16_UINT;
};
