#pragma once
#include <string>
#include <GLFW/glfw3.h>
#include <Event/Event.hpp>

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

	using EventCallback = std::function<void(Event&)>;

public:
	Window(std::string title, const int width, const int height);
	~Window();

public:
	std::pair<int, int> GetSize();
	std::pair<int, int> GetPosition();
	GLFWwindow* GetGLFWwindow() const noexcept;
	bool ShouldClose() const noexcept;
	bool IsFullscreen() const noexcept;
	const std::string& GetTitle() const noexcept;

public:
	void SetShouldClose(const bool should_close) noexcept;
	void SetEventCallback(const EventCallback& callback) noexcept;
	void SetTitle(const std::string& title, std::uint32_t FPS = 0) noexcept;

public:
	void PollEvents() const noexcept;
	void SwapBuffers() const noexcept;

private:
	bool InitGLFW(const std::string title, const int width, const int height);
	bool InitGLFWCallbacks();
	bool InitGLAD();
	bool InitOpenGLOptions();


private:
	std::string m_title;

private:
	GLFWwindow* m_window;

private: /* Events */
	EventCallback m_event_callback;
};

