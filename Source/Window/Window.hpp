#pragma once
#include <string>
#include <GLFW/glfw3.h>
#include <Event/Event.hpp>

static constexpr auto PPG_GL_VERSION_MAJOR = 3;
static constexpr auto PPG_GL_VERSION_MINOR = 3;

class Window final
{
	/*
		Interval 0: unlimited FPS
		Interval 1: 60 FPS
		Interval 2: 30 FPS
	*/
	enum FrameRate : std::int32_t
	{
		Unlimited = 0,
		$60 = 1,
		$30 = 2,
	};

public:
	Window(const std::string title, const int width, const int height);
	~Window();

public:
	std::pair<int, int> GetSize();
	std::pair<int, int> GetPosition();
	GLFWwindow* GetGLFWwindow() const noexcept;
	bool ShouldClose() const noexcept;
	bool IsFullscreen() const noexcept;

public:
	void SetShouldClose(const bool should_close) noexcept;

public:
	void PollEvents() const noexcept;
	void SwapBuffers() const noexcept;

private:
	bool InitGLAD();
	bool InitGLFW(const std::string title, const int width, const int height);
	bool InitGLFWCallbacks();


private:
	GLFWwindow* m_window;

private: /* Events */
	using EventCallback = std::function<void(Event&)>;
	EventCallback m_event_callback;

};

