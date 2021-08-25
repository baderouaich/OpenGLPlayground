// Book: https://learnopengl.com/book/book_pdf.pdf
/*
5.8 Exercises
To really get a good grasp of the concepts discussed a few exercises were set up. It is advised to
work through them before continuing to the next subject to make sure you get a good grasp of what’s
going on.
1. Try to draw 2 triangles next to each other using glDrawArrays by adding more vertices to your data. 
Solution: /src/1.getting_started/2.3.hello_triangle_
exercise1/.
2. Now create the same 2 triangles using two different VAOs and VBOs for their data. 
Solution:/src/1.getting_started/2.4.hello_triangle_exercis
e2/.
3. Create two shader programs where the second program uses a different fragment shader
that outputs the color yellow; draw both triangles again where one outputs the color yellow.
Solution: /src/1.getting_started/2.5.hello_triangle_exercise3/
*/
#pragma once
#include <Scenes/Scene.hpp>
#include <Graphics/Shader/Shader.hpp>
#include <Graphics/Buffer/VertexBuffer/VertexBuffer.hpp>
#include <Graphics/Buffer/VertexArray/VertexArray.hpp>

class Basics_Page41_Section5_8 : public Scene
{	
public:
	Basics_Page41_Section5_8() = default;
	~Basics_Page41_Section5_8() = default;

public: /* Scene Life Cicle */
	void OnCreate() override
	{
		TRACE_FUNCTION();
	
		// VAO
		m_vertex_array.reset(new VertexArray());


		// VBO
		// See OpenGL Tutorials/Basics_Page41_Section5_8_Vertices.png
		float two_triangle_vertices[]
		{
			// First triangle
			-0.5f, 0.5f, 0.0f,   // top left 0
			-0.5f, -0.5f, 0.0f, // bottom left 1
			0.5f, -0.5f, 0.0f,  // bottom right 2

			// Second triangle
			-0.5f, 0.5f, 0.0f,   // top left 4
			0.5f, 0.5f, 0.0f, // top right 5
			0.5f, -0.5f, 0.0f,  // bottom right 6

		};
		auto vertex_buffer = std::make_shared<VertexBuffer>(VertexBuffer::DrawType::Static);
		vertex_buffer->SetBufferData(two_triangle_vertices, sizeof two_triangle_vertices);

		// tell opengl about our vertices layout, what they contain
		BufferLayout layout(
			{
				BufferElement(Shader::ShaderDataType::Vec3f, "v_Position"), // vertices contain position only
			}
		);
		vertex_buffer->SetLayout(layout);
		m_vertex_array->AddVertexBuffer(vertex_buffer);
		

		// IBO
		constexpr std::array<unsigned int, 6> indices
		{
			0, 1, 2, // to draw first triangle
			3, 4, 5  // to draw second triangle
		};
		auto index_buffer = std::make_shared<IndexBuffer>(indices);
		m_vertex_array->SetIndexBuffer(index_buffer);


		// Shader
		m_shader.reset(new Shader(
			{
				{
					Shader::ShaderType::Vertex,
					Shader::ShaderSourceType::String,
					R"(
						#version 330 core
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
						out vec4 final_color;
						vec4 WHITE = vec4(1.0, 1.0, 1.0, 1.0);
						void main()
						{
							final_color = WHITE; // white
						}
					)"
				},
			}
		));

	}
	
	void OnEvent(Event& event) override
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

	void OnUpdate([[maybe_unused]] float dt)  override 
	{
	}

	void OnDraw()  override 
	{
		// Clear buffers
		glAssert(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));
		glAssert(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT));

		m_shader->Bind();
		m_vertex_array->Bind();

		glDrawArrays(GL_TRIANGLES, 0, m_vertex_array->GetIndexBuffer()->GetCount());
		//glAssert(glDrawElements(GL_TRIANGLES, m_vertex_array->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr));
	
		m_shader->Unbind();
		m_vertex_array->Unbind();

	}

	void OnImGuiDraw()  override 
	{
		//ImGui::Begin(typeid(this).name());
		//ImGui::End();
	}

	void OnDestroy()  override
	{
		TRACE_FUNCTION();

	}

private:
	std::shared_ptr<VertexArray> m_vertex_array;
	std::shared_ptr<Shader> m_shader;
};