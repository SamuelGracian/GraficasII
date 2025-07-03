#pragma once
#include "texture.h"
#include "Base.h"


class Dx11Texture2D : public Texture
{
    Dx11Texture2D();
    virtual ~Dx11Texture2D();

    virtual void CleanUpResources() override;

    ID3D11Texture2D* m_texture = nullptr;
    ID3D11ShaderResourceView* m_srv = nullptr;
};
