#pragma once
#include <format>
#include <unordered_map>
#include <unordered_set>
#include <type_traits>

#include <rsl/primitives>
#include <rsl/hash>
#include <rsl/containers>

#include "core/containers/pointer.hpp"


namespace rythe::core::ecs
{
	struct entity_data;

	struct entity
	{
		entity_data* data;

		[[nodiscard]] operator rsl::id_type() const noexcept;

		[[nodiscard]] entity_data* operator->() noexcept;
		[[nodiscard]] const entity_data* operator->() const noexcept;

		template<typename T>
		[[rythe_always_inline]] bool operator==(T val) const;

		template<typename T>
		[[rythe_always_inline]] bool operator!=(T val) const;

		void addComponent(rsl::id_type compId);

		bool hasComponent(rsl::id_type compId);

		std::unordered_set<rsl::id_type>& component_composition();
		const std::unordered_set<rsl::id_type>& component_composition() const;

		template<typename componentType>
		componentType& addComponent();

		template<typename componentType>
		componentType& addComponent(const componentType& value);

		template<typename componentType>
		componentType& addComponent(componentType&& value);

		template<typename componentType>
		componentType& getComponent();

		template<typename componentType>
		bool hasComponent();

		template<typename componentType>
		void destroyComponent();
	};

	using entity_set = rsl::hashed_sparse_set<entity>;
}

namespace std
{
	template <>
	struct hash<rythe::core::ecs::entity>
	{
		size_t operator()(const rythe::core::ecs::entity& handle) const noexcept;

	};
}

namespace rythe::core::ecs
{
	struct entity_data
	{
		rsl::id_type id = 0;
		std::string name = "";
		bool alive = true;
		bool enabled = true;
		entity parent = { nullptr };
		rsl::hashed_sparse_set<entity> children;
	};

	inline entity_data* entity::operator->() noexcept { return data; }
	inline const entity_data* entity::operator->() const noexcept { return data; }
}

namespace std
{
	inline size_t hash<rythe::core::ecs::entity>::operator()(const rythe::core::ecs::entity& handle) const noexcept
	{
		return handle.data != nullptr ? handle.data->id : invalid_id;
	}
}

namespace rythe::core::ecs
{

	template<typename T>
	[[rythe_always_inline]] inline bool entity::operator==(T val) const
	{
		return data && data->alive ? data->id == val : val == invalid_id;
	}

	template<typename T>
	[[rythe_always_inline]] inline bool entity::operator!=(T val) const
	{
		return data && data->alive && (data->id != val || val == invalid_id);
	}
	template<>
	[[rythe_always_inline]] inline bool entity::operator==<std::nullptr_t>(std::nullptr_t) const
	{
		return !(data && data->alive);
	}

	template<>
	[[rythe_always_inline]] inline bool entity::operator!=<std::nullptr_t>(std::nullptr_t) const
	{
		return data && data->alive;
	}

	template<>
	[[rythe_always_inline]] inline  bool entity::operator==<rsl::id_type>(rsl::id_type id) const
	{
		return data && data->alive ? data->id == id : id == invalid_id;
	}

	template<>
	[[rythe_always_inline]] inline bool entity::operator!=<rsl::id_type>(rsl::id_type id) const
	{
		return data && data->alive && (data->id != id || id == invalid_id);
	}

	template<>
	[[rythe_always_inline]] inline bool entity::operator==<entity>(entity other) const
	{
		return data && data->alive && other && data->id == other.data->id;
	}

	template<>
	[[rythe_always_inline]] inline bool entity::operator!=<entity>(entity other) const
	{
		return data && data->alive && other && data->id != other.data->id;
	}

	template<>
	[[rythe_always_inline]] inline bool entity::operator==<entity_data>(entity_data other) const
	{
		return data && data->alive && data->id == other.id;
	}

	template<>
	[[rythe_always_inline]] inline bool entity::operator!=<entity_data>(entity_data other) const
	{
		return data && data->alive && data->id != other.id;
	}
}


