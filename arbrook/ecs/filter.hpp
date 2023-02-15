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
	//using entity_set = std::unordered_map<rsl::id_type, ecs::entity>;
	using entity_set = std::vector<ecs::entity>;
	template<typename... componentTypes>
	struct filter
	{
		using types = std::tuple<componentTypes...>;
		entity_set m_entities;

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
		entity_set::iterator begin() noexcept;
		entity_set::iterator end() noexcept;
		entity_set::reverse_iterator rbegin() noexcept;
		entity_set::reverse_iterator rend() noexcept;
		//entity_set::reverse_itr_range reverse_range() noexcept;

		rsl::size_type size() noexcept;
		bool empty() noexcept;

		rsl::size_type count(ecs::entity val);
		bool contains(ecs::entity val);

		entity_set::iterator find(ecs::entity val);

		ecs::entity& at(rsl::size_type index);
		ecs::entity& operator[](rsl::size_type index);

		template<typename componentType>
		void addEntity(events::component_creation<componentType>& evnt);

		template<typename componentType>
		void removeEntity(events::component_destruction<componentType>& evnt);
	};
}

#include "ecs/filter.inl"
