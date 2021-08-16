#pragma once
#include <Utility/OpenGLUtils.hpp>
#include <Graphics/Buffer/BufferLayout/BufferLayout.hpp>
#include <glad/glad.h>
#include <memory>

/*
VBO p29 s5.2
We manage GPU memory via so called vertex buffer objects (VBO) that can store a large number
of vertices in the GPU’s memory. The advantage of using those buffer objects is that we can send
large batches of data all at once to the graphics card, and keep it there if there’s enough memory left,
without having to send data one vertex at a time. Sending data to the graphics card from the CPU is
relatively slow, so wherever we can we try to send as much data as possible at once. Once the data is
in the graphics card’s memory the vertex shader has almost instant access to the vertices making it
extremely fast

also p34 s5

VertexBuffer is an array of vertices [(x,y,z),(x,y,z)...]
used to pack vertices for some object like a bunny 3D ? a 2D triangle.. or a part of an object
*/
class VertexBuffer
{
public:
	/*
	VBO p29 s5.2
	The fourth parameter specifies how we want the graphics card to manage the given data. This
	can take 3 forms:
	• GL_STREAM_DRAW: the data is set only once and used by the GPU at most a few times.
	• GL_STATIC_DRAW: the data is set only once and used many times.
	• GL_DYNAMIC_DRAW: the data is changed a lot and used many times.
	*/
	enum class DrawType : GLenum
	{
		Static = GL_STATIC_DRAW,
		Dynamic = GL_DYNAMIC_DRAW,
		Stream = GL_STREAM_DRAW,
	};

	VertexBuffer(const DrawType draw_type)
		:
		m_draw_type(draw_type)
	{
		glAssert(glGenBuffers(1, &m_id));
	}

	~VertexBuffer()
	{
		glAssert(glDeleteBuffers(1, &m_id));
	}

	void Bind() const noexcept
	{
		glAssert(glBindBuffer(GL_ARRAY_BUFFER, m_id));
	}

	void Unbind() const noexcept
	{
		glAssert(glBindBuffer(GL_ARRAY_BUFFER, 0));
	}

	void SetBufferData(const float* vertices)
	{
		this->Bind();
		// p29 s5.2 /We call to the glBufferData function that copies the previously defined vertex data into the buffer’s memory GPU
		glAssert(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, static_cast<GLenum>(m_draw_type)));

	}
	void SetLayout(const BufferLayout& layout) noexcept { m_layout = layout; }

	const BufferLayout& GetLayout() const noexcept { return m_layout; }

private:

#if 0
	bool IsBound()
	{
		//https://stackoverflow.com/questions/27459859/how-to-check-which-frame-buffer-object-is-currently-bound-in-opengl
		GLint r{ 0 };
		glAssert(glGetIntegerv(GL_FRAMEBUFFER_BINDING, &r));
		return r == m_id;
	}
#endif

private:
	GLuint m_id{};
	DrawType m_draw_type{};
	BufferLayout m_layout{};
};
