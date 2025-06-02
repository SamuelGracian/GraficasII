#pragma once

#include <windows.h>
#include <d3d11_1.h>
#include <directxmath.h>
#include <d3dcompiler.h>
#include <directxcolors.h>
#include <stdexcept>
#include <memory> 

#include "InConstantBuffer.h"
#include "InIndexBuffer.h"
#include "VertexBuffers.h"

class GraphicsAPI
{
public:
    GraphicsAPI() = default;
    ~GraphicsAPI();

    // Buffer creation functions returning weak pointers to their interfaces
    std::weak_ptr<InterDx11ConstantBuffer> CreateConstantBuffer();
    std::weak_ptr<InterDx11IndexBuffer> CreateIndexBuffer();
    std::weak_ptr<InterDx11VertexBuffers> CreateVertexBuffer();

private:


};


