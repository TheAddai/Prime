
project "editor"
    language "C++"
    kind "ConsoleApp"

    targetdir(targetDir)
    objdir(objDir)

    files
    {
        "editor.lua",
        "src/**.h",
        "src/**.cpp"
    }

    includedirs 
    {
        "src",
        "%{includeDirs.engine}",
    }

    externalincludedirs
    {
        "%{includeDirs.spdlog}",
        "%{includeDirs.entt}",
        "%{includeDirs.glm}",
        "%{includeDirs.imgui}",
        "%{includeDirs.glfw}",
        "%{includeDirs.glad}"
    }

    links
    {
        "engine",
        "imgui"
    }