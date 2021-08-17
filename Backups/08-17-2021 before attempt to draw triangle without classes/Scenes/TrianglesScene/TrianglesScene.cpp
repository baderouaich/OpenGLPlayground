#include "pch.hpp"
#include "TrianglesScene.hpp"
#include <Application/Application.hpp>
#include <Input/Input.hpp>
#include <Event/EventDispatcher.hpp>
#include <Event/KeyEvent.hpp>
#include <glad/glad.h>
#include <Utility/OpenGLUtils.hpp>



void TrianglesScene::InitVertexBuffer()
{
	// 3 Vertices (3 points) to draw triangle (See OpenGL Tutorials/Triangle Vertices.png)
	const float TRIANGLE_VERTICES[]
	{
#if 0
		/*Vertex 1 xyz */ -1.0f, -1.0f, 0.0f, // left bottom 0
		/*Vertex 2 xyz */ 0.0f, 1.0f, 0.0f,   // top center 1
		/*Vertex 3 xyz */ 1.0f, -1.0f, 0.0f   // right bottom 2
#endif
		- 0.5f, -0.5f, 0.0f, // left  
		 0.5f, -0.5f, 0.0f, // right 
		 0.0f,  0.5f, 0.0f  // top   

	};

	// p35 s5.5
	m_vertex_buffer.reset(new VertexBuffer(VertexBuffer::DrawType::Static));
	// Copy our vertices array in a buffer for OpenGL to use
	m_vertex_buffer->SetBufferData(TRIANGLE_VERTICES);

	BufferLayout layout(
	{
		{ Shader::ShaderDataType::Vec4f, "a_Color" }, // see shader above
	});
	m_vertex_buffer->SetLayout(layout);
}


void TrianglesScene::InitIndexBuffer()
{
	std::array<std::uint32_t, 3> indices
	{
		0, 1, 2
	};
	m_index_buffer.reset(new IndexBuffer(indices.data(), static_cast<std::uint32_t>(indices.size())));
}

void TrianglesScene::InitVertexBufferArray()
{
	m_vertex_array.reset(new VertexArray());
}

void TrianglesScene::InitShader()
{
	m_shader.reset(new Shader(
		{
			{
				Shader::ShaderType::Vertex,
				Shader::ShaderSourceType::String,
				R"(
					#version 330 core
					layout (location = 0) in vec3 a_Position;

					void main()
					{
						gl_Position = vec4(a_Position.x, a_Position.y, a_Position.z, 0.0);
					}

				)"
			},
			{
				Shader::ShaderType::Fragment,
				Shader::ShaderSourceType::String,
				R"(
					#version 330 core
					out vec4 final_pixel_color;

					void main()
					{
						final_pixel_color = vec4(1.0f, 0.5f, 0.2f, 1.0f);
					}
				)"
			},
		}));
}

void TrianglesScene::OnCreate()
{
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	this->InitVertexBufferArray();
	this->InitVertexBuffer();
	this->InitIndexBuffer();

	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	m_vertex_array->AddVertexBuffer(m_vertex_buffer);
	m_vertex_array->SetIndexBuffer(m_index_buffer);
	this->InitShader();

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	m_vertex_buffer->Unbind();
	m_vertex_array->Unbind();
}

void TrianglesScene::OnEvent(Event& event)
{
	EventDispatcher dispatcher(event);
	// Handle Keyboard ESCAPE Press
	dispatcher.Dispatch<KeyPressedEvent>([this](KeyPressedEvent& e) -> bool
		{
			if (e.GetKeyCode() == KeyCode::Escape)
			{
				Scene::Exit();
				return true;
			}
			return false; 
		});
}

void TrianglesScene::OnUpdate([[maybe_unused]] float dt)
{

}

// https://github.com/JoeyDeVries/LearnOpenGL/blob/master/src/1.getting_started/2.2.hello_triangle_indexed/hello_triangle_indexed.cpp
void TrianglesScene::OnDraw()
{
	glAssert(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));
	glAssert(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT));

	m_shader->Bind();
	//m_shader->SetVec4f("a_Color", glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
	//m_shader->SetVec3f("a_Position", glm::vec3(0.0f, 0.0f, 0.0f));
	// 0. Copy our vertices array in a buffer for OpenGL to use: done in InitVertexBuffer()
	//m_vertex_buffer->Bind(); // bind VBO
	m_vertex_array->Bind(); // bind VAO


	// 1. then set the vertex attributes pointers: done in InitVertexBufferArray VAO::AddVertexBuffer
	//glAssert(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0));
	//glAssert(glEnableVertexAttribArray(0));

	// 2. use our shader program when we want to render an object

	// 3. now draw the object
	glAssert(glDrawElements(GL_TRIANGLES, m_vertex_array->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr));



	m_shader->Unbind();
	m_vertex_array->Unbind();

}

void TrianglesScene::OnImGuiDraw()
{
}

void TrianglesScene::OnDestroy()
{
}
