-- stb utils, image...
project "stb"
	kind "StaticLib"
	language "C"
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
		"src/stb.c", -- stb.c has available stb tools include with macro STB_IMAGE_STATIC if not defined, to compile as static lib
	}

	defines
	{
		"STB_IMAGE_STATIC",
		-- NOTE: you must define STB_IMAGE_IMPLEMENTATION before including stb_image in a source file
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