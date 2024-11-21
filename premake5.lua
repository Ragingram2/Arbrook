
workspace "arbrook"
    -- location("build/" .. _ACTION)
    configurations { "Debug", "Development", "Release" }

os.chdir(_MAIN_SCRIPT_DIR)

local a = require("premake/rythe-build-system/rythe")

-- proof of concept for global depenencies..... needs work
-- local projects = dofile("premake/rythe-build-system/projects.lua")
-- projects.loadProject("third_party/tracy", { name = "tracy", group = "third_party", location = "libraries/third_party/tracy", src = "premake5.lua" },"libraries/third_party/tracy", "tracy", "library")

a.configure()