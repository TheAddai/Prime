
project "engine"
    language "C++"
    kind "StaticLib"

    targetdir(targetDir)
    objdir(objDir)

    pchheader "pch.h"
    pchsource "src/pch.cpp"

    files
    {
        "engine.lua",
        "src/**.h",
        "src/**.cpp"
    }

    includedirs 
    {
        "src"
    }

    externalincludedirs
    {
        "%{includeDirs.spdlog}",
        "%{includeDirs.entt}",
        "%{includeDirs.glfw}",
        "%{includeDirs.glad}",
        "%{includeDirs.glm}",
        "%{includeDirs.stb}"
    }

    links
    {
        "glfw",
        "glad"
    }

    filter {"system:windows", "configurations:*"}
        defines
        {
            "GLFW_INCLUDE_NONE"
        }