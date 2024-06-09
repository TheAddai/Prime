
targetDir = "%{wks.location}/bin/%{prj.name}"
objDir = "%{wks.location}/bin-int"

includeDirs = {}
includeDirs["engine"] = "%{wks.location}/engine/src"
includeDirs["spdlog"] = "%{wks.location}/vendor/spdlog/include"
includeDirs["entt"] = "%{wks.location}/vendor/entt/include"
includeDirs["glfw"] = "%{wks.location}/vendor/glfw/include"
includeDirs["glad"] = "%{wks.location}/vendor/glad/include"
includeDirs["glm"] = "%{wks.location}/vendor/glm/include"
includeDirs["stb"] = "%{wks.location}/vendor/stb_image/include"
includeDirs["imgui"] = "%{wks.location}/vendor/imgui/include"

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

    externalwarnings "off"
    characterset "ASCII"

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


    group "core"
        include "engine/engine.lua"
        include "editor/editor.lua"
    group ""

    group "vendor"
        include "vendor/glfw/glfw.lua"
        include "vendor/glad/glad.lua"
        include "vendor/imgui/imgui.lua"
    group ""