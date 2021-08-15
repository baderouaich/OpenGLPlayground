#include "pch.hpp"
#include "TrianglesScene.hpp"
#include <Application/Application.hpp>
#include <Input/Input.hpp>
#include <Event/EventDispatcher.hpp>
#include <Event/KeyEvent.hpp>
#include <glad/glad.h>
#include <Utility/OpenGLUtils.hpp>
#include <Shader/Shader.hpp>

struct Vertex
{
	Vertex()
	{
		position.x = position.y = position.z = 0.0f;
	}
	Vertex(float _x, float _y, float _z)
	{
		position.x = _x;
		position.y = _y;
		position.z = _z;
	}
	union { // unify x, y, z with data array
		struct Position { float x, y, z; } position;
		float data[3]; 
	};
};

// 3 Vertices (3 points) to draw triangle (See OpenGL Tutorials/Triangle Vertices.png)
static const float TRIANGLE_VERTICES[]
{
	-1.0f, -1.0f, 0.0f, //xyz left bottom
	0.0f, 1.0f, 0.0f,   //xyz top center
	1.0f, -1.0f, 0.0f   //xyz right bottom
};



void TrianglesScene::OnCreate()
{
	m_shader.reset(new Shader(
		{
			{
				Shader::ShaderType::Vertex,
				Shader::ShaderSourceType::String,
				R"(
					#version 330 core

					void main()
					{
						gl_Position = vec4(0.0, 0.0, 0.0, 0.0);
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
						final_pixel_color = vec4(1.0, 1.0, 1.0, 1.0);
					}
				)"
			},
		}));

	//std::printf("Vertex 1(%.2f, %.2f, %.2f)\n", TRIANGLE_VERTICES[0].data[0], TRIANGLE_VERTICES[0].data[1], TRIANGLE_VERTICES[0].data[2]);
	//std::printf("Vertex 2(%.2f, %.2f, %.2f)\n", TRIANGLE_VERTICES[1].data[0], TRIANGLE_VERTICES[1].data[1], TRIANGLE_VERTICES[1].data[2]);
	//std::printf("Vertex 3(%.2f, %.2f, %.2f)\n", TRIANGLE_VERTICES[2].data[0], TRIANGLE_VERTICES[2].data[1], TRIANGLE_VERTICES[2].data[2]);
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

void TrianglesScene::OnDraw()
{
	glAssert(glClear(GL_COLOR_BUFFER_BIT));

	m_shader->Bind();

	// 4.6 Rendering
	//glAssert(glClear(GL_COLOR_BUFFER_BIT));
	//glMatrixMode(GL_PROJECTION);

	//glAssert(glBegin(GL_TRIANGLES));
	//for (auto v : TRIANGLE_VERTICES)
	//{
	//	//glAssert(glVertex3f(v.position.x, v.position.y, v.position.z));
	//}

	//glAssert(glEnd());
	m_shader->Unbind();
}

void TrianglesScene::OnImGuiDraw()
{
	/*
	const auto [win_w, win_h] = Application::GetInstance()->GetWindow()->GetSize();
	const auto [win_x, win_y] = Application::GetInstance()->GetWindow()->GetPosition();

	ImGui::Begin(typeid(this).name(), nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBackground);
	ImGui::SetWindowPos(ImVec2{ 0.0f, 0.0f });
	ImGui::SetWindowSize(ImVec2{ float(win_w), float(win_h) });
	{
		ImGui::SetCursorPos(ImVec2(0.0f, 0.0f));
		if (ImGui::Button("Back"))
		{
			Scene::Exit();
		}
	}
	ImGui::End();
	*/
}

void TrianglesScene::OnDestroy()
{
}
