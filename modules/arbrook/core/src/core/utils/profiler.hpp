#pragma once

#ifdef _DEBUG
#undef TRACY_ENABLE
#else
#undef TRACY_ENABLE
#endif

#include <public/tracy/Tracy.hpp>