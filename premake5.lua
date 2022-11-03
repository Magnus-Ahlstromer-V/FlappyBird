workspace "Workspace"
    architecture "x64"
    configurations { "Debug", "Release" }

outputdir = "%{cfg.buildcfg}"

project "Game"
    location "Game"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++14"
    staticruntime "on"

    targetdir("bin/" .. outputdir)
    objdir("bin-int/" .. outputdir)

    files
    {
        "%{prj.name}/source/**.h",
        "%{prj.name}/source/**.cpp"
    }

    includedirs
    {
        "%{prj.name}/source"
    }

    links { "SDL2main", "SDL2", "SDL2_image", "SDL2_ttf" }

    filter "configurations:Debug"
        symbols "on"
        defines { "DEBUG" }

    filter "configurations:Release"
        optimize "on"
        defines { "RELEASE" }
