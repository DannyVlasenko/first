#ifndef RENDER_LOOP_H
#define RENDER_LOOP_H

#include <GLFW/glfw3.h>

namespace GlHelper
{
	class GLFWLibrary;

	class RenderLoop final
	{
	public:
		explicit constexpr RenderLoop(GLFWwindow* window) noexcept :
			mWindow(window)
		{}
		
		RenderLoop(const RenderLoop& other) = delete;
		RenderLoop(RenderLoop&& other) noexcept = delete;
		RenderLoop& operator=(const RenderLoop& other) = delete;
		RenderLoop& operator=(RenderLoop&& other) noexcept = delete;
		~RenderLoop() = default;

		void run(const GLFWLibrary& library) const;
		
	private:
		GLFWwindow * const mWindow;
	};
}

#endif // RENDER_LOOP_H
