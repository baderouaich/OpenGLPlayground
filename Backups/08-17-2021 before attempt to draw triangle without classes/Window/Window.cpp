#include "pch.hpp"
#include "Window.hpp"
#include <Application/Application.hpp> // for opengl version define
#include <glad/glad.h>
#include <Event/Event.hpp>
#include <Event/ApplicationEvent.hpp>
#include <Event/KeyEvent.hpp>
#include <Event/MouseEvent.hpp>

Window::Window(std::string title, const int width, const int height)
	:
	m_title(std::move(title))
{
	if (!InitGLFW(title, width, height))
		throw std::runtime_error("Failed to initialize GLFW");
	if (!InitGLFWCallbacks())
		throw std::runtime_error("Failed to initialize GLFW Callbacks");
	if (!InitGLAD())
		throw std::runtime_error("Failed to initialize OpenGL");
}

Window::~Window()
{
	// Cleanup GLFW
	glfwDestroyWindow(m_window);
	glfwTerminate();
}

std::pair<int, int> Window::GetSize()
{
	int width{}, height{};
	glfwGetWindowSize(m_window, &width, &height);
	return std::make_pair(width, height);
}

std::pair<int, int> Window::GetPosition()
{
	int x{}, y{};
	glfwGetWindowPos(m_window, &x, &y);
	return std::make_pair(x, y);
}

GLFWwindow* Window::GetGLFWwindow() const noexcept
{
	return m_window;
}

bool Window::ShouldClose() const noexcept
{
	return !!glfwWindowShouldClose(m_window);
}

bool Window::IsFullscreen() const noexcept
{
	return glfwGetWindowMonitor(m_window) != nullptr;
}

const std::string& Window::GetTitle() const noexcept
{
	return m_title;
}

void Window::SetShouldClose(const bool should_close) noexcept
{
	glfwSetWindowShouldClose(m_window, should_close);
}

void Window::SetEventCallback(const EventCallback& callback) noexcept
{
	m_event_callback = callback;
}

void Window::PollEvents() const noexcept
{
	glfwPollEvents();
}

void Window::SetTitle(const std::string& title, std::uint32_t FPS) noexcept
{
	m_title = title;
	std::ostringstream oss{};
	oss << m_title;
	if(FPS != 0)
		oss << " - FPS: " << FPS;
	glfwSetWindowTitle(m_window, oss.str().c_str());
}

void Window::SwapBuffers() const noexcept
{
	glfwSwapBuffers(m_window);
}

bool Window::InitGLAD()
{
	/* Init Glad OpenGL */
	// Method 2, to resolve conversion warning C4191: 'type cast': unsafe conversion from 'GLFWglproc (__cdecl *)(const char *)' to 'GLADloadproc'
	auto glfw_gl_proc = glfwGetProcAddress;
	auto glad_proc = *static_cast<GLADloadproc*>((void*)&glfw_gl_proc);
	const bool loaded = !!gladLoadGLLoader(glad_proc);
	return loaded;
}

bool Window::InitGLFW(const std::string title, const int width, const int height)
{
	//INIT GLFW
	if (glfwInit() != GLFW_TRUE)
		return false;

	/// Set error callback
	glfwSetErrorCallback([](int err_code, const char* message) -> void
	{
		std::cerr << "GLFW ERROR #" << err_code << ": " << message << std::endl;
	});
	
	/// Set modern opengl core profile (which enables us to use latest funcs like debugging...)
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/// Set window hints
	//OpenGL version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OPENGL_VERSION_MAJOR);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OPENGL_VERSION_MINOR);

	///Making window: floating, non resizable, maximized, transparent
	glfwWindowHint(GLFW_FLOATING, GLFW_FALSE); // always on top
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
	glfwWindowHint(GLFW_MAXIMIZED, GLFW_FALSE);
	glfwWindowHint(GLFW_DECORATED, GLFW_TRUE); // hide/show title bar title - [] x 
	glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_FALSE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
#endif

#ifdef DEBUG
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
#endif

	m_window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
	if (!m_window)
	{
		glfwTerminate();
		return false;
	}



	//MUST BE RIGHT AFTER WINDOW CREATED
	glfwMakeContextCurrent(m_window); // !! IMPORTANT FOR GLAD TO WORK !!

	//Enable/Disable vsync
	glfwSwapInterval(FrameRate::Unlimited);

	//Set this window as data ptr to access in callbacks to avoid static funcs headaches
	glfwSetWindowUserPointer(m_window, this);

	return true;
}

