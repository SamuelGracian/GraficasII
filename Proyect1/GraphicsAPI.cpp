
#include <memory>
#include "GraphicsAPI.h"

std::weak_ptr<InterDx11ConstantBuffer> GraphicsAPI::CreateConstantBuffer()
{
    auto buffer = std::make_shared<InterDx11ConstantBuffer>();

    return std::weak_ptr<InterDx11ConstantBuffer>(buffer);
}

std::weak_ptr<InterDx11IndexBuffer> GraphicsAPI::CreateIndexBuffer()
{
    auto buffer = std::make_shared<InterDx11IndexBuffer>();

    return std::weak_ptr<InterDx11IndexBuffer>(buffer);
}

std::weak_ptr<InterDx11VertexBuffers> GraphicsAPI::CreateVertexBuffer()
{
    auto buffer = std::make_shared<InterDx11VertexBuffers>();

    return std::weak_ptr<InterDx11VertexBuffers>(buffer);
}

