#pragma once
#include "RenderResource.h"
#include "RasterizerDesc.h"

class RasterizerState : public RenderResource
{
public:
    virtual ~RasterizerState() = default;

   RasterizerState() = default;
};

