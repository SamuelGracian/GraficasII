#pragma once
#include <cstdint>
class Topology
{
public:
    enum class Type : uint32_t
    {
        TriangleList = 0,
        TriangleStrip = 1,
        LineList = 2,
        PointList = 3
    };

    Topology();

    virtual ~Topology() = default;

	void SetType(Type type);

	Type GetType() const;

protected:
	Type m_type;
};

