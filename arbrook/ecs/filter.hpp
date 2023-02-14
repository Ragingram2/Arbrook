#pragma once
#include <tuple>
#include <utility>
#include <algorithm>

#include <rythe/primitives>

#include "platform/platform.hpp"
#include "ecs/entity.hpp"
#include "ecs/component_container.hpp"
#include "ecs/component_family.hpp"

namespace rythe::core::ecs
{
	template<typename... componentTypes>
	struct filter
	{
		using types = std::tuple<componentTypes...>;
		std::unordered_map<rsl::id_type, ecs::entity> m_entities;

		std::tuple<ecs::component_container<componentTypes>...> m_containers;
		filter()
		{
			types t;
			std::apply([=]<typename... T>(T... args)
			{
				(
					(
						Program::Instance().m_registry->get_service<events::EventBus>()->bind<events::component_creation<decltype(args)>, filter<componentTypes...>, &filter<componentTypes...>::addEntity>(*this),
						Program::Instance().m_registry->get_service<events::EventBus>()->bind<events::component_destruction<decltype(args)>, filter<componentTypes...>, &filter<componentTypes...>::removeEntity>(*this)
						)
					, ...);
			}, t);
		}
	public:
		//R_NODISCARD entity_set::iterator begin() noexcept;
		//R_NODISCARD entity_set::iterator end() noexcept;
		//R_NODISCARD entity_set::reverse_iterator rbegin() noexcept;
		//R_NODISCARD entity_set::reverse_iterator rend() noexcept;
		////R_NODISCARD entity_set::reverse_itr_range reverse_range() noexcept;

		//R_NODISCARD rsl::size_type size() noexcept;
		//R_NODISCARD bool empty() noexcept;

		//R_NODISCARD rsl::size_type count(ecs::entity val);
		//R_NODISCARD rsl::size_type contains(ecs::entity val);

		//R_NODISCARD entity_set::iterator find(ecs::entity val);

		//R_NODISCARD ecs::entity& at(rsl::size_type index);
		//R_NODISCARD ecs::entity& operator[](rsl::size_type index);

		template<typename componentType>
		void addEntity(events::component_creation<componentType>& evnt);

		template<typename componentType>
		void removeEntity(events::component_destruction<componentType>& evnt);

		//template<typename componentType>
		//R_NODISCARD ecs::component_container<componentType>& get();
	};
}

#include "ecs/filter.inl"
