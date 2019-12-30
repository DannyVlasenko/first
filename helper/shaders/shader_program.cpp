#include "shader_program.h"

using namespace std::string_literals;

namespace GlHelper
{
	namespace Impl
	{
		void attach_single_shader(GLuint program, GLuint shader)
		{
			call_and_handle_gl_errors(glAttachShader, program, shader);
		}

		void link_program(GLuint program)
		{
			call_and_handle_gl_errors(glLinkProgram, program);
		}

		void validate_program(GLuint program)
		{
			call_and_handle_gl_errors(glValidateProgram, program);
		}
	}

	ShaderProgram::ShaderProgram(ShaderProgram &&rhs) noexcept :
		mProgramId(rhs.mProgramId)
	{
		rhs.mProgramId = 0;
	}

	ShaderProgram& ShaderProgram::operator=(ShaderProgram &&rhs) noexcept
	{
		mProgramId = rhs.mProgramId;
		rhs.mProgramId = 0;
		return *this;
	}

	ShaderProgram::~ShaderProgram()
	{
		glDeleteProgram(mProgramId);
	}

	void use_program(const ShaderProgram& program)
	{
		call_and_handle_gl_errors(glUseProgram, static_cast<GLuint>(program));
	}
}
