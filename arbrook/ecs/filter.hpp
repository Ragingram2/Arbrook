#pragma once

#include <rythe/primitives>

#include "platform/platform.hpp"
#include "ecs/entity.hpp"
#include "ecs/component_container.hpp"
#include "ecs/component_family.hpp"

namespace rythe::core::ecs
{
	using entity_set = std::vector<ecs::entity>;

	template<typename... componentTypes>
	struct filter
	{
	private:
		std::tuple<ecs::component_container<componentTypes>...> m_containers;
	public:
		R_NODISCARD entity_set::iterator begin() noexcept;
		R_NODISCARD entity_set::iterator end() noexcept;
		R_NODISCARD entity_set::reverse_iterator rbegin() noexcept;
		R_NODISCARD entity_set::reverse_iterator rend() noexcept;
		//R_NODISCARD entity_set::reverse_itr_range reverse_range() noexcept;

		R_NODISCARD rsl::size_type size() noexcept;
		R_NODISCARD bool empty() noexcept;

		R_NODISCARD rsl::size_type count(ecs::entity val);
		R_NODISCARD rsl::size_type contains(ecs::entity val);

		R_NODISCARD entity_set::iterator find(ecs::entity val);

		R_NODISCARD ecs::entity& at(rsl::size_type index);
		R_NODISCARD ecs::entity& operator[](rsl::size_type index);

		template<typename componentType>
		R_NODISCARD ecs::component_container<componentType>& get();
	};
}

#include "ecs/filter.inl"
