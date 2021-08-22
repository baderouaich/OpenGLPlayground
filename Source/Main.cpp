#include <pch.hpp>
#include "Application/Application.hpp"


int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) try
{
	std::unique_ptr<Application> _App(new Application());
	_App->Run();
	return EXIT_SUCCESS;
}
catch (const std::exception& e)
{
	std::cerr << "[EXCEPTION THROWN]: " << e.what() << std::endl;
	return EXIT_FAILURE;
}
catch (...)
{
	std::cerr << "[UNKNOWN EXCEPTION THROWN]" << std::endl;
	return EXIT_FAILURE;
}


/**
*	Windows Entry Point (for Release & Distribution)
*/
#if defined(PLATFORM_WINDOWS) && (defined(RELEASE) || defined(DIST))

int WINAPI WinMain(
	[[maybe_unused]] _In_ HINSTANCE instance,
	[[maybe_unused]] _In_opt_ HINSTANCE prev_instance,
	[[maybe_unused]] _In_ LPSTR cmd_line,
	[[maybe_unused]] _In_ int cmd_show)
{
	return ::main(__argc, __argv);
}

#endif
