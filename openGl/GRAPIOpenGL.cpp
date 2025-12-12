#include "GRAPIOpenGL.h"

const char* GRAPIOpenGL::vertexSrc = R"(
#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;

uniform mat4 uMVP;

out vec3 vColor;

void main()
{
    vColor = aColor;
    gl_Position = uMVP * vec4(aPos, 1.0);
}
)";

const char* GRAPIOpenGL::fragmentSrc = R"(
#version 330 core
in vec3 vColor;
out vec4 FragColor;
void main()
{
    FragColor = vec4(vColor, 1.0);
}
)";

GRAPIOpenGL::GRAPIOpenGL(int, int, const char*)
    : m_eye{ 2.0f, 2.0f, 2.0f }
    , m_center{ 0.0f, 0.0f, 0.0f }
    , m_up{ 0.0f, 1.0f, 0.0f }
{
}

GRAPIOpenGL::~GRAPIOpenGL()
{
    ShutdownGL();
}

bool GRAPIOpenGL::InitializeGL(GLFWwindow* window)
{
    if (!window)
    {
        std::cout << "GRPIOpenGL:: initializeGL - null window" << std::endl;
        return false;
    }
    m_window = window;

    glfwMakeContextCurrent(m_window);

    glfwGetFramebufferSize(m_window, &m_bufferWidth, &m_bufferHeight);

    if (!InitGLEW())
    {
        return false;
    }

    glViewport(0, 0, m_bufferWidth, m_bufferHeight);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    SetupScene();
    return true;
}


bool GRAPIOpenGL::InitGLEW()
{
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        std::cout << "Failed to initialize GLEW\n";
        return false;
    }
    return true;
}

void GRAPIOpenGL::SetupScene()
{
    // Cube: pos.xyz, color.rgb (copiado del source original)
    std::vector<float> vertices = {
        -0.5f,-0.5f,-0.5f,  1,0,0,
         0.5f,-0.5f,-0.5f,  0,1,0,
         0.5f, 0.5f,-0.5f,  0,0,1,
        -0.5f, 0.5f,-0.5f,  1,1,0,
        -0.5f,-0.5f, 0.5f,  1,0,1,
         0.5f,-0.5f, 0.5f,  0,1,1,
         0.5f, 0.5f, 0.5f,  1,1,1,
        -0.5f, 0.5f, 0.5f,  0.2f,0.8f,0.2f
    };

    std::vector<unsigned int> indices = {
        0,1,2, 2,3,0,
        4,5,6, 6,7,4,
        4,0,3, 3,7,4,
        1,5,6, 6,2,1,
        4,5,1, 1,0,4,
        3,2,6, 6,7,3
    };

    m_shader = std::make_unique<Shader>(vertexSrc, fragmentSrc);
    m_mesh = std::make_unique<Mesh>(vertices, indices);
}

void GRAPIOpenGL::RenderFrame()
{
    float t = (float)glfwGetTime();
    Mat4 model = Rotate(t * 0.5f, { 0.5f, 1.0f, 0.0f });
    Mat4 view = LookAt(m_eye, m_center, m_up);
    Mat4 proj = Perspective(45.0f * 3.14159265f / 180.0f, (float)m_bufferWidth / (float)m_bufferHeight, 0.1f, 100.0f);

    Mat4 mv = Multiply(view, model);          // view * model
    Mat4 mvp = Multiply(proj, mv);            // proj * (view * model)

    m_shader->UseShader();
    m_shader->SetMat4("uMVP", mvp.data());

    m_mesh->Draw();
}

int GRAPIOpenGL::Run()
{
    if (!m_window)
    {
        std::cout << "GrapiOpenGL::Run called before Init\n";
        return -1;
    }

    while (!glfwWindowShouldClose(m_window))
    {
        glfwPollEvents();

        glClearColor(0.12f, 0.14f, 0.18f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        RenderFrame();

        glfwSwapBuffers(m_window);
    }

    return 0;
}

void GRAPIOpenGL::ShutdownGL()
{
    if (m_window)
    {
        glfwDestroyWindow(m_window);
        m_window = nullptr;
    }
    glfwTerminate();

    // smart pointers se liberan automáticamente
    m_shader.reset();
    m_mesh.reset();
}