#include "pch.hpp"
#include "MainMenuScene.hpp"
#include <Application/Application.hpp>
#include <glad/glad.h>

void MainMenuScene::OnCreate()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
}

void MainMenuScene::OnEvent([[maybe_unused]] Event& event)
{
}

void MainMenuScene::OnUpdate([[maybe_unused]] float dt)
{
}

void MainMenuScene::OnDraw()
{
	// 4.6 Rendering
	glClear(GL_COLOR_BUFFER_BIT);
}

void MainMenuScene::OnImGuiDraw()
{
	const auto [win_w, win_h] = Application::GetInstance()->GetWindow()->GetSize();
	const auto [win_x, win_y] = Application::GetInstance()->GetWindow()->GetPosition();

	ImGui::Begin("Menu", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBackground);
	ImGui::SetWindowPos(ImVec2{ 0.0f, 0.0f });
	ImGui::SetWindowSize(ImVec2{ float(win_w), float(win_h) });
	{
		if (ImGui::Button("Exit"))
		{
			Scene::EndScene();
		}
	}
	ImGui::End();
}

void MainMenuScene::OnDestroy()
{
}
