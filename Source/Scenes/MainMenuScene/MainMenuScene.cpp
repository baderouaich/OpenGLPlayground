#include "pch.hpp"
#include "MainMenuScene.hpp"
#include <Application/Application.hpp>
#include <glad/glad.h>
#include <Utility/OpenGLUtils.hpp>

void MainMenuScene::OnCreate()
{
	IMJPEG_TRACE_FUNCTION();
}

void MainMenuScene::OnEvent([[maybe_unused]] Event& event)
{
}

void MainMenuScene::OnUpdate([[maybe_unused]] float dt)
{
}

void MainMenuScene::OnDraw()
{
	glAssert(glClearColor(0.22f, 0.9f, 0.7f, 0.95f));
	glAssert(glClear(GL_COLOR_BUFFER_BIT));
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

		float y = 70.0f;

		ImGui::SetCursorPos(ImVec2((win_w - button_size.x) / 2.0f, y += 50.0f));
		if (ImGui::Button("Static Triangle", button_size))
		{
			//Application::GetInstance()->PushScene(std::make_unique<StaticTriangleScene>());
		}
		ImGui::SetCursorPos(ImVec2((win_w - button_size.x) / 2.0f, y += 50.0f));
		if (ImGui::Button("Dynamic Triangle", button_size))
		{
			//Application::GetInstance()->PushScene(std::make_unique<DynamicTriangleScene>());
		}

		ImGui::SetCursorPos(ImVec2((win_w - button_size.x) / 2.0f, y += 50.0f));
		if (ImGui::Button("Static Square", button_size))
		{
			//Application::GetInstance()->PushScene(std::make_unique<StaticSquareScene>());
		}
		ImGui::SetCursorPos(ImVec2((win_w - button_size.x) / 2.0f, y += 50.0f));
		if (ImGui::Button("Dynamic Square", button_size))
		{
			//Application::GetInstance()->PushScene(std::make_unique<DynamicSquareScene>());
		}

		ImGui::SetCursorPos(ImVec2((win_w - button_size.x) / 2.0f, y += 50.0f));
		if (ImGui::Button("Exercices", button_size))
		{
			//Application::GetInstance()->PushScene(std::make_unique<ExercicesScene>());
		}


		ImGui::SetCursorPos(ImVec2((win_w - button_size.x) / 2.0f, win_h - button_size.y - 40.0f));
		if (ImGui::Button("Exit", button_size))
		{
			Scene::Exit();
		}

		ImGui::Spacing();
		ImGui::Separator();
		ImGui::Spacing();
		ImGui::Text("**NOTE**: Press ESCAPE to exit from a scene");
	}
	ImGui::End();

}

void MainMenuScene::OnDestroy()
{
	IMJPEG_TRACE_FUNCTION();

}
