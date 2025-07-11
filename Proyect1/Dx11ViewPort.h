#pragma once

#include "ViewPort.h"

#include "Dx11ViewPort.h"
#include "GraphicsAPI.h" 

class Dx11ViewPort : public ViewPort
{
	friend class Dx11GraphicsAPI;
public:
    Dx11ViewPort(int x, int y, int width, int height)
        : m_x(x), m_y(y), m_width(width), m_height(height) {
    }

    virtual ~Dx11ViewPort() {CleanUpResources();}

	uint32_t GetX() const override { return m_x; }
	uint32_t GetY() const override { return m_y; }
	uint32_t GetWidth() const override { return m_width; }
	uint32_t GetHeight() const override { return m_height; }

protected:

    void CleanUpResources() override{}

    uint32_t m_x;
    uint32_t m_y;
    uint32_t m_width;
    uint32_t m_height;
};
