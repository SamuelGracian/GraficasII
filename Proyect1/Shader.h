// Shader.h
#pragma once
#include "RenderResource.h"



class PixelShader : public RenderResource
{
    public:
    PixelShader() = default;

    virtual ~PixelShader() = default;
};

class VertexShader :public RenderResource
{
public:
    VertexShader() = default;
    virtual ~VertexShader () = default;
};

class Dx11PixelShader : public PixelShader
{
    friend class Dx11GraphicsAPI;

public:
    Dx11PixelShader() :
        m_shader(nullptr){ }

    ~Dx11PixelShader() { CleanUpResources(); }

protected:

    void CleanUpResources() override;

public:
    ID3D11PixelShader* m_shader;
};

class Dx11VertexShader :public VertexShader
{
    friend class Dx11GraphicsAPI;
public:
    Dx11VertexShader();

    ~Dx11VertexShader() { CleanUpResources(); }

protected:
    void CleanUpResources() override;

public:
    ID3D11PixelShader* m_shader;
    ID3D11InputLayout* m_inputLayout;
};