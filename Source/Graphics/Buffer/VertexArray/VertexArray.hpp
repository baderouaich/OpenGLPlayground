#pragma once
#include <Utility/OpenGLUtils.hpp>
#include <Graphics/Buffer/VertexBuffer/VertexBuffer.hpp>
#include <Graphics/Buffer/BufferLayout/BufferLayout.hpp>
#include <Graphics/Buffer/IndexBuffer/IndexBuffer.hpp>
#include <memory>
#include <vector>

// p32 s5.5.1 Vertex Array Object (Array of VertexBuffer)
class VertexArray
{
public:
	VertexArray()
	{
		//glCreateVertexArrays(1, &m_id); GL >= 4.5
		glAssert(glGenVertexArrays(1, &m_id));
	}
	~VertexArray()
	{
		glAssert(glDeleteVertexArrays(1, &m_id));
	}

	void Bind() const noexcept
	{
		glAssert(glBindVertexArray(m_id));
	}

	void Unbind() const noexcept
	{
		glAssert(glBindVertexArray(0));
	}

	void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertex_buffer)
	{
		this->Bind(); // Bind Current VAO 
		vertex_buffer->Bind(); // Bind VBO

		assert(vertex_buffer->GetLayout().GetElements().size() && "Vertex Buffer has no layout");

		std::uint32_t index = 0;
		auto& layout = vertex_buffer->GetLayout();
		for (const auto& element : layout)
		{
			glAssert(glEnableVertexAttribArray(index));

			glAssert(glVertexAttribPointer(
				index, 
				element.Count(),
				Shader::ShaderDataTypeToOpenGLBaseType(element.type),
				element.normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(const void*)element.offset)
			);

			index++;
		}


		m_vertex_buffers.emplace_back(vertex_buffer);

	}

	void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& index_buffer)
	{
		this->Bind();
		index_buffer->Bind();

		m_index_buffer = index_buffer;
	}

	const std::shared_ptr<IndexBuffer>& GetIndexBuffer()const noexcept { return m_index_buffer; }

private:
	GLuint m_id{};
	std::vector<std::shared_ptr<VertexBuffer>> m_vertex_buffers;
	std::shared_ptr<IndexBuffer> m_index_buffer;
};

