#pragma once
#include <vector>
#include <GL/glew.h>

class Mesh
{
public:
    // vertices: interleaved pos.xyz, color.rgb (stride = 6 floats)
    Mesh(const std::vector<float>& vertices, const std::vector<unsigned int>& indices);
    ~Mesh();

    void Draw() const;

private:
	GLuint m_vertexArrayObject = 0; // captures vertex attribute config, position , color
	GLuint m_vertexBufferObject = 0; // raw vertex data
	GLuint m_elementBufferObject = 0; //index data
	GLsizei m_IndexCount = 0; // number of indices to draw
};