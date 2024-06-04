
targetDir = "%{wks.location}/bin/%{prj.name}"
objDir = "%{wks.location}/bin-int"

includeDirs = {}
includeDirs["engine"] = "%{wks.location}/engine/src"
includeDirs["spdlog"] = "%{wks.location}/vendor/spdlog/include"

workspace "prime"
    startproject "editor"

    configurations
    {
        "Debug",
        "Release"
    }

    flags 
    {
        "MultiProcessorCompile"
    }

    disablewarnings
    {

    }

    filter {"system:windows", "configurations:*"}
        architecture "x64"
        systemversion "latest"
        cppdialect "C++17"
        staticruntime "on"

    filter "configurations:Debug"
        symbols "on"
        runtime "Debug"

    filter "configurations:Release"
        symbols "off"
        runtime "Release"
        optimize "full"


    include "engine/engine.lua"
    include "editor/editor.lua"