
workspace "arbrook"
    location("build/" .. _ACTION)
    configurations { "Debug", "Development", "Release" }

os.chdir(_MAIN_SCRIPT_DIR)

local a = require("premake/rythe-build-system/rythe")

a.configure()