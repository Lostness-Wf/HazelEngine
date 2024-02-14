include "./vender/premake/premake_customization/solution_items.lua"
include "Dependencies.lua"

workspace "Hazel"
	architecture "x86_64"
	startproject "Hazel-Editor"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	solution_items
	{
		".editorconfig"
	}

	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

group "Dependencies"
	include "vender/premake"
	include "Hazel/vender/GLFW"
	include "Hazel/vender/Glad"
	include "Hazel/vender/imgui"
	include "Hazel/vender/yaml-cpp"
group ""

include "Hazel"
include "Sandbox"
include "Hazel-Editor"