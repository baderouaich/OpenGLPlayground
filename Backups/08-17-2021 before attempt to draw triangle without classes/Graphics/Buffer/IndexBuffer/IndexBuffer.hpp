#pragma once
#include <Utility/OpenGLUtils.hpp>

class IndexBuffer
{
public:
	IndexBuffer(const std::uint32_t* indices, const std::uint32_t count)
		:
		m_count(count)
	{
		glAssert(glGenBuffers(1, &m_id));
		this->Bind();
		glAssert(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(decltype(indices[0])), indices, GL_STATIC_DRAW));
	}

	~IndexBuffer() 
	{
		glAssert(glDeleteBuffers(1, &m_id));
	}

	void Bind() const noexcept
	{
		glAssert(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id));
	}
	void Unbind() const noexcept
	{
		glAssert(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
	}

public: /* Accessors */
	std::uint32_t GetCount() const noexcept { return m_count; }

public: /* Modifiers */


private:
	GLuint m_id{};
	std::uint32_t m_count{};
};
