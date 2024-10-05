#pragma once
#include <vector>
#include <functional>

namespace rythe::core::ecs
{
    template<typename componentType>
    using component_container = std::vector<std::reference_wrapper<componentType>>;
}
