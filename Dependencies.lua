-- Hazel Dependencies

VULKAN_SDK = os.getenv("VULKAN_SDK")

IncludeDir = {}
IncludeDir["stb_image"] = "%{wks.location}/Hazel/vender/stb_image"
IncludeDir["yaml_cpp"] = "%{wks.location}/Hazel/vender/yaml-cpp/include"
IncludeDir["Box2D"] = "%{wks.location}/Hazel/vender/Box2D/include"
IncludeDir["filewatch"] = "%{wks.location}/Hazel/vender/filewatch"
IncludeDir["GLFW"] = "%{wks.location}/Hazel/vender/GLFW/include"
IncludeDir["Glad"] = "%{wks.location}/Hazel/vender/Glad/include"
IncludeDir["ImGui"] = "%{wks.location}/Hazel/vender/ImGui"
IncludeDir["ImGuizmo"] = "%{wks.location}/Hazel/vender/ImGuizmo"
IncludeDir["glm"] = "%{wks.location}/Hazel/vender/glm"
IncludeDir["entt"] = "%{wks.location}/Hazel/vender/entt/include"
IncludeDir["mono"] = "%{wks.location}/Hazel/vender/mono/include"
IncludeDir["shaderc"] = "%{wks.location}/Hazel/vender/shaderc/include"
IncludeDir["SPIRV_Cross"] = "%{wks.location}/Hazel/vender/SPIRV-Cross"
IncludeDir["VulkanSDK"] = "%{VULKAN_SDK}/Include"
IncludeDir["msdfgen"] = "%{wks.location}/Hazel/vender/msdf-atlas-gen/msdfgen"
IncludeDir["msdf_atlas_gen"] = "%{wks.location}/Hazel/vender/msdf-atlas-gen/msdf-atlas-gen"

LibraryDir = {}

LibraryDir["VulkanSDK"] = "%{VULKAN_SDK}/Lib"
LibraryDir["mono"] = "%{wks.location}/Hazel/vender/mono/lib/%{cfg.buildcfg}"

Library = {}
Library["mono"] = "%{LibraryDir.mono}/libmono-static-sgen.lib"

Library["Vulkan"] = "%{LibraryDir.VulkanSDK}/vulkan-1.lib"
Library["VulkanUtils"] = "%{LibraryDir.VulkanSDK}/VkLayer_utils.lib"

Library["ShaderC_Debug"] = "%{LibraryDir.VulkanSDK}/shaderc_sharedd.lib"
Library["SPIRV_Cross_Debug"] = "%{LibraryDir.VulkanSDK}/spirv-cross-cored.lib"
Library["SPIRV_Cross_GLSL_Debug"] = "%{LibraryDir.VulkanSDK}/spirv-cross-glsld.lib"
Library["SPIRV_Tools_Debug"] = "%{LibraryDir.VulkanSDK}/SPIRV-Toolsd.lib"

Library["ShaderC_Release"] = "%{LibraryDir.VulkanSDK}/shaderc_shared.lib"
Library["SPIRV_Cross_Release"] = "%{LibraryDir.VulkanSDK}/spirv-cross-core.lib"
Library["SPIRV_Cross_GLSL_Release"] = "%{LibraryDir.VulkanSDK}/spirv-cross-glsl.lib"

-- Windows
Library["WinSock"] = "Ws2_32.lib"
Library["WinMM"] = "Winmm.lib"
Library["WinVersion"] = "Version.lib"
Library["BCrypt"] = "Bcrypt.lib"