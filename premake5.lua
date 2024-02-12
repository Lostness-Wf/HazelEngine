include "./vender/premake/premake_customization/solution_items.lua"

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

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "%{wks.location}/Hazel/vender/GLFW/include"
IncludeDir["Glad"] = "%{wks.location}/Hazel/vender/Glad/include"
IncludeDir["ImGui"] = "%{wks.location}/Hazel/vender/imgui"
IncludeDir["glm"] = "%{wks.location}/Hazel/vender/glm"
IncludeDir["stb_image"] = "%{wks.location}/Hazel/vender/stb_image"
IncludeDir["entt"] = "%{wks.location}/Hazel/vender/entt/include"
IncludeDir["yaml_cpp"] = "%{wks.location}/Hazel/vender/yaml-cpp/include"
IncludeDir["ImGuizmo"] = "%{wks.location}/Hazel/vender/ImGuizmo"

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