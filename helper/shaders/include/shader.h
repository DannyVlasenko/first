#ifndef VERTEX_SHADER_H
#define VERTEX_SHADER_H

#include <string>
#include <GL/glew.h>
#include <stdexcept>
#include <filesystem>
#include <iosfwd>

namespace GlHelper
{
	struct ShaderCompilationError final : public std::runtime_error
	{
		explicit ShaderCompilationError(const std::string& message)
			: runtime_error(message) {}

		explicit ShaderCompilationError(const char* message)
			: runtime_error(message) {}
	};
	
	namespace Impl
	{
		class ShaderId final
		{
		public:
			constexpr explicit ShaderId(GLuint id):
				mId(id)
			{}

			ShaderId(const ShaderId& rhs) = delete;
			ShaderId& operator=(const ShaderId& rhs) = delete;
			ShaderId(ShaderId&& rhs) noexcept;
			ShaderId& operator=(ShaderId&& rhs) noexcept;

			~ShaderId();

			void swap(ShaderId& rhs) noexcept;

			explicit constexpr operator GLuint() const noexcept
			{
				return mId;
			}
			
		private:
			GLuint mId;
		};

		void swap(ShaderId& lhs, ShaderId& rhs) noexcept;

		std::ifstream get_shader_file_stream(const std::filesystem::path& file);
	}
	
	class VertexShader final
	{
	public:
		static VertexShader loadFromFile(const std::filesystem::path& file);
		
		explicit VertexShader(const std::string& source_code);
		explicit VertexShader(const std::istream &source_code_stream);
		
		explicit operator GLuint() const noexcept
		{
			return static_cast<GLuint>(mShaderId);
		}
		
	private:
		const Impl::ShaderId mShaderId;
	};

	class FragmentShader final
	{
	public:
		static FragmentShader loadFromFile(const std::filesystem::path& file);
		
		explicit FragmentShader(const std::string& source_code);
		explicit FragmentShader(const std::istream& source_code_stream);

		explicit operator GLuint() const noexcept
		{
			return static_cast<GLuint>(mShaderId);
		}

	private:
		const Impl::ShaderId mShaderId;
	};
	
	template <typename ShaderType>
	ShaderType shader_load_from_file(const std::filesystem::path &file)
	{
		
		return ShaderType{ shaderFileStream };
	}
}
#endif // VERTEX_SHADER_H
