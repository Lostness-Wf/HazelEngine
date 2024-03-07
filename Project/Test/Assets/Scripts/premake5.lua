local HazelRootDir = os.getenv("HAZEL2D_DIR")

workspace "Test"
	architecture "x86_64"
	startproject "Test"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Test"
	kind "SharedLib"
	language "C#"
	dotnetframework "4.7.2"

	targetdir ("Binaries")
	objdir ("Intermediates")

	files 
	{
		"Source/**.cs",
		"Properties/**.cs"
	}

	links
	{
		"Hazel-ScriptCore"
	}

	filter "configurations:Debug"
		optimize "Off"
		symbols "Default"

	filter "configurations:Release"
		optimize "On"
		symbols "Default"

	filter "configurations:Dist"
		optimize "Full"
		symbols "Off"

group "Hazel"
	include (HazelRootDir .. "/Hazel-ScriptCore")
group ""