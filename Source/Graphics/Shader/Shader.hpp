#pragma once
#include <string>
#include <initializer_list>
#include <iostream>

#include <Utility/FileUtils.hpp>
#include <Utility/OpenGLUtils.hpp>

#include <glad/glad.h>

class Shader
{

public:
	enum class ShaderSourceType : unsigned char
	{
		String,
		File
	};
	enum class ShaderType : GLenum
	{
		Vertex   = GL_VERTEX_SHADER,
		Fragment = GL_FRAGMENT_SHADER,
		Geometry = GL_GEOMETRY_SHADER,
		Compute  = GL_COMPUTE_SHADER,
	};
	enum class ShaderDataType : unsigned char
	{
		None = 0,
		Float, Vec2f, Vec3f, Vec4f,
		Mat3, Mat4,
		Int, Vec2i, Vec3i, Vec4i,
		Bool
	};

	struct ShaderProgramData
	{
		ShaderType type;
		ShaderSourceType source_type;
		std::string filename_or_source;
	};

	// to use Shader::EnumValue
	using enum ShaderSourceType;
	using enum ShaderType;
	using enum ShaderDataType;

public:
	explicit Shader(const std::initializer_list<ShaderProgramData>& shaders_data);
	~Shader();

public:
	void Bind() const noexcept;
	void Unbind() const noexcept;

public: // Set shader uniform variables
	void SetInteger(const GLchar* name, GLint v) noexcept;
	void SetFloat(const GLchar* name, GLfloat v) noexcept;
	void SetVec2f(const GLchar* name, const glm::fvec2& v) noexcept;
	void SetVec3f(const GLchar* name, const glm::fvec3& v) noexcept;
	void SetVec4f(const GLchar* name, const glm::fvec4& v) noexcept;
	void SetMat3(const GLchar* name, const glm::mat3& v, GLboolean transpose) noexcept;
	void SetMat4(const GLchar* name, const glm::mat4& v, GLboolean transpose) noexcept;
	void SetIntegerArray(const GLchar* name, const GLint* v, GLsizei count) noexcept;

public: 
	GLint GetUniformLocation(const std::string& uniform_name) noexcept;

	static std::uint32_t GetDataTypeSize(ShaderDataType type) noexcept;

private:
	bool Compile(const std::unordered_map<GLenum, std::string>& shader_sources) noexcept;

public:
	/** Converts ShaderDataType to OpenGLBase Type */
	static GLenum ShaderDataTypeToOpenGLBaseType(const ShaderDataType type) noexcept;

private:
	GLuint m_id{};

private:	
	std::unordered_map<std::string, GLint> m_uniform_locations_cache; // Cache uniforms to avoid calling glGetUniformLocation() all the time

};

