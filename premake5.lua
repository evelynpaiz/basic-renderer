-- premake5.lua

-- Solution
workspace "basic-renderer"
    architecture "x64"
    startproject "Renderer"
    configurations { "Debug", "Release" }

-- Directories
outputdir = "%{cfg.buildcfg}"

-- Project
project "Renderer"
    location "Renderer"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
    staticruntime "off"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files { 
        "%{prj.name}/include/**.h",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/resource/shader/**.glsl"}

    includedirs { 
        "%{prj.name}/include", "3rdparty/include",  
        "/usr/local/Cellar/glfw/3.3.8/include", "/usr/local/Cellar/glew/2.2.0_1/include"}

    libdirs {
        "/usr/local/Cellar/glfw/3.3.8/lib",
        "/usr/local/Cellar/glew/2.2.0_1/lib",
    }

    links {
        "OpenGL.framework", 
        "libglfw.3.3.dylib",
        "libGLEW.2.2.0.dylib"
    }

    -- mac specific settings
    filter "action:xcode4"
        sysincludedirs { 
            "3rdparty/include", "/usr/local/Cellar/glfw/3.3.8/include",
            "/usr/local/Cellar/glew/2.2.0_1/include"
        }

        xcodebuildsettings {
            ["PRODUCT_BUNDLE_IDENTIFIER"] = 'com.epaiz.basic-renderer'
        }

    -- windows specific settings
    filter "system:windows"
        systemversion "latest"

    -- debug configuration settings
    filter "configurations:Debug"
        defines { "DEBUG" }
        runtime "Debug"
        symbols "On"

    -- release configuration settings
    filter "configurations:Release"
        defines { "NDEBUG" }
        runtime "Release"
        optimize "On"
