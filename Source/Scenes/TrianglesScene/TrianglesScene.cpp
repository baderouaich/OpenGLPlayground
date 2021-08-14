#include "pch.hpp"
#include "TrianglesScene.hpp"
#include <Application/Application.hpp>
#include <Input/Input.hpp>
#include <Event/EventDispatcher.hpp>
#include <Event/KeyEvent.hpp>
#include <glad/glad.h>

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
static const std::array<Vertex, 3> TRIANGLE_VERTICES
{
	Vertex(-1.0f, -1.0f, 0.0f), // left bottom
	Vertex(0.0f, 1.0f, 0.0f), // top center
	Vertex(1.0f, -1.0f, 0.0f) // right bottom
};

void TrianglesScene::OnCreate()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
}

void TrianglesScene::OnEvent(Event& event)
{
	EventDispatcher dispatcher(event);
	// Handle Keyboard ESCAPE Press
	dispatcher.Dispatch<KeyPressedEvent>([this](KeyPressedEvent& e) -> bool
		{
			if (e.GetKeyCode() == KeyCode::Escape)
			{
				auto& data = TRIANGLE_VERTICES[0].data;
				std::printf("Vertex 1(%.2f, %.2f, %.2f)\n", data[0], data[1], data[2]);
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
	// 4.6 Rendering
	glClear(GL_COLOR_BUFFER_BIT);

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
