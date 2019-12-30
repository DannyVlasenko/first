#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#include "GL/glew.h"
#include "gl_errors.h"
#include <stdexcept>

namespace GlHelper
{
	namespace Impl
	{
		void attach_single_shader(GLuint program, GLuint shader);
		void link_program(GLuint program);
		void validate_program(GLuint program);

		template<typename ShaderType>
		void attach_shader(GLuint program, const ShaderType& shader)
		{
			attach_single_shader(program, static_cast<GLuint>(shader));
		}
		
		template<typename ShaderType, typename... RemainType>
		void attach_shader(GLuint program, const ShaderType& shader, const RemainType&... remain)
		{
			attach_single_shader(program, static_cast<GLuint>(shader));
			attach_shader(program, remain...);
		}
	}
	
	struct ShaderProgramError final : public std::runtime_error
	{
		explicit ShaderProgramError(const std::string& message)
			: runtime_error(message) {}

		explicit ShaderProgramError(const char* message)
			: runtime_error(message) {}
	};
	
	class ShaderProgram	final
	{
	public:
		template<typename... ShaderType>
		explicit ShaderProgram(const ShaderType&... shader):		
			mProgramId(call_and_handle_gl_errors(glCreateProgram))
		{		
			Impl::attach_shader(mProgramId, shader...);
			Impl::link_program(mProgramId);
			Impl::validate_program(mProgramId);
		}

		ShaderProgram(const ShaderProgram &) = delete;
		ShaderProgram& operator=(const ShaderProgram &) = delete;
		ShaderProgram(ShaderProgram &&) noexcept;
		ShaderProgram& operator=(ShaderProgram &&) noexcept;
		
		explicit operator GLuint() const noexcept
		{
			return mProgramId;
		}

		~ShaderProgram();

	private:
		GLuint mProgramId;
	};

	void use_program(const ShaderProgram& program);
}

#endif // SHADER_PROGRAM_H
