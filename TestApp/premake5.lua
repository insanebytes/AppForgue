project "TestApp"
    kind "ConsoleApp"
    language "C++"
	cppdialect "C++20"
	staticruntime "off"

    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

    files
	{
		"src/**.h",
		"src/**.cpp"
	}

    defines
    {
		"APPFORGUE_INCLUDE_NONE"
    }

    includedirs
	{
		"%{wks.location}/AppForgue/"
	}

    links
	{
		"AppForgue"
	}

filter "system:windows"
		kind "WindowedApp"
		systemversion "latest"
		defines {"PLATFORM_WINDOWS"}

filter "configurations:Debug"
        defines "DEBUG"
		runtime "Debug"
		symbols "on"

filter "configurations:Release"
		defines "NDEBUG"
		runtime "Release"
		optimize "on"
		symbols "off"