#include "GL/glew.h"
#include "shader.h"
#include "shader_program.h"
#include <iostream>
#include <exception>
#include <GLFW/glfw3.h>
#include "glfw.h"
#include "glew.h"
#include "render_loop.h"

using GlHelper::GLFWLibrary;
using GlHelper::GLEW;
using GlHelper::RenderLoop;
using GlHelper::ShaderProgram;
using GlHelper::VertexShader;
using GlHelper::FragmentShader;

using namespace std::string_literals;

static ShaderProgram create_shader_program()
{	
    return ShaderProgram
	(
        VertexShader::loadFromFile("shaders/vertex"), 
        FragmentShader::loadFromFile("shaders/fragment")
    );
}

int main()
{
    try
    {
        const GLFWLibrary glfwLib;
        const auto window = glfwLib.createWindow(1024, 768, "Hello World", nullptr, nullptr);
        GLFWLibrary::makeContextCurrent(window);

        GLEW::init();

        std::cout << glGetString(GL_VERSION) << std::endl;

        float positions[8] =
        {
            -0.5f, -0.5f,
             0.5f, -0.5f,
             0.5f,  0.5f,
            -0.5f,  0.5f
        };

        GLuint bufferId;
        glGenBuffers(1, &bufferId);
        glBindBuffer(GL_ARRAY_BUFFER, bufferId);
        glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(float), positions, GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);

        unsigned int indices[6] =
        {
            0, 1, 2,
            2, 3, 0
        };

        GLuint iboId;
        glGenBuffers(1, &iboId);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboId);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW);

        use_program(create_shader_program());
        const RenderLoop mainLoop(window);
        mainLoop.run(glfwLib);
    }
    catch (std::exception & e)
    {
        std::cout << e.what() << std::endl;
    }
    return 0;
}