#pragma once
class Dx11ViewPort
{
public:
    Dx11ViewPort(int x, int y, int width, int height);
    virtual ~Dx11ViewPort();

    void Set(int x, int y, int width, int height) override;

    int GetX() const override { return m_x; }

    int GetY() const override { return m_y; }

    int GetWidth() const override { return m_width; }

    int GetHeight() const override { return m_height; }

private:
    int m_x, m_y, m_width, m_height;
};

