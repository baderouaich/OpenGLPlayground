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

	const auto button_size = ImVec2(win_w * 0.30f, 45.0f);

	ImGui::Begin(typeid(this).name(), nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove);
	ImGui::SetWindowPos(ImVec2{ 0.0f, 0.0f });
	ImGui::SetWindowSize(ImVec2{ static_cast<float>(win_w), static_cast<float>(win_h) });
	{
		ImGui::SetCursorPos(ImVec2((win_w - button_size.x) / 2.0f, 100.0f));
		if (ImGui::Button("Triangles", button_size))
		{
			Application::GetInstance()->PushScene(std::make_unique<TrianglesScene>());
		}


		ImGui::SetCursorPos(ImVec2((win_w - button_size.x-20.0f) / 2.0f, win_h - button_size.y));
		if (ImGui::Button("Exit", button_size))
		{
			Scene::Exit();
		}
	}
	ImGui::End();
}

void MainMenuScene::OnDestroy()
{
}
