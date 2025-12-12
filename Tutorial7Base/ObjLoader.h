#pragma once
#include <string>
#include <vector>
#include <cstdint>
#include <directxmath.h>

using DirectX::XMFLOAT2;
using DirectX::XMFLOAT3;

// Must match the vertex layout used in Source.cpp
struct SimpleVertex
{
    XMFLOAT3 Pos;
    XMFLOAT2 Tex;
};

bool LoadOBJSimple(const std::string& path, std::vector<SimpleVertex>& vertices, std::vector<uint16_t>& indices, std::string& error);