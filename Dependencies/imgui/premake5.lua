-- imgui 1.81 release
project "imgui"
	kind "StaticLib"
	language "C++"
	cppdialect "C++latest" -- C++20
	staticruntime "On"

	targetdir ("Bin/" .. outputdir .. "/%{prj.name}")
	objdir ("Bin-Intermediate/" .. outputdir .. "/%{prj.name}")

    warnings "Off" -- turn Off warnings for this library

    includedirs
    {
    	"./",
    	"%{IncludeDir.glad}", -- tell imgui where is OpenGL loader lib include located
        "%{IncludeDir.glfw}", -- tell imgui where is glfw include located
    }

	files
	{
		"premake5.lua",
		
		"*.h",
		"*.cpp", -- Dont include backends/*, use only *.cpp instead of **.cpp (recurse)
	}

	-- Platform --
	filter "system:windows"
		systemversion "latest"
		defines
		{
		}
		links
		{
		}

	filter "system:linux"
		links
		{
		}
		defines
		{
		}

	filter "system:macosx"
		defines
		{
		}	
		links
		{
		}	


	--- Configurations ---
	filter "configurations:Debug"
		runtime "Debug"
		symbols "Full" --vs17 and newer | symbols "On"
		optimize "Off" -- No optimization will be performed.

	filter "configurations:Release"
		runtime "Release"
		optimize "On" -- Perform a balanced set of optimizations.
		inlining "Explicit" -- Only inline functions explicitly marked with the inline keyword.

	filter "configurations:Dist"
		runtime "Release"
		optimize "Full" -- Full optimization.
		inlining "Auto" -- Inline any suitable function for full performance