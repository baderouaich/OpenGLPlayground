-- https://github.com/g-truc/glm/releases/tag/0.9.9.8
project "glm"
	kind "StaticLib"
	language "C++"
	cppdialect "C++latest" -- C++20
	staticruntime "On"

	targetdir ("Bin/" .. outputdir .. "/%{prj.name}")
	objdir ("Bin-Intermediate/" .. outputdir .. "/%{prj.name}")

    warnings "Off" -- turn Off warnings for this library

    includedirs
    {
    	"include/",
    }

	files
	{
		"**.hpp",
		"src/glm.cpp" -- to compile as static lib
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
		disablewarnings{
			"4201"
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