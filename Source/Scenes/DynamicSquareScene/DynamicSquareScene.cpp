#include "pch.hpp"
#include "DynamicSquareScene.hpp"
#include <Application/Application.hpp>
#include <Input/Input.hpp>
#include <Event/EventDispatcher.hpp>
#include <Event/KeyEvent.hpp>
#include <Utility/OpenGLUtils.hpp>
#include <glad/glad.h>

void DynamicSquareScene::OnCreate()
{
	TRACE_FUNCTION();

	// Make vertex array
	m_vertex_array = std::make_shared<VertexArray>();

	// Make statically drawn vertex buffer and set vertices to it (dynamic cuz we're gonna call SetBufferData alot to move the triangle, vertices will not change)
	m_vertex_buffer = std::make_shared<VertexBuffer>(VertexBuffer::DrawType::Dynamic);
	m_vertex_buffer->SetBufferData(SQUARE_VERTICES.data(), sizeof(float) * SQUARE_VERTICES.size());

	// Tell opengl what my vertices layout is, now vertices contain positions only.
	BufferLayout layout({
		{ Shader::ShaderDataType::Vec3f, "a_Position" },
		});
	m_vertex_buffer->SetLayout(layout); // set layout to vertex buffer
	// add vertex buffer to vertex buffer array
	m_vertex_array->AddVertexBuffer(m_vertex_buffer);


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

					uniform vec4 u_Color; // m_shader->SetVec4f("u_Color", m_square_color);

					out vec4 final_color;
					void main()
					{
						final_color = u_Color;
					}
				)"
			},
		}));
}


void DynamicSquareScene::OnEvent(Event& event)
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

			if (e.GetKeyCode() == KeyCode::Space) // CHANGES square's color randomly
			{
				static std::random_device seed{};
				static std::default_random_engine engine{ seed() };
				std::uniform_real_distribution<float> dist(0.0f, 1.0f);

				glm::vec4 color(dist(engine), dist(engine), dist(engine), dist(engine));
				m_shader->Bind();
				m_shader->SetVec4f("u_Color", color);
				m_shader->Unbind();
			}
			return false;
		});
}


void DynamicSquareScene::OnUpdate([[maybe_unused]] float dt)
{
	// TODO: use MVP Matrix to move all vertices at once http://www.opengl-tutorial.org/beginners-tutorials/tutorial-3-matrices/
	///========= MOVEMENT =========///
	// to make square move, all vertices should move
	static float* vertex_xyz_1 = SQUARE_VERTICES.data() + 0;  // Vertex 1 x,y,z
	static float* vertex_xyz_2 = SQUARE_VERTICES.data() + 3;  // Vertex 2 x,y,z
	static float* vertex_xyz_3 = SQUARE_VERTICES.data() + 6;  // Vertex 3 x,y,z
	static float* vertex_xyz_4 = SQUARE_VERTICES.data() + 9;  // Vertex 4 x,y,z

	const static float SPEED = 2.0f;

	// LEFT
	if (Input::IsKeyPressed(KeyCode::Left))
	{
		vertex_xyz_1[0] -= SPEED * dt; // vertex1.x-
		vertex_xyz_2[0] -= SPEED * dt; // vertex2.x-
		vertex_xyz_3[0] -= SPEED * dt; // vertex3.x-
		vertex_xyz_4[0] -= SPEED * dt; // vertex4.x-

	}
	// RIGHT
	else if (Input::IsKeyPressed(KeyCode::Right))
	{
		vertex_xyz_1[0] += SPEED * dt; // vertex1.x+
		vertex_xyz_2[0] += SPEED * dt; // vertex2.x+
		vertex_xyz_3[0] += SPEED * dt; // vertex3.x+
		vertex_xyz_4[0] += SPEED * dt; // vertex4.x+
	}
	// UP
	if (Input::IsKeyPressed(KeyCode::Up))
	{
		vertex_xyz_1[1] += SPEED * dt; // vertex1.y+
		vertex_xyz_2[1] += SPEED * dt; // vertex2.y+
		vertex_xyz_3[1] += SPEED * dt; // vertex3.y+
		vertex_xyz_4[1] += SPEED * dt; // vertex4.y+

	}
	// DOWN
	else if (Input::IsKeyPressed(KeyCode::Down))
	{
		vertex_xyz_1[1] -= SPEED * dt; // vertex1.y-
		vertex_xyz_2[1] -= SPEED * dt; // vertex2.y-
		vertex_xyz_3[1] -= SPEED * dt; // vertex3.y-
		vertex_xyz_4[1] -= SPEED * dt; // vertex4.y-
	}

	// Update vertex buffer data (in gpu)
	m_vertex_buffer->SetBufferData(SQUARE_VERTICES.data(), SQUARE_VERTICES.size() * sizeof(float));
}

void DynamicSquareScene::OnDraw()
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

void DynamicSquareScene::OnImGuiDraw()
{
	static bool info_showing = true;
	if (info_showing)
	{
		ImGui::Begin("Info");
		ImGui::Text("Use arrows UP DOWN LEFT RIGHT to move the square\nCick Space to change square's color randomly");
		if (ImGui::Button("OK"))
		{
			info_showing = false;
		}
		ImGui::End();

	}
}

void DynamicSquareScene::OnDestroy()
{
	TRACE_FUNCTION();

}
