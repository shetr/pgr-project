
workspace "PGR"
    --location ("solutions/" .. _ACTION)
    configurations { "debug", "release" }
    cppdialect "C++17"

    targetdir "./"
    targetname ("%{cfg.buildcfg}-%{cfg.system}%{cfg.architecture}")
    objdir "obj/%{cfg.buildcfg}-%{cfg.system}%{cfg.architecture}/"

    includedirs "include"
    --libdirs "lib"

    filter "system:windows"
        defines { "PGR_WINDOWS", "WIN32" }

    filter "system:linux"
        defines { "PGR_LINUX" }
    filter {}

    filter "configurations:debug"
        defines { "PGR_DEBUG", "_DEBUG" }
        runtime "Debug"
        symbols "On"

    filter "configurations:release"
        defines { "PGR_RELEASE", "NDEBUG" }
        runtime "Release"
        optimize "On"
    filter {}


project("app")
    --location ("solutions/" .. _ACTION)
    kind "ConsoleApp"
    language "C++"
    files ("src/**")
    includedirs "src"
    --postbuildcommands { "{COPY} ../../res %{cfg.targetdir}/"}
    --libdirs "lib"
    filter "system:windows"
        links { "freeglut", "assimp", "DevIL", "AntTweakBar", "zlib" }
    filter "system:linux"
        links { "glut", "assimp", "IL", "AntTweakBar", "z", "GLEW", "X11", "dl", "pthread", "GLX" }
    filter {}



