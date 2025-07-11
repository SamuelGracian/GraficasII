#pragma once 
#include "RenderResource.h"
class ViewPort : public RenderResource
{
public:
    ViewPort();
    virtual ~ViewPort();

    virtual uint32_t GetX() const = 0;
    virtual uint32_t GetY() const = 0;
    virtual uint32_t GetWidth() const = 0;
    virtual uint32_t GetHeight() const = 0;
};