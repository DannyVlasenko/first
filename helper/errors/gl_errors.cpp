#include "gl_errors.h"
#include <GL/glew.h>
#include <string>

using namespace std::string_literals;

namespace GlHelper
{
	void flush_gl_errors() noexcept
	{
		while (glGetError() != GL_NO_ERROR);
	}

	std::string get_error_message(const GLenum error_code)
	{
		switch (error_code)
		{
		case GL_NO_ERROR:
			return "No error";
		case GL_INVALID_ENUM:
			return "An unacceptable value is specified for an enumerated argument.";
		case GL_INVALID_VALUE:
			return "A numeric argument is out of range.";
		case GL_INVALID_OPERATION:
			return "The specified operation is not allowed in the current state.";
		case GL_INVALID_FRAMEBUFFER_OPERATION:
			return "The frame buffer object is not complete.";
		case GL_OUT_OF_MEMORY:
			return "There is not enough memory left to execute the command. The state of the GL is undefined";
		case GL_STACK_UNDERFLOW:
			return "An attempt has been made to perform an operation that would cause an internal stack to underflow.";
		case GL_STACK_OVERFLOW:
			return "An attempt has been made to perform an operation that would cause an internal stack to overflow.";
		default:
			return "Unknown error with code: "s + std::to_string(error_code);
		}
	}

	void throw_if_errors()
	{
		auto errorCode = glGetError();
		if (errorCode == GL_NO_ERROR)
		{
			return;
		}

		std::string errorMessage;
		do
		{
			errorMessage.append(get_error_message(errorCode));
			errorCode = glGetError();
		}
		while (errorCode != GL_NO_ERROR);

		throw GLError(errorMessage);
	}
}
