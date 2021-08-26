/// Precompiled Header ///
#pragma once
#ifndef IMJPEG_PCH_H
#define IMJPEG_PCH_H


/// Platform specific includes ///
/// Windows
#if defined(IMJPEG_PLATFORM_WINDOWS)
	#include <Windows.h>
	#include <TlHelp32.h>
#endif
///


/// OpenGL: GLAD
#pragma warning(push, 0) /* Disable all <glad/glad.h>'s warnings */
#include <glad/glad.h>
#pragma warning(pop)
///

/// Graphic library framwork: GLFW
#pragma warning(push, 0) /* Disable all <GLFW/glfw3.h>'s warnings */
#include <GLFW/glfw3.h>
#pragma warning(pop)
///

/// UI: ImGui
#pragma warning(push, 0) /* Disable all  <imgui.h>'s warnings */
#include <imgui.h>
#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_glfw.h>
#pragma warning(pop)
///



///the C++20 Standard Libraries
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <chrono>
#include <random>
#include <algorithm>
#include <vector>
#include <array>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <set>
#include <stack>
#include <thread>
#include <memory>
#include <queue>
#include <deque>
#include <utility>
#include <list>
#include <future>
#include <functional>
#include <iomanip>
#include <numeric>
#include <regex>
#include <exception>
#include <source_location>	// std::source_location::current() file column function...

#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <cassert>
#include <cstdint>
#include <cstring>

///



#endif // !IMJPEG_PCH_H

