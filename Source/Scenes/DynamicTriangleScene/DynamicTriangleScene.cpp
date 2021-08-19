#include "pch.hpp"
#include "DynamicTriangleScene.hpp"
#include <Application/Application.hpp>
#include <Input/Input.hpp>
#include <Event/EventDispatcher.hpp>
#include <Event/KeyEvent.hpp>
#include <Utility/OpenGLUtils.hpp>
#include <glad/glad.h>

/* OpenGL Dynamic Triangle Drawing Steps:
* # Initialization:
* 1- Create VertexArray object glGenVertexArrays(1, &m_id);
* 2- Create VertexBuffer objects glGenBuffers(1, &m_id);
* 3- Bind and Set vertices buffer to VertexBuffer objects  glBindBuffer(GL_ARRAY_BUFFER, m_id) & glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_DYNAMIC_DRAW))
* 4- Create Set BufferLayout to VertexBuffer, to tell OpenGL what are my vertices contain of? positions and colors? or positions only...and their types
* 5- Add Created VertexBuffer objects to VertexArray m_vertex_array->AddVertexBuffer(vertex_buffer);
* 6- Create & Bind IndexBuffer object, to tell OpenGL how to draw vertices in order from 0 to N vertices  glGenBuffers(1, &m_id); && glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id) && glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(decltype(indices[0])), indices, GL_STATIC_DRAW);
* 7- Set IndexBuffer object to VertexArray (bind vao, bind ibo)
* 8- Create Shader program of vertex and fragment, with layout(location = 0) in vec3 a_Position; in vertex according to your vertices layout, and uniform vec4 u_Color; if u want to upload them from cpp
* # Draw
* 1- Clear buffers glClearColor(0.2f, 0.3f, 0.3f, 1.0f) && glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT)
* 2- Bind & set uniform u_Color to m_triangle_color which modifies by ui settings m_shader->Bind(); && m_shader->SetVec4f("u_Color", m_triangle_color);
* 3- Bind vertex array to be drawn m_vertex_array->Bind();
* 4- Draw triangle glDrawElements(GL_TRIANGLES, m_vertex_array->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
* 5- Unbind Shader & VAO
*/

void DynamicTriangleScene::OnCreate()
{
	// Make vertex array
	m_vertex_array = std::make_shared<VertexArray>();

	// Make dynamic drawn vertex buffer and set vertices to it (dynamic cuz we're gonna call SetBufferData alot to move the triangle, vertices will not change)
	m_vertex_buffer = std::make_shared<VertexBuffer>(VertexBuffer::DrawType::Dynamic);
	m_vertex_buffer->SetBufferData(m_vertices.data(), sizeof(float) * m_vertices.size());

	// Tell opengl what my vertices layout is, now vertices contain positions only.
	BufferLayout layout({
		{ Shader::ShaderDataType::Vec3f, "a_Position" },
		});
	m_vertex_buffer->SetLayout(layout); // set layout to vertex buffer
	// add vertex buffer to vertex buffer array
	m_vertex_array->AddVertexBuffer(m_vertex_buffer);


	// Make index buffer, to tell opengl which vertex to draw first and last..
	uint32_t indices[3] = { 0, 1, 2 }; // no worries, we can get it from vao with GetIndexBuffer later
	auto index_buffer = std::make_shared<IndexBuffer>(indices, 3);
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
					layout(location = 0) in vec3 v_Position;

					void main()
					{
						gl_Position = vec4(v_Position, 1.0);
					}

				)"
			},
			{
				Shader::ShaderType::Fragment,
				Shader::ShaderSourceType::String,
				R"(
					#version 330 core

					uniform vec4 u_Color; // m_shader->SetVec4f("u_Color", m_triangle_color);

					out vec4 final_color;
					void main()
					{
						final_color = u_Color;
					}
				)"
			},
		}));


}


void DynamicTriangleScene::OnEvent(Event& event)
{
	EventDispatcher dispatcher(event);
	// Handle Keyboard ESCAPE Press
	dispatcher.Dispatch<KeyPressedEvent>([this](KeyPressedEvent& e) -> bool
		{
			if (e.GetKeyCode() == KeyCode::Escape) // EXITS scene
			{
				Scene::Exit();
				return true;
			}
			
			if (e.GetKeyCode() == KeyCode::Space) // CHANGES triangle color randomly
			{
				static std::random_device seed{};
				static std::default_random_engine engine{seed()};
				std::uniform_real_distribution<float> dist(0.0f, 1.0f);
				
				glm::vec4 color(dist(engine), dist(engine), dist(engine), dist(engine));
				m_shader->Bind();
				m_shader->SetVec4f("u_Color", color);
				m_shader->Unbind();
			}
			return false;
		});

}

void DynamicTriangleScene::OnUpdate(float dt)
{
	///========= MOVEMENT =========///
// to make triangle go up, all vertices should go up
	static float* vertex_xyz_1 = m_vertices.data() + 0;  // Vertex 1 x,y,z
	static float* vertex_xyz_2 = m_vertices.data() + 3;  // Vertex 2 x,y,z
	static float* vertex_xyz_3 = m_vertices.data() + 6;  // Vertex 3 x,y,z

	const static float SPEED = 2.0f;

	// UP
	if (Input::IsKeyPressed(KeyCode::Up))
	{
		vertex_xyz_1[1] += SPEED * dt; // vertex1.y+
		vertex_xyz_2[1] += SPEED * dt; // vertex2.y+
		vertex_xyz_3[1] += SPEED * dt; // vertex3.y+

	}
	// DOWN
	else if (Input::IsKeyPressed(KeyCode::Down))
	{
		vertex_xyz_1[1] -= SPEED * dt; // vertex1.y-
		vertex_xyz_2[1] -= SPEED * dt; // vertex2.y-
		vertex_xyz_3[1] -= SPEED * dt; // vertex3.y-
	}
	// LEFT
	if (Input::IsKeyPressed(KeyCode::Left))
	{
		vertex_xyz_1[0] -= SPEED * dt; // vertex1.x-
		vertex_xyz_2[0] -= SPEED * dt; // vertex2.x-
		vertex_xyz_3[0] -= SPEED * dt; // vertex3.x-

	}
	// RIGHT
	else if (Input::IsKeyPressed(KeyCode::Right))
	{
		vertex_xyz_1[0] += SPEED * dt; // vertex1.x+
		vertex_xyz_2[0] += SPEED * dt; // vertex2.x+
		vertex_xyz_3[0] += SPEED * dt; // vertex3.x+
	}

	// Update vertex buffer data (in gpu)
	m_vertex_buffer->SetBufferData(m_vertices.data(), m_vertices.size() * sizeof(float));
}

void DynamicTriangleScene::OnDraw()
{
	// Clear buffers
	glAssert(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));
	glAssert(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT));

	// Bind & set uniform u_Color to m_triangle_color which modifies by ui settings
	m_shader->Bind();
	// Bind vertex array to be drawn
	m_vertex_array->Bind();

		// Draw triangle
		glAssert(glDrawElements(GL_TRIANGLES, m_vertex_array->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr));

	// Unbind stuff
	m_shader->Unbind();
	m_vertex_array->Unbind();
}

void DynamicTriangleScene::OnImGuiDraw()
{
	static bool info_showing = true;
	if (info_showing)
	{
		ImGui::Begin("Info");
		ImGui::Text("Use arrows UP DOWN LEFT RIGHT to move the triangle\nCick Space to change triangle color randomly");
			if (ImGui::Button("OK"))
			{
				info_showing = false;
			}
		ImGui::End();

	}
}

void DynamicTriangleScene::OnDestroy()
{
}