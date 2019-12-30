#ifndef GLEW_H
#define GLEW_H
#include <stdexcept>

namespace GlHelper
{
	class GLEWError final : public std::runtime_error
	{
	public:
		explicit GLEWError(const std::string& message)
			: runtime_error(message) {}

		explicit GLEWError(const char* message)
			: runtime_error(message) {}
	};

	class GLEW final
	{
	public:
		static void init();
	};
}

#endif // GLEW_H
