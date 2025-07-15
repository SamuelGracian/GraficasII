#pragma once
#include "RenderResource.h"

class Texture : public RenderResource
{
public:
    Texture()
        : m_width(0), m_height(0), m_mipLevels(1) {
    }
    virtual ~Texture() {}
    uint32_t GetWidth() const { return m_width; }
    uint32_t GetHeight() const { return m_height; }
    uint32_t GetMipLevels() const { return m_mipLevels; }

public:
    uint32_t m_width;
    uint32_t m_height;
    uint32_t m_mipLevels;
};

class ShaderResourceTexture : public Texture
{
public:
    ShaderResourceTexture() = default;
    virtual ~ShaderResourceTexture() = default;
};


class DepthStencilTexture : public Texture
{
public:
    DepthStencilTexture() = default;
    virtual ~DepthStencilTexture() = default;
};

class RenderTarget :public Texture
{
public:
    RenderTarget() = default;

    virtual ~RenderTarget() = default;
};