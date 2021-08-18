#include "pch.hpp"
#include "MainMenuScene.hpp"
#include <Application/Application.hpp>
#include <glad/glad.h>
#include <Scenes/TrianglesScene/TrianglesScene.hpp>

void MainMenuScene::OnCreate()
{
}

void MainMenuScene::OnEvent([[maybe_unused]] Event& event)
{
}

void MainMenuScene::OnUpdate([[maybe_unused]] float dt)
{
}

void MainMenuScene::OnDraw()
{
}

void MainMenuScene::OnImGuiDraw()
{
	const auto [win_w, win_h] = Application::GetInstance()->GetWindow()->GetSize();
	const auto [win_x, win_y] = Application::GetInstance()->GetWindow()->GetPosition();

	const auto button_size = ImVec2(win_w * 0.30f, 36.0f);

	ImGui::Begin(typeid(this).name(), nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove);
	ImGui::SetWindowPos(ImVec2{ 0.0f, 0.0f });
	ImGui::SetWindowSize(ImVec2{ static_cast<float>(win_w), static_cast<float>(win_h) });
	{
		static constexpr const char* title = "OpenGL Playground Scenes Menu";
		static const auto title_size = ImGui::CalcTextSize(title);
		ImGui::SetCursorPos(ImVec2((win_w - title_size.x ) / 2.0f, 60.0f));
		ImGui::Text(title);

		ImGui::SetCursorPos(ImVec2((win_w - button_size.x) / 2.0f, 150.0f));
		if (ImGui::Button("Triangles", button_size))
		{
			Application::GetInstance()->PushScene(std::make_unique<TrianglesScene>());
		}


		ImGui::SetCursorPos(ImVec2((win_w - button_size.x) / 2.0f, win_h - button_size.y - 40.0f));
		if (ImGui::Button("Exit", button_size))
		{
			Scene::Exit();
		}

		ImGui::Spacing();
		ImGui::Separator();
		ImGui::Spacing();
		ImGui::Text("Press ESCAPE to exit from a scene back to main menu");
	}
	ImGui::End();
}

void MainMenuScene::OnDestroy()
{
}
