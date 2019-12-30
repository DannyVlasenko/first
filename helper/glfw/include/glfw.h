#ifndef GLFW_H
#define GLFW_H

#include <stdexcept>
#include <GLFW/glfw3.h>

namespace GlHelper
{
	class GLFWLibError final : public std::runtime_error
	{
	public:
		explicit GLFWLibError(const std::string& message)
			: runtime_error(message) {}

		explicit GLFWLibError(const char* message)
			: runtime_error(message) {}
	};
	
	class GLFWLibrary final
	{
	public:
		GLFWLibrary();
		GLFWLibrary(const GLFWLibrary&) = delete;
		GLFWLibrary& operator=(const GLFWLibrary&) = delete;
		GLFWLibrary(GLFWLibrary&&) = delete;
		GLFWLibrary& operator=(GLFWLibrary&&) = delete;
		~GLFWLibrary();

		GLFWwindow* createWindow(int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* share) const;
		void pollEvents() const;

		static void makeContextCurrent(GLFWwindow* window);
		static void swapBuffers(GLFWwindow* window);
		static bool checkWindowIsClosing(GLFWwindow* window);
	};
}

#endif // GLFW_H
