#include "ObjLoader.h"
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>

struct Vec3 { float x,y,z; };
struct Vec2 { float u,v; };

static inline std::vector<std::string> Split(const std::string& s, char delim)
{
    std::vector<std::string> elems;
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) elems.push_back(item);
    return elems;
}

// key: "v/vt" or "v/vt/vn"
static inline std::string MakeKey(int vi, int vti)
{
    return std::to_string(vi) + "/" + std::to_string(vti);
}

bool LoadOBJSimple(const std::string& filename, std::vector<SimpleVertex>& outVertices, std::vector<uint16_t>& outIndices, std::string& outError)
{
    std::ifstream in(filename);
    if (!in.is_open())
    {
        outError = "Failed to open: " + filename;
        return false;
    }

    std::vector<Vec3> positions;
    std::vector<Vec2> texcoords;
    std::string line;

    std::unordered_map<std::string, uint32_t> indexMap;
    std::vector<SimpleVertex> vertices;
    std::vector<uint32_t> indices32;

    while (std::getline(in, line))
    {
        if (line.empty()) continue;
        if (line[0] == '#') continue;

        std::istringstream iss(line);
        std::string token;
        iss >> token;
        if (token == "v")
        {
            Vec3 p; iss >> p.x >> p.y >> p.z;
            positions.push_back(p);
        }
        else if (token == "vt")
        {
            Vec2 t; iss >> t.u >> t.v;
            texcoords.push_back(t);
        }
        else if (token == "f")
        {
            std::vector<std::string> verts;
            std::string vertRef;
            while (iss >> vertRef) verts.push_back(vertRef);

            if (verts.size() < 3) continue;

            auto processVertRef = [&](const std::string& ref)->uint32_t {
                auto parts = Split(ref, '/');
                int vi = 0, vti = 0;
                if (parts.size() >= 1 && !parts[0].empty()) vi = std::stoi(parts[0]);
                if (parts.size() >= 2 && !parts[1].empty()) vti = std::stoi(parts[1]);

                if (vi < 0) vi = (int)positions.size() + vi + 1;
                if (vti < 0) vti = (int)texcoords.size() + vti + 1;

                if (vi == 0 || vi > (int)positions.size())
                {
                    outError = "OBJ: position index out of range in " + ref;
                    throw std::runtime_error(outError);
                }

                std::string key = MakeKey(vi, vti);
                auto it = indexMap.find(key);
                if (it != indexMap.end()) return it->second;

                SimpleVertex sv;
                Vec3 p = positions[vi - 1];
                sv.Pos = DirectX::XMFLOAT3(p.x, p.y, p.z);
                if (vti != 0 && vti <= (int)texcoords.size())
                {
                    Vec2 t = texcoords[vti - 1];
                    sv.Tex = DirectX::XMFLOAT2(t.u, 1.0f - t.v);
                }
                else
                {
                    sv.Tex = DirectX::XMFLOAT2(0.0f, 0.0f);
                }

                uint32_t newIndex = (uint32_t)vertices.size();
                vertices.push_back(sv);
                indexMap.emplace(key, newIndex);
                return newIndex;
            };

            try
            {
                for (size_t i = 1; i + 1 < verts.size(); ++i)
                {
                    uint32_t a = processVertRef(verts[0]);
                    uint32_t b = processVertRef(verts[i]);
                    uint32_t c = processVertRef(verts[i+1]);
                    indices32.push_back(a);
                    indices32.push_back(b);
                    indices32.push_back(c);
                }
            }
            catch (const std::exception& ex)
            {
                outError = ex.what();
                return false;
            }
        }
    }

    if (vertices.size() > 65535u)
    {
        outError = "Too many vertices (>65535). Build with 32-bit index support or reduce mesh.";
        return false;
    }

    outVertices = std::move(vertices);
    outIndices.resize(indices32.size());
    for (size_t i = 0; i < indices32.size(); ++i) outIndices[i] = static_cast<uint16_t>(indices32[i]);

    return true;
}