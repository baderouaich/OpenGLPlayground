#pragma once
#include <Utility/OpenGLUtils.hpp>

class IndexBuffer
{
public:
	IndexBuffer(const std::uint32_t* indices, const std::uint32_t count);
	~IndexBuffer();

public:
	void Bind() const noexcept;
	void Unbind() const noexcept;
	
public: 
	std::uint32_t GetCount() const noexcept { return m_count; }

private:
	GLuint m_id{};
	std::uint32_t m_count{};
};
