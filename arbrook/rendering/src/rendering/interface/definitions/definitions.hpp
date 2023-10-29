#pragma once
#include "rendering/interface/definitions/renderinterface.hpp"
#include "rendering/interface/definitions/inputlayout.hpp"
#include "rendering/interface/definitions/shader.hpp"
#include "rendering/interface/definitions/buffer.hpp"
#include "rendering/interface/definitions/texture.hpp"
#include "rendering/interface/definitions/window.hpp"
#include "rendering/interface/config.hpp"
#include EnumTypes_HPP_PATH

#define Screen_Width 1280.f
#define Screen_Height 720.f

#define CLEAR_PRIORITY 0x0000
#define OPAQUE_PRIORITY 0x0001
#define TRANSPARENT_PRIORITY 0x0002
#define POST_FX_PRIORITY 0x0003
#define UI_PRIORITY 0x0004
