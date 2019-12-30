#include "shader.h"
#include <array>
#include <sstream>
#include <fstream>

using namespace std::string_literals;

namespace GlHelper
{
	namespace Impl
	{
		static std::string read_source_code(const std::istream& source_code_stream)
		{
			std::stringstream sstr;
			sstr << source_code_stream.rdbuf();
			return sstr.str();
		}
		
		static auto compile_shader(GLenum type, const std::string& source_code)
		{
			const auto id = glCreateShader(type);
			std::array<const GLchar*, 1> sourceCodeArray{ source_code.c_str() };
			glShaderSource(id, 1, sourceCodeArray.data(), nullptr);
			glCompileShader(id);

			GLint result;
			glGetShaderiv(id, GL_COMPILE_STATUS, &result);
			if (result == GL_FALSE)
			{
				GLint errorMessageLength;
				glGetShaderiv(id, GL_INFO_LOG_LENGTH, &errorMessageLength);
				std::string errorMessage(static_cast<size_t>(errorMessageLength), 0);
				glGetShaderInfoLog(id, errorMessageLength, &errorMessageLength, errorMessage.data());
				glDeleteShader(id);
				throw ShaderCompilationError("Compilation failed"s + errorMessage);
			}

			return id;
		}

		ShaderId::ShaderId(ShaderId&& rhs) noexcept:
			mId(rhs.mId)
		{
			rhs.mId = 0;
		}

		ShaderId& ShaderId::operator=(ShaderId&& rhs) noexcept
		{
			mId = rhs.mId;
			rhs.mId = 0;
			return *this;
		}

		ShaderId::~ShaderId()
		{
			glDeleteShader(mId);
		}

		void ShaderId::swap(ShaderId& rhs) noexcept
		{
			using std::swap;
			swap(this->mId, rhs.mId);
		}

		void swap(ShaderId& lhs, ShaderId& rhs) noexcept
		{
			lhs.swap(rhs);
		}

		std::ifstream get_shader_file_stream(const std::filesystem::path& file)
		{
			if (std::error_code errorCode; !std::filesystem::exists(file, errorCode))
			{
				throw std::filesystem::filesystem_error("Shader file not found", file, errorCode);
			}
			return std::ifstream{ file.generic_string(), std::ios::binary };
		}
	}

	VertexShader VertexShader::loadFromFile(const std::filesystem::path& file)
	{
		return VertexShader{ Impl::get_shader_file_stream(file) };
	}

	VertexShader::VertexShader(const std::string& source_code):
		mShaderId(Impl::compile_shader(GL_VERTEX_SHADER, source_code))
	{}

	VertexShader::VertexShader(const std::istream& source_code_stream):
		VertexShader(Impl::read_source_code(source_code_stream))
	{}

	FragmentShader FragmentShader::loadFromFile(const std::filesystem::path& file)
	{
		return FragmentShader{ Impl::get_shader_file_stream(file) };
	}

	FragmentShader::FragmentShader(const std::string& source_code):
		mShaderId(Impl::compile_shader(GL_FRAGMENT_SHADER, source_code))
	{}

	FragmentShader::FragmentShader(const std::istream& source_code_stream):
		FragmentShader(Impl::read_source_code(source_code_stream))
	{}
}
