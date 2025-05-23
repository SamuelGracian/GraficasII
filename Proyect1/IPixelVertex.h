
#include <d3d11_1.h>
#include <directxmath.h>

using namespace DirectX;

/// <summary>
/// Simple vertex structure
/// </summary>
struct SimpleVertex
{
	// pos - position
    XMFLOAT3 Pos;
	// tex - texture coordinates
    XMFLOAT2 Tex;
};

class IPixelVertex
{
public:
    virtual ~IPixelVertex() = default;
    virtual const XMFLOAT3& GetPosition() const = 0;
    virtual const XMFLOAT2& GetTexCoord() const = 0;
};


class PixelVertex : public IPixelVertex
{
public:
    PixelVertex(const XMFLOAT3& pos, const XMFLOAT2& tex)
        : m_pos(pos), m_tex(tex) {}

    const XMFLOAT3& GetPosition() const override { return m_pos; }
    const XMFLOAT2& GetTexCoord() const override { return m_tex; }

private:
    XMFLOAT3 m_pos;
    XMFLOAT2 m_tex;
};
