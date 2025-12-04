#include "Shader.h"

Shader::Shader(const char* vertexSrc, const char* fragmentSrc)
{
    GLuint vert = CompileShader(GL_VERTEX_SHADER, vertexSrc);
    GLuint frag = CompileShader(GL_FRAGMENT_SHADER, fragmentSrc);

    programID = glCreateProgram();
    if (vert) glAttachShader(programID, vert);
    if (frag) glAttachShader(programID, frag);
    glLinkProgram(programID);

    GLint success = 0;
    glGetProgramiv(programID, GL_LINK_STATUS, &success);
    if (!success)
    {
        char info[1024];
        glGetProgramInfoLog(programID, sizeof(info), nullptr, info);
        std::cerr << "Shader program link error: " << info << std::endl;
        glDeleteProgram(programID);
        programID = 0;
    }

    if (vert) glDeleteShader(vert);
    if (frag) glDeleteShader(frag);
}

Shader::~Shader()
{
    if (programID)
    {
        glDeleteProgram(programID);
    }
}

void Shader::UseShader() const
{
    if (programID)
    {
        glUseProgram(programID);
    }
}

GLuint Shader::CompileShader(GLenum type, const char* src) const
{
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);

    GLint success = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        char info[1024];
        glGetShaderInfoLog(shader, sizeof(info), nullptr, info);
        std::cerr << "Shader compile error: " << info << std::endl;
        glDeleteShader(shader);
        return 0;
    }
    return shader;
}

void Shader::SetMat4(const std::string& name, const float* mat) const
{
    if (!programID || !mat) return;
    GLint loc = glGetUniformLocation(programID, name.c_str());
    if (loc >= 0)
    { 
        glUniformMatrix4fv(loc, 1, GL_FALSE, mat);
    }
}