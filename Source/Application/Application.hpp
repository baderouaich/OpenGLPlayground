#pragma once
#include <Window/Window.hpp>
#include <memory>
#include <vector>
#include <cstdint>

/*
learnopengl_book.pdf Page 28 section 4.1
Make sure you have OpenGL versions 3.3 or higher installed on your system/hardware otherwise
the application will crash or display undefined behavior.
*/
#define OPENGL_VERSION_MAJOR 1
#define OPENGL_VERSION_MINOR 5

#define BIND_FUN(fun) [this](auto&&... args) -> decltype(auto) { return this->fun(std::forward<decltype(args)>(args)...); }

class Scene;
class ImGuiRenderer;
class Event;
class WindowCloseEvent;
class WindowResizeEvent;
class FrameBufferResizeEvent;

class Application
{
public:
	Application();
	~Application();

public: 
	// App Loop
	void Run();
	
	// Push new scene to back of the stack
	void PushScene(std::unique_ptr<Scene> scene);

	// Update dt
	void UpdateDeltaTime() noexcept;

	// Update FPS
	void UpdateFPS() noexcept;

public:
	void OnEvent(Event& event);
	bool OnWindowClose(WindowCloseEvent& event);
	bool OnWindowResize(WindowResizeEvent& event);
	bool OnFrameBufferResize(FrameBufferResizeEvent& event);

public:
	static Application* GetInstance() noexcept { return m_instance; }
	const std::unique_ptr<Window>& GetWindow() const noexcept { return m_window; }
	float GetDeltaTime() const noexcept { return m_delta_time; }

private: // Window
	std::unique_ptr<Window> m_window;
	
private: // UI
	std::unique_ptr<ImGuiRenderer> m_imgui_renderer;

private: // Scenes
	std::vector<std::unique_ptr<Scene>> m_scenes;

private: // Delta Time
	float m_delta_time{ 0.0f };
	float m_current_frame_time{ 0.0f };
	float m_last_frame_time{ 0.0f };

private: // FPS
	std::uint32_t m_FPS{ 0 };
	float m_FPS_timer{ 0.0f };

private:
	inline static Application* m_instance{ nullptr };
};