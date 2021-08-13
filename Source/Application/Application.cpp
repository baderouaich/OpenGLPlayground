#include "pch.hpp"
#include "Application.hpp"
#include <Utility/OpenGLUtils.hpp>
#include <UI/ImGuiRenderer.hpp>
#include <Scene/MainMenuScene/MainMenuScene.hpp>
#include <Event/EventDispatcher.hpp>
#include <Event/ApplicationEvent.hpp>
#include <Event/ApplicationEvent.hpp>


Application::Application()
	:
	m_window(new Window("OpenGL Play Ground", 800, 600))
{
	if (m_instance)
		throw std::runtime_error("Application instance already created");

	m_instance = this;

	// Init imgui renderer
	m_imgui_renderer = std::make_unique<ImGuiRenderer>();

	// Push Main Menu Scene as initial scene
	PushScene(std::make_unique<MainMenuScene>());
}

void Application::PushScene(std::unique_ptr<Scene> scene)
{
	m_scenes.emplace_back(std::move(scene));
	m_scenes.back()->OnCreate();
}

void Application::UpdateDeltaTime() noexcept
{
	m_current_frame_time = static_cast<float>(glfwGetTime());
	m_delta_time = m_current_frame_time - m_last_frame_time;
	m_last_frame_time = m_current_frame_time;
}


void Application::OnEvent(Event& event)
{
	// Listen for WindowClose, WindowResize and FrameBufferResizeEvent Events
	EventDispatcher dispatcher(event);
	/*dispatcher.Dispatch<WindowCloseEvent>([this](WindowCloseEvent& e) -> bool
	{
	});*/
	dispatcher.Dispatch<WindowCloseEvent>(BIND_FUN(Application::OnWindowClose));
	dispatcher.Dispatch<WindowResizeEvent>(BIND_FUN(Application::OnWindowResize));
	dispatcher.Dispatch<FrameBufferResizeEvent>(BIND_FUN(Application::OnFrameBufferResize));

	// Alert All Scenes OnEvent
	for (auto it = m_scenes.rbegin(); it != m_scenes.rend(); ++it)
	{
		// Alert each scene with the triggered event
		(*it)->OnEvent(event);

		// if event is handled, stop passing it to other scenes
		if (event.IsHandled())
			break;
	}
}

bool Application::OnWindowClose(WindowCloseEvent& /*event*/)
{
		this->m_window->SetShouldClose(true);
		return true; // the end of the app, all events are handled.
}

bool Application::OnWindowResize(WindowResizeEvent& event)
{
	// Update OpenGL Viewport
	glAssert(glViewport(0, 0, event.GetWidth(), event.GetHeight()));
	return false;
}



bool Application::OnFrameBufferResize(FrameBufferResizeEvent& event)
{
	// Update OpenGL Viewport
	glAssert(glViewport(0, 0, event.GetWidth(), event.GetHeight()));
	return false;
}


void Application::Run()
{
	while (!m_window->ShouldClose())
	{
		// Poll Events
		m_window->PollEvents();

		// Grab current active scene from back stack
		const auto& active_scene = m_scenes.back();

		// Update & Draw (only if there are scenes, otherwise end app).
		if (!m_scenes.empty())
		{
			//Update
			{
				// Delta time
				UpdateDeltaTime();
				// Update back scene (last pushed scene which is the active one)
				active_scene->OnUpdate(m_delta_time);
			}

			//Draw
			{
				// Draw back scene (last pushed scene which is the active one)
				active_scene->OnDraw();

				// ImGui Draw
				m_imgui_renderer->Begin();
					active_scene->OnImGuiDraw();
				m_imgui_renderer->End();

				// Force execution of GL commands in finite time 
				glAssert(glFlush());
			}

			// Swap Buffers
			m_window->SwapBuffers();

			// Check if the current active scene wants to quit (scene must call EndScene to be destroyed)
			if (active_scene->WantsToQuit())
			{
				// Notify user before ending scene
				active_scene->OnDestroy();
				// Destroy Scene
				m_scenes.pop_back(); // Remove scene from vector (btw vector will call ~unique_ptr to cleanup memory)
			}

		}
		else // No scenes ? End App.
		{
			m_window->SetShouldClose(true);
		}
	}
}



Application::~Application()
{
	// Call Scene::OnDestroy()
	std::for_each(m_scenes.rbegin(), m_scenes.rend(), [](const std::unique_ptr<Scene>& scene)
	{
		scene->OnDestroy();
	});
	m_scenes.clear();
}