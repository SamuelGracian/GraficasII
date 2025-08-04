#pragma once
#include "texture.h"

class RenderTarget :public Texture
{
public:
    RenderTarget() = default;

    virtual ~RenderTarget() = default;
};
