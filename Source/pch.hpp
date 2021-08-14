/// Precompiled Header ///
#pragma once
#ifndef PCH_H
#define PCH_H


/// Platform specific includes ///
/// Windows
#if defined(PLATFORM_WINDOWS)
	#include <Windows.h>
	#include <TlHelp32.h>
#endif
///


/// OpenGL: GLAD
#include <glad/glad.h>
///

/// Graphic library framwork: GLFW
#include <GLFW/glfw3.h>
///

/// UI: ImGui
#include <imgui.h>
#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_glfw.h>
///



///the C++ Standard Libraries
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

#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <cassert>
#include <cstdint>
#include <cstring>

///



#endif // !PCH_H

