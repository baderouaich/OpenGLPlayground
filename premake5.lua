require("premake", ">=5.0.0-alpha15") -- allow premake 5.0.0 alpha15 and up only 

workspace "OpenGLPlayground"  -- Workspace which is the solution in windows, in xcode will be something else
	architecture "x86_64" -- Targeted architecture x64
	startproject "OpenGLPlayground" -- Set 'OpenGLPlayground' project as start up project
	
	configurations
	{
		"Debug", 
		"Release", 
		"Dist" -- Distribution, when everything is done, optimization: Full
	}
	
	--https://github.com/premake/premake-core/wiki/flags
	flags
	{
		"MultiProcessorCompile", -- Speed up compile time, Enable Visual Studio to use multiple compiler processes when building.
	}


--Set up the output directory For multiplatforms, see https://github.com/premake/premake-core/wiki/Tokens
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["glfw"]			= "%{wks.location}/Dependencies/glfw/include"  -- Graphics Library Framework lib
IncludeDir["glad"]			= "%{wks.location}/Dependencies/glad/include"-- OpenGL lib
IncludeDir["imgui"]			= "%{wks.location}/Dependencies/imgui" 	-- UI lib
IncludeDir["glm"]			= "%{wks.location}/Dependencies/glm/include" 	-- GLM math lib

-- Organize libs solution in a single filtered directory 
group "Dependencies"
	include "Dependencies/glfw" --there is a premake5.lua in Dependencies/glfw/ which will be detected and set things up for us
	include "Dependencies/glad"
	include "Dependencies/imgui"
	include "Dependencies/glm"
group ""

project "OpenGLPlayground"
	language "C++"
	cppdialect "C++latest" -- C++20 
	staticruntime "On"


	---[[ Binary Output dirs ]]---
	targetdir ("%{wks.location}/Bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/Bin-Intermediate/" .. outputdir .. "/%{prj.name}")

	-- Precompiled Header
	pchheader "pch.hpp"
	pchsource "Source/pch.cpp"
	

	---[[ Disable RTTI to optimize if we're not using dynamic_cast or typeid ]]---
	--rtti "Off"

	---[[ Enable the toolset's maximum warning level ]]---
	warnings "Extra"
	
	---[[ Source files ]]---
	files
	{
		"Resources/**.*",

		"premake5.lua",
		"Source/**.hpp",
		"Source/**.cpp"
	}

	---[[ Add Libraries include directories ]]---	
	includedirs
	{
		"Source", -- include Source/ dir so we can include e.g "Core/Core.hpp" directly, not to keep going back steps e.g "../../Core/Core.hpp"
		"%{IncludeDir.glfw}",
		"%{IncludeDir.glad}",
		"%{IncludeDir.imgui}",
		"%{IncludeDir.glm}",
	}


	---[[ Link Libraries (Order Matters) ]]---
	links
	{
		"glfw", -- Links glfw.lib
		"glad", 
		"imgui",
		"glm",
	}


	---[[ Platform ]]---
	filter "system:windows"
		systemversion "latest"
		--entrypoint "WinMainCRTStartup" -- use WinMain as entry point

		defines
		{
			"PLATFORM_WINDOWS",

			-- Common MSVC warnings defines
			"_CRT_SECURE_NO_DEPRECATE",
			"_CRT_SECURE_NO_WARNINGS",
			"_CRT_NONSTDC_NO_WARNINGS",
			"_SILENCE_ALL_CXX17_DEPRECATION_WARNINGS",
		}
		links
		{
			"opengl32", -- Loads windows opengl32 kernel .lib
		}

	filter "system:linux"
		defines
		{
			"PLATFORM_LINUX",
		}
		links
		{
			"GL", -- link opengl lib
			"X11", -- x11 Linux gui libs
			"dl", -- dynamic loader interface
			"pthread", -- std::thread
			"stdc++fs" -- std::filesystem
		}

	filter "system:macosx"
		defines
		{
			"PLATFORM_MACOS",
		}	
		links
		{
			-- TODO
			"GL", -- link opengl lib
			"pthread", -- std::thread
			"stdc++fs" -- std::filesystem
		}

	
	---[[ Configurations ]]---
	filter "configurations:Debug"
		kind "ConsoleApp" -- Debug we need console for logging
		defines "DEBUG"
		runtime "Debug"
		symbols "Full" --vs17 and newer | symbols "On"
		optimize "Off" -- No optimization will be performed.


	filter "configurations:Release"
		kind "ConsoleApp" -- we need console for logging in CLI
		--kind "WindowedApp" -- Release as windowed application
		defines "RELEASE"
		runtime "Release"
		optimize "On" -- Perform a balanced set of optimizations.
		inlining "Explicit" -- Only inline functions explicitly marked with the inline keyword.
		
		flags
		{
			-- Only applicable in Release configurations
			"LinkTimeOptimization", -- Link Time Optimization (LTO) refers to program optimization during linking. The linker pulls all object files together and combines them into one program. The linker can see the whole of the program, and can therefore do whole-program analysis and optimization.
		}

	filter "configurations:Dist"
		kind "ConsoleApp" -- we need console for logging in CLI
		--kind "WindowedApp" -- Distribution as windowed application
		defines "DIST"
		runtime "Release"
		optimize "Full" -- Full optimization.
		inlining "Auto" -- Inline any suitable function for full performance
		
		flags
		{
			-- Only applicable in Release configurations
			"LinkTimeOptimization", -- Link Time Optimization (LTO) refers to program optimization during linking. The linker pulls all object files together and combines them into one program. The linker can see the whole of the program, and can therefore do whole-program analysis and optimization.
		}
