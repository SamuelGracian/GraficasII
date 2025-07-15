#pragma once 
#include "RenderResource.h"
class ViewPort : public RenderResource
{
public:
    ViewPort() : m_x(0), m_y(0), m_width(0), m_height(0)
    {};
    virtual ~ViewPort() = default;

    uint32_t m_x;
    uint32_t m_y;
    uint32_t m_width;
    uint32_t m_height;
};