#ifndef GL_ERRORS_H
#define GL_ERRORS_H

#include <type_traits>
#include <stdexcept>

namespace GlHelper
{
	struct GLError final : public std::runtime_error
	{
		explicit GLError(const std::string& message)
			: runtime_error(message) {}

		explicit GLError(const char* message)
			: runtime_error(message) {}
	};
	
	void flush_gl_errors() noexcept;

	void throw_if_errors();
	
	template <typename Ret, typename... Args>
	std::enable_if_t<std::is_same_v<Ret, void>, Ret> call_and_handle_gl_errors(Ret(*function)(std::remove_const_t<std::remove_reference_t<Args>>...), Args&&... args)
	{
		flush_gl_errors();
		(*function)(std::forward<Args>(args)...);
		throw_if_errors();
	}

	template <typename Ret, typename... Args>
	std::enable_if_t<!std::is_same_v<Ret, void>, Ret> call_and_handle_gl_errors(Ret(*function)(std::remove_reference_t<Args>...), Args&&... args)
	{		
		flush_gl_errors();
		auto result = (*function)(std::forward<Args>(args)...);
		throw_if_errors();
		return result;
	}
}

#endif // GL_ERRORS_H
