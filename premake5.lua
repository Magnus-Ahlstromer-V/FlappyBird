workspace "Workspace"
    architecture "x64"
    configurations { "Debug", "Release" }
    platforms { "Windows", "Linux" }

outputdir = "%{cfg.buildcfg}-%{cfg.system}"

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

    filter { "platforms:Windows" }
        system "Windows"
        includedirs { "vendor/Windows/SDL2/include", "%{prj.name}/source" }
        libdirs { "vendor/Windows/SDL2/lib" }
        links { "mingw32", "SDL2main", "SDL2", "SDL2_image", "SDL2_ttf" }

    filter { "platforms:Linux" }
        system "Linux"
        includedirs { "%{prj.name}/source" }
        links { "SDL2main", "SDL2", "SDL2_image", "SDL2_ttf" }

    filter "configurations:Debug"
        symbols "on"
        defines { "DEBUG" }

    filter "configurations:Release"
        optimize "on"
        defines { "RELEASE" }
