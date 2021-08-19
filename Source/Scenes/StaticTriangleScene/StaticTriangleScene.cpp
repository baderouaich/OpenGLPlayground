#include "pch.hpp"
#include "StaticTriangleScene.hpp"
#include <Application/Application.hpp>
#include <Input/Input.hpp>
#include <Event/EventDispatcher.hpp>
#include <Event/KeyEvent.hpp>
#include <Utility/OpenGLUtils.hpp>
#include <glad/glad.h>

/* OpenGL Triangle Drawing Steps:
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
* 2- Bind & set uniform u_Color to m_triangle_color which modifies by ui settings m_shader->Bind(); && m_shader->SetVec4f("u_Color", m_triangle_color);
* 3- Bind vertex array to be drawn m_vertex_array->Bind();
* 4- Draw triangle glDrawElements(GL_TRIANGLES, m_vertex_array->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
* 5- Unbind Shader & VAO
*/

void StaticTriangleScene::OnCreate()
{
	TRACE_FUNCTION();

	// Make vertex array
	m_vertex_array = std::make_shared<VertexArray>();
	
	// Make statically drawn vertex buffer and set vertices to it (static cuz we're not gonna call SetBufferData each frame, vertices will not change)
	auto vertex_buffer = std::make_shared<VertexBuffer>(VertexBuffer::DrawType::Static);
	vertex_buffer->SetBufferData(TRIANGLE_VERTICES.data(), sizeof(float) * TRIANGLE_VERTICES.size());
	  
	// Tell opengl what my vertices layout is, now vertices contain positions only.
	BufferLayout layout({
		{ Shader::ShaderDataType::Vec3f, "a_Position" },
	});
	vertex_buffer->SetLayout(layout); // set layout to vertex buffer
	// add vertex buffer to vertex buffer array
	m_vertex_array->AddVertexBuffer(vertex_buffer);


	// Make index buffer, to tell opengl which vertex to draw first and last..
	uint32_t indices[3] = { 0, 1, 2 };
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

					uniform vec4 u_Color; // m_shader->SetVec4f("u_Color", m_triangle_color);

					out vec4 final_color;
					void main()
					{
						final_color = u_Color;
					}
				)"
			},
		}));
	m_shader->Bind();


}


void StaticTriangleScene::OnEvent(Event& event)
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

void StaticTriangleScene::OnUpdate(float dt)
{
}

void StaticTriangleScene::OnDraw()
{
	// Clear buffers
	glAssert(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));
	glAssert(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT));

	// Bind & set uniform u_Color to m_triangle_color which modifies by ui settings
	m_shader->Bind(); 
	m_shader->SetVec4f("u_Color", m_triangle_color);

	// Bind vertex array to be drawn
	m_vertex_array->Bind();

	// Draw triangle
	glAssert(glDrawElements(GL_TRIANGLES, m_vertex_array->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr));

	// Unbind stuff
	m_shader->Unbind();
	m_vertex_array->Unbind();
}

void StaticTriangleScene::OnImGuiDraw()
{
	ImGui::Begin("Settings");
		ImGui::ColorEdit4("Triangle Color", glm::value_ptr(m_triangle_color));
	ImGui::End();
}

void StaticTriangleScene::OnDestroy()
{
	TRACE_FUNCTION();

}

























#if OPENGL_VERSION_MAJOR <= 2
// 3 Vertices (3 points) to draw triangle (See OpenGL Tutorials/Triangle Vertices.png)
std::array<float, 9> TRIANGLE_VERTICES
{
	/*Vertex 1 xyz */ -1.0f, -1.0f, 0.0f, // left bottom 0
	/*Vertex 2 xyz */ 0.0f, 1.0f, 0.0f,   // top center 1
	/*Vertex 3 xyz */ 1.0f, -1.0f, 0.0f   // right bottom 2

};

void TriangleScene::OnCreate()
{
}

void TriangleScene::OnEvent(Event& event)
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

