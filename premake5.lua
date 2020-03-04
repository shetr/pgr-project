
workspace "pgr-project"
    configurations { "debug", "release" }
    cppdialect "C++17"

    targetdir "app/"
    debugdir "app/" 
    targetname ("%{cfg.buildcfg}-%{cfg.system}%{cfg.architecture}")
    objdir "obj/%{cfg.buildcfg}-%{cfg.system}%{cfg.architecture}/"
       
    includedirs "include"

    filter "system:windows"
        defines { "PGR_WINDOWS", "WIN32" }
        libdirs "lib"

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
    kind "ConsoleApp"
    language "C++"
    files ("src/**", "app/res/**")
    includedirs "src"
    filter "system:windows"
        links { "freeglut", "assimp", "DevIL", "AntTweakBar", "zlibstatic", "IrrXML" }
    filter "system:linux"
        links { "glut", "assimp", "IL", "AntTweakBar", "z", "GLEW", "X11", "dl", "pthread", "GLX" }
    filter {}



