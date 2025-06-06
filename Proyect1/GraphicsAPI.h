#pragma once
#include <memory>
#include <d3d11.h>

#include "Gapibuffer.h"

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"


class GraphicsAPI 
{
public:
    GraphicsAPI(ID3D11Device* device);

    std::shared_ptr<GapiBufferResource> CreateVertexBuffer(const void* data, size_t size, UINT stride);
    std::shared_ptr<GapiBufferResource> CreateIndexBuffer(const void* data, size_t size);
    std::shared_ptr<GapiBufferResource> CreateConstantBuffer(size_t size);

private:
    ID3D11Device* m_device;
};



