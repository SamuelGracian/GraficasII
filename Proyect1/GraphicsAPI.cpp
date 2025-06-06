#include "GraphicsAPI.h"

GraphicsAPI::GraphicsAPI(ID3D11Device* device)
    : m_device(device)
{
}

std::shared_ptr<GapiBufferResource> GraphicsAPI::CreateVertexBuffer(const void* data, size_t size, UINT stride) {
    return std::make_shared<Dx11VertexBuffer>(m_device, data, size, stride);
}

std::shared_ptr<GapiBufferResource> GraphicsAPI::CreateIndexBuffer(const void* data, size_t size) {
    return std::make_shared<Dx11IndexBuffer>(m_device, data, size);
}

std::shared_ptr<GapiBufferResource> GraphicsAPI::CreateConstantBuffer(size_t size) {
    return std::make_shared<Dx11ConstantBuffer>(m_device, size);
}