void TriangleScene::OnUpdate(float dt)
{
	if (Input::IsKeyPressed(KeyCode::Left))
	{
		TRIANGLE_VERTICES[0] -= dt;
		TRIANGLE_VERTICES[1] -= dt;
	}
	if (Input::IsKeyPressed(KeyCode::Right))
	{
		TRIANGLE_VERTICES[2] += dt;
		TRIANGLE_VERTICES[3] += dt;
	}
	if (Input::IsKeyPressed(KeyCode::Up))
	{
		TRIANGLE_VERTICES[4] += dt;
		TRIANGLE_VERTICES[5] += dt;
	}
	if (Input::IsKeyPressed(KeyCode::Down))
	{
		TRIANGLE_VERTICES[6] -= dt;
		TRIANGLE_VERTICES[7] -= dt;
	}
	if (Input::IsKeyPressed(KeyCode::Space))
	{
		TRIANGLE_VERTICES[8] = 0.0f;
	}
}
void TriangleScene::OnDraw()
{
	glAssert(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));
	glAssert(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT));

#if OPENGL_VERSION_MAJOR <= 2
	glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
	glBegin(GL_TRIANGLES);
	for (std::size_t i = 0; i < TRIANGLE_VERTICES.size(); i += 3)
	{
		glVertex3f(TRIANGLE_VERTICES[i + 0], TRIANGLE_VERTICES[i + 1], TRIANGLE_VERTICES[i + 2]);

	}
	glEnd();
#else
	#error change OPENGL_VERSION_MAJOR & OPENGL_VERSION_MINOR in Application.hpp to 3.3
#endif
}

void TriangleScene::OnImGuiDraw()
{
}

void TriangleScene::OnDestroy()
{
}


#endif













#if 0
#include "pch.hpp"
#include "TriangleScene.hpp"
#include <Application/Application.hpp>
#include <Input/Input.hpp>
#include <Event/EventDispatcher.hpp>
#include <Event/KeyEvent.hpp>
#include <glad/glad.h>
#include <Utility/OpenGLUtils.hpp>



void TriangleScene::InitVertexBuffer()
{
	// 3 Vertices (3 points) to draw triangle (See OpenGL Tutorials/Triangle Vertices.png)
	const float TRIANGLE_VERTICES[]
	{
#if 0
		/*Vertex 1 xyz */ - 1.0f, -1.0f, 0.0f, // left bottom 0
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
	m_vertex_buffer->SetBufferData(TRIANGLE_VERTICES, sizeof(TRIANGLE_VERTICES));

	BufferLayout layout(
		{
			{ Shader::ShaderDataType::Vec4f, "a_Color" }, // see shader above
		});
	m_vertex_buffer->SetLayout(layout);

	m_vertex_buffer->Bind();

}


void TriangleScene::InitIndexBuffer()
{
	std::array<std::uint32_t, 3> indices
	{
		0, 1, 2
	};
	m_index_buffer.reset(new IndexBuffer(indices.data(), static_cast<std::uint32_t>(indices.size())));
	m_index_buffer->Bind();
}

void TriangleScene::InitVertexBufferArray()
{
	m_vertex_array.reset(new VertexArray());
	m_vertex_array->AddVertexBuffer(m_vertex_buffer);
	m_vertex_array->SetIndexBuffer(m_index_buffer);
	m_vertex_array->Bind();
}

void TriangleScene::InitShader()
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

void TriangleScene::OnCreate()
{
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	this->InitVertexBuffer();
	this->InitIndexBuffer();
	this->InitVertexBufferArray();

	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	this->InitShader();

}

void TriangleScene::OnEvent(Event& event)
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

void TriangleScene::OnUpdate([[maybe_unused]] float dt)
{

}

// https://github.com/JoeyDeVries/LearnOpenGL/blob/master/src/1.getting_started/2.2.hello_triangle_indexed/hello_triangle_indexed.cpp
void TriangleScene::OnDraw()
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



	//m_shader->Unbind();
	//m_vertex_array->Unbind();

}

void TriangleScene::OnImGuiDraw()
{
}

void TriangleScene::OnDestroy()
{
}
#endif