bool Window::InitGLFWCallbacks()
{
	/// Set GLFW Callbacks ///
	if (!m_window)
		return false;

	//Window ReSize
	glfwSetWindowSizeCallback(m_window, [](GLFWwindow* window, int width, int height)
		{
			Window& this_window = *static_cast<Window*>(glfwGetWindowUserPointer(window));
			if (!this_window.IsFullscreen())
			{
				WindowResizeEvent event(width, height);
				this_window.m_event_callback(event);
			}
		});

	//Framebuffer ReSize
	glfwSetFramebufferSizeCallback(m_window, [](GLFWwindow* window, int fbw, int fbh)
		{
			Window& this_window = *static_cast<Window*>(glfwGetWindowUserPointer(window));

			FrameBufferResizeEvent event(fbw, fbh);
			this_window.m_event_callback(event);
		});

	//Window Move
	glfwSetWindowPosCallback(m_window, [](GLFWwindow* window, int x, int y)
		{
			Window& this_window = *static_cast<Window*>(glfwGetWindowUserPointer(window));
			if (!this_window.IsFullscreen()) // fullscreen triggers a move event, ignore it.
			{
				WindowMoveEvent event(x, y);
				this_window.m_event_callback(event);
			}
		});

	//Window Maximized
	glfwSetWindowMaximizeCallback(m_window, [](GLFWwindow* window, int maximized)
		{
			Window& this_window = *static_cast<Window*>(glfwGetWindowUserPointer(window));
			const bool is_maximized = maximized == GLFW_TRUE;
			WindowMaximizedEvent event(is_maximized);
			this_window.m_event_callback(event);
		});


	//Window Focus
	glfwSetWindowFocusCallback(m_window, [](GLFWwindow* window, int focused)
		{
			Window& this_window = *static_cast<Window*>(glfwGetWindowUserPointer(window));
			if (focused == GLFW_TRUE)
			{
				WindowFocusEvent event;
				this_window.m_event_callback(event);
			}
			else
			{
				WindowFocusLostEvent event;
				this_window.m_event_callback(event);
			}
		});

	//Window Close
	glfwSetWindowCloseCallback(m_window, [](GLFWwindow* window)
		{
			Window& this_window = *static_cast<Window*>(glfwGetWindowUserPointer(window));
			WindowCloseEvent event;
			this_window.m_event_callback(event);
		});

	//Window Files Drop Event
	glfwSetDropCallback(m_window, [](GLFWwindow* window, int path_count, const char* paths[])
		{
			Window& this_window = *static_cast<Window*>(glfwGetWindowUserPointer(window));

			std::vector<fs::path> filenames{};
			filenames.reserve(path_count);
			for (int i = 0; i < path_count; i++)
			{
				filenames.emplace_back(fs::path(paths[i]));
			}

			WindowFileDropEvent event(filenames);
			this_window.m_event_callback(event);
		});

	//Key
	glfwSetKeyCallback(m_window, [](GLFWwindow* window, int key, int /*scancode*/, int action, int /*mods*/)
		{
			Window& this_window = *static_cast<Window*>(glfwGetWindowUserPointer(window));
			switch (action)
			{
			case GLFW_PRESS:
			{
				KeyPressedEvent event(static_cast<KeyCode>(key), 0);
				this_window.m_event_callback(event);
			}
			break;
			case GLFW_RELEASE:
			{
				KeyReleasedEvent event(static_cast<KeyCode>(key));
				this_window.m_event_callback(event);
			}
			break;
			case GLFW_REPEAT:
			{
				KeyPressedEvent event(static_cast<KeyCode>(key), 1);
				this_window.m_event_callback(event);
			}
			break;
			default:
				std::cout << "Unsupported Key Event " << key << std::endl;
				break;
			}
		});

	//Key Typed
	glfwSetCharCallback(m_window, [](GLFWwindow* window, unsigned int keycode)
		{
			Window& this_window = *static_cast<Window*>(glfwGetWindowUserPointer(window));
			KeyTypedEvent event(static_cast<KeyCode>(keycode));
			this_window.m_event_callback(event);
		});


	//Mouse button 
	glfwSetMouseButtonCallback(m_window, [](GLFWwindow* window, int button, int action, int /*mods*/)
		{
			Window& this_window = *static_cast<Window*>(glfwGetWindowUserPointer(window));
			switch (action)
			{
			case GLFW_PRESS:
			{
				MouseButtonPressedEvent event(static_cast<MouseCode>(button));
				this_window.m_event_callback(event); //dispatch event
			}
			break;
			case GLFW_RELEASE:
			{
				MouseButtonReleasedEvent event(static_cast<MouseCode>(button));
				this_window.m_event_callback(event); //dispatch event
			}
			break;
			default:
				std::cout << "Unsupported Mouse Button Event " << button << std::endl;
				break;
			}
		});

	//Mouse Wheel Scroll
	glfwSetScrollCallback(m_window, [](GLFWwindow* window, double xOffset, double yOffset)
		{
			Window& this_window = *static_cast<Window*>(glfwGetWindowUserPointer(window));
			MouseWheelEvent event(static_cast<float>(xOffset), static_cast<float>(yOffset));
			this_window.m_event_callback(event);
		});

	//Mouse Move
	glfwSetCursorPosCallback(m_window, [](GLFWwindow* window, double xPos, double yPos)
		{
			Window& this_window = *static_cast<Window*>(glfwGetWindowUserPointer(window));
			MouseMotionEvent event(static_cast<float>(xPos), static_cast<float>(yPos));
			this_window.m_event_callback(event); //dispatch event
		});


	return true;
}

