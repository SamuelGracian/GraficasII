#pragma once


enum class D3D11_FillMode
{
    D3D11_FILL_WIREFRAME = 2,
    D3D11_FILL_SOLID = 3
};


enum class D3D11_CullMode
{
    D3D11_CULL_NONE = 1,
    D3D11_CULL_FRONT = 2,
    D3D11_CULL_BACK = 3
};


struct D3D11_RasterizerDesc
{
    D3D11_FillMode FillMode;
    D3D11_CullMode CullMode;
    bool FrontCounterClockwise = false;
    int DepthBias = 0;
    float DepthBiasClamp = 0.0f;
    float SlopeScaledDepthBias = 0.0f;
    bool DepthClipEnable = true;
    bool ScissorEnable = false;
    bool MultisampleEnable = false;
    bool AntialiasedLineEnable = false;
};