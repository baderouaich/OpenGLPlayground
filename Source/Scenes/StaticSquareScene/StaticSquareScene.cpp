#include "pch.hpp"
#include "StaticSquareScene.hpp"
#include <Application/Application.hpp>
#include <Input/Input.hpp>
#include <Event/EventDispatcher.hpp>
#include <Event/KeyEvent.hpp>
#include <Utility/OpenGLUtils.hpp>
#include <glad/glad.h>

/* OpenGL Square Drawing Steps:
* # Initialization:
* 1- Create VertexArray object glGenVertexArrays(1, &m_id);
* 2- Create VertexBuffer objects glGenBuffers(1, &m_id);
* 3- Bind and Set vertices buffer to VertexBuffer objects  glBindBuffer(GL_ARRAY_BUFFER, m_id) & glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW|GL_DYNAMIC_DRAW))
* 4- Create Set BufferLayout to VertexBuffer, to tell OpenGL what are my vertices contain of? positions and colors? or positions only...and their types
* 5- Add Created VertexBuffer objects to VertexArray m_vertex_array->AddVertexBuffer(vertex_buffer);
* 6- Create & Bind IndexBuffer object, to tell OpenGL how to draw vertices in order from 0 to N vertices  glGenBuffers(1, &m_id); && glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id) && glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(decltype(indices[0])), indices, GL_STATIC_DRAW);
* 7- Set IndexBuffer object to VertexArray (bind vao, bind ibo)
* 8- Create Shader program of vertex and fragment, with layout(location = 0) in vec3 a_Position; in vertex according to your vertices layout, and uniform vec4 u_Color; if u want to upload them from cpp
* # Draw
* 1- Clear buffers glClearColor(0.2f, 0.3f, 0.3f, 1.0f) && glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT)
* 2- Bind & set uniform u_Color to Square which modifies by ui settings m_shader->Bind(); && m_shader->SetVec4f("u_Color", SquareColor);
* 3- Bind vertex array to be drawn m_vertex_array->Bind();
* 4- Draw Square glDrawElements(GL_TRIANGLES, m_vertex_array->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
* 5- Unbind Shader & VAO
*/

void StaticSquareScene::OnCreate()
{
	TRACE_FUNCTION();

	// Make vertex array
	m_vertex_array = std::make_shared<VertexArray>();

	// Make statically drawn vertex buffer and set vertices to it (static cuz we're not gonna call SetBufferData each frame, vertices will not change)
	auto vertex_buffer = std::make_shared<VertexBuffer>(VertexBuffer::DrawType::Static);
	vertex_buffer->SetBufferData(SQUARE_VERTICES.data(), sizeof(float) * SQUARE_VERTICES.size());

	// Tell opengl what my vertices layout is, now vertices contain positions only.
	BufferLayout layout({
		{ Shader::ShaderDataType::Vec3f, "a_Position" },
		});
	vertex_buffer->SetLayout(layout); // set layout to vertex buffer
	// add vertex buffer to vertex buffer array
	m_vertex_array->AddVertexBuffer(vertex_buffer);


	// Make index buffer, to tell opengl which vertex to draw first and last..
	auto index_buffer = std::make_shared<IndexBuffer>(SQUARE_INDICES.data(), static_cast<std::uint32_t>(SQUARE_INDICES.size()));
	// Set index buffer to the vertex array
	m_vertex_array->SetIndexBuffer(index_buffer);


	// Make shader, vertex with a_Position we have in vertices and which we set its layout to vertex buffer
	// and a fragment shader which has a uniform variable u_Color which we will pass to shader from ui settings setUniform
	m_shader.reset(new Shader(
		{
			{
				Shader::ShaderType::Vertex,
				Shader::ShaderSourceType::String,
				R"(
					#version 330 core
			
					// my vertex layout has only positions for now
					layout(location = 0) in vec3 a_Position;

					void main()
					{
						gl_Position = vec4(a_Position, 1.0);
					}

				)"
			},
			{
				Shader::ShaderType::Fragment,
				Shader::ShaderSourceType::String,
				R"(
					#version 330 core

					uniform vec4 u_Color; // m_shader->SetVec4f("u_Color", m_square_color);, currently ignored

					out vec4 final_color;
					void main()
					{
						final_color = vec4(1.0, 1.0, 1.0, 1.0); // white for now
					}
				)"
			},
		}));
}


void StaticSquareScene::OnEvent(Event& event)
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


void StaticSquareScene::OnUpdate(float dt)
{
}

void StaticSquareScene::OnDraw()
{
	// Clear buffers
	glAssert(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));
	glAssert(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT));

	// Bind & set uniform u_Color to m_square_color which modifies by ui settings
	m_shader->Bind();
	//m_shader->SetVec4f("u_Color", m_square_color);

	// Bind vertex array to be drawn
	m_vertex_array->Bind();

	// Draw Two triangles (indexed) will show as a Square
	glAssert(glDrawElements(GL_TRIANGLES, m_vertex_array->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr));
	//glDrawArrays(GL_TRIANGLES, 0, m_vertex_array->GetIndexBuffer()->GetCount() - 1 );
	
	// Unbind stuff
	m_shader->Unbind();
	m_vertex_array->Unbind();
}

void StaticSquareScene::OnImGuiDraw()
{
	//ImGui::Begin("Settings");
	//ImGui::ColorEdit4("Square Color", glm::value_ptr(m_square_color));
	//ImGui::End();
}

void StaticSquareScene::OnDestroy()
{
	TRACE_FUNCTION();

}
