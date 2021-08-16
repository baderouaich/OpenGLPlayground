#pragma once
#include <string>
#include <Graphics/Shader/Shader.hpp> // ShaderDataType

struct BufferElement
{
	std::string name; // required
	Shader::ShaderDataType type; // required
	std::size_t offset;
	std::uint32_t size;
	bool normalized;

	BufferElement()
		:
		name(),
		type(Shader::ShaderDataType::None),
		normalized(false),
		size(0),
		offset(0) {}

	BufferElement(Shader::ShaderDataType type, const std::string& name, bool normalized = false)
		:
		name(name),
		type(type),
		normalized(normalized),
		size(Shader::GetDataTypeSize(type)),
		offset(0) {}


	std::uint32_t Count() const noexcept
	{
		switch (type)
		{
		case Shader::ShaderDataType::Float:		return 1;
		case Shader::ShaderDataType::Vec2f:		return 2;
		case Shader::ShaderDataType::Vec3f:		return 3;
		case Shader::ShaderDataType::Vec4f:		return 4;
		case Shader::ShaderDataType::Mat3:		return 3;
		case Shader::ShaderDataType::Mat4:		return 4;
		case Shader::ShaderDataType::Int:		return 1;
		case Shader::ShaderDataType::Vec2i:		return 2;
		case Shader::ShaderDataType::Vec3i:		return 3;
		case Shader::ShaderDataType::Vec4i:		return 4;
		case Shader::ShaderDataType::Bool:		return 1;
		default:
			break;
		}
		assert(false && "Unsupported Shader Data Type");
		return 0;
	}
};
