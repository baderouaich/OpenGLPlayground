#include "pch.hpp"
#include "ExercicesScene.hpp"
#include <Application/Application.hpp>
#include <glad/glad.h>
#include <Scenes/TriangleScene/TriangleScene.hpp>
#include <Scenes/SquareScene/SquareScene.hpp>
#include "Basics_Page41_Section5_8/Basics_Page41_Section5_8.hpp"
#include <Event/EventDispatcher.hpp>
#include <Event/KeyEvent.hpp>

void ExercicesScene::OnCreate()
{
}

void ExercicesScene::OnEvent(Event& event)
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

void ExercicesScene::OnUpdate([[maybe_unused]] float dt)
{
}

void ExercicesScene::OnDraw()
{
}

void ExercicesScene::OnImGuiDraw()
{
	const auto [win_w, win_h] = Application::GetInstance()->GetWindow()->GetSize();
	const auto [win_x, win_y] = Application::GetInstance()->GetWindow()->GetPosition();

	const auto button_size = ImVec2(win_w * 0.30f, 36.0f);

	ImGui::Begin(typeid(this).name(), nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove);
	ImGui::SetWindowPos(ImVec2{ 0.0f, 0.0f });
	ImGui::SetWindowSize(ImVec2{ static_cast<float>(win_w), static_cast<float>(win_h) });
	{
		static constexpr const char* title = "Book Exercices Scenes Menu";
		static const auto title_size = ImGui::CalcTextSize(title);
		ImGui::SetCursorPos(ImVec2((win_w - title_size.x) / 2.0f, 60.0f));
		ImGui::Text(title);

	    float y = 120.0f;
		ImGui::SetCursorPos(ImVec2((win_w - button_size.x) / 2.0f, y += 50.0f));
		if (ImGui::Button("Basics Page 41 Section 5.8", button_size))
		{
			Application::GetInstance()->PushScene(std::make_unique<Basics_Page41_Section5_8>());
		}
	
	}
	ImGui::End();
}

void ExercicesScene::OnDestroy()
{
}
