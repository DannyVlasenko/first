#include "glfw.h"
#include "GLFW/glfw3.h"
#include <string>

using namespace std::string_literals;

namespace GlHelper
{
	GLFWLibrary::GLFWLibrary()
	{
		if (!glfwInit())
		{
			throw GLFWLibError("GLFW library initialization error");
		}
	}

	GLFWLibrary::~GLFWLibrary()
	{
		glfwTerminate();
	}

	GLFWwindow* GLFWLibrary::createWindow(int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* share) const
	{
		const auto window = glfwCreateWindow(width, height, title, monitor, share);
		if (!window)
		{
			throw GLFWLibError
			(
				"Cannot create window ["s + title 
				+ "]s with dimensions w:" + std::to_string(width) 
				+ " h:" + std::to_string(height)
			);
		}
		return window;
	}

	void GLFWLibrary::pollEvents() const
	{
		glfwPollEvents();
	}

	void GLFWLibrary::makeContextCurrent(GLFWwindow* window)
	{
		glfwMakeContextCurrent(window);
	}

	void GLFWLibrary::swapBuffers(GLFWwindow* window)
	{
		glfwSwapBuffers(window);
	}

	bool GLFWLibrary::checkWindowIsClosing(GLFWwindow* window)
	{
		return glfwWindowShouldClose(window);
	}
}
