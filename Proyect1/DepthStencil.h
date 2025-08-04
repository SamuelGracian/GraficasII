#pragma once

#include "texture.h"

class DepthStencilTexture : public Texture
{
public:
    DepthStencilTexture() = default;
    virtual ~DepthStencilTexture() = default;
};