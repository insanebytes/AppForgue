include "dependencies.lua"

workspace "AppForgue"
    architecture "x86_64"
    startproject "TestApp"
    configurations
    {
        "Debug",
        "Release"
    }

    flags
    {
 	"MultiProcessorCompile"
    }

outputdir="%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

group "Dependencies"
	include "AppForgue/vendor/glfw"
    include "AppForgue/vendor/glad"
	include "AppForgue/vendor/imgui"
group ""

group "AppForgue"
    include "AppForgue"
group ""

group "TestApp"
    include "TestApp"
group ""