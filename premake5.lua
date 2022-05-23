outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Brio/vendor/GLFW/include"
IncludeDir["Glad"] = "Brio/vendor/Glad/include"
IncludeDir["ImGui"] = "Brio/vendor/imgui"
IncludeDir["glm"] = "Brio/vendor/glm"
IncludeDir["stb_image"] = "Brio/vendor/stb_image"
IncludeDir["ASSIMP"] = "Brio/vendor/ASSIMP"

workspace "Brio"
    architecture "x64"
    startproject "Sandbox"

    configurations 
    {
        "Debug",
        "Release",
        "Dist"
    }


include "Brio/vendor/GLFW"
include "Brio/vendor/Glad"
include "Brio/vendor/ImGui"

project "Brio"
    location "Brio"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin/int/" .. outputdir .. "/%{prj.name}")

    pchheader "brpch.h"
    pchsource "Brio/src/brpch.cpp"

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/vendor/glm/glm/**.hpp",
        "%{prj.name}/vendor/glm/glm/**.inl",
        "%{prj.name}/vendor/stb_image/**.cpp",
        "%{prj.name}/vendor/stb_image/**.h"
    }

    defines
    {
        "_CRT_SECURE_NO_WARNINGS",
        "GLFW_INCLUDE_NONE"
    }

    includedirs
    {
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.glm}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.stb_image}",
        "%{IncludeDir.ImGui}",
        "%{IncludeDir.ASSIMP}/include"
    }

    libdirs
    {
        "%{IncludeDir.ASSIMP}/lib"
    }

    links 
    {
        "GLFW",
        "Glad",
        "ImGui",
        "opengl32.lib",
        "assimp-vc142-mtd.lib"
    }

    filter "system:windows"
        systemversion "latest"

        defines
        {
            "BR_PLATFORM_WINDOWS"
        }
    
    filter "configurations:Debug"
        defines "BR_DEBUG"
        runtime "Debug"
        symbols "on"

        defines 
        {
            "BR_ENABLE_ASSERTS"
        }

    filter "configurations:Release"
        defines "BR_RELEASE"
        runtime "Release"
        optimize "on"

    filter "configurations:Dist"
        defines "BR_DIST"
        runtime "Release"
        optimize "on"



project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin/int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "Brio/vendor/spdlog/include",
        "%{IncludeDir.glm}",
        "Brio/vendor/Glad/include",
        "Brio/src",
        "Brio/vendor",
        "%{IncludeDir.ASSIMP}/include"
    }

    libdirs
    {
        "%{IncludeDir.ASSIMP}/lib"
    }

    links
    {
        "Brio"
    }
    
    postbuildcommands
    {
        "{COPY} ../Brio/vendor/ASSIMP/lib/assimp-vc143-mtd.dll %{cfg.targetdir}",
        "{COPY} ../Sandbox/assets %{cfg.targetdir}/assets",
    }
    
    filter "system:windows"
        systemversion "latest"

        defines
        {
            "BR_PLATFORM_WINDOWS"
        }
    
    filter "configurations:Debug"
        defines "BR_DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "BR_RELEASE"
        runtime "Release"
        optimize "on"

    filter "configurations:Dist"
        defines "BR_DIST"
        runtime "Release"
        optimize "on"
