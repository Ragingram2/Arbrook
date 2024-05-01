#include "core/ecs/entity.hpp"
#include "core/ecs/entity_data.hpp"
#include "core/ecs/registry.hpp"
namespace rythe::core::ecs
{
	entity::operator rsl::id_type() const noexcept
	{
		return (data && data->alive) ? data->id : invalid_id;
	}

	entity_data* entity::operator->() noexcept
	{
		return data;
	}

	const entity_data* entity::operator->() const noexcept
	{
		return data;
	}

	//entity& entity::operator=(const entity& other) {
	//    data->id = other->id;
	//    data->name = other->name;
	//    return *this;
	//}

	struct child_iterator::impl
	{
		entity_set::iterator iterator;

		impl(entity_set::iterator it) : iterator(it) {}
	};

	child_iterator::child_iterator(impl* implptr) : m_pimpl(implptr) {}

	struct const_child_iterator::impl
	{
		entity_set::const_iterator iterator;

		impl(entity_set::const_iterator it) : iterator(it) {}
	};

	const_child_iterator::const_child_iterator(impl* implptr) : m_pimpl(implptr) {}

	struct child_reverse_iterator::impl
	{
		entity_set::reverse_iterator iterator;

		impl(entity_set::reverse_iterator it) : iterator(it) {}
	};

	child_reverse_iterator::child_reverse_iterator(impl* implptr) : m_pimpl(implptr) {}

	struct const_child_reverse_iterator::impl
	{
		entity_set::const_reverse_iterator iterator;

		impl(entity_set::const_reverse_iterator it) : iterator(it) {}
	};

	const_child_reverse_iterator::const_child_reverse_iterator(impl* implptr) : m_pimpl(implptr) {}

	bool operator==(const child_iterator& lhs, const child_iterator& rhs)
	{
		return lhs.m_pimpl->iterator == rhs.m_pimpl->iterator;
	}

	entity& child_iterator::operator*()
	{
		return *m_pimpl->iterator;
	}

	entity* child_iterator::operator->()
	{
		return &*m_pimpl->iterator;
	}

	child_iterator& child_iterator::operator++()
	{
		++m_pimpl->iterator;
		return *this;
	}

	child_iterator& child_iterator::operator--()
	{
		--m_pimpl->iterator;
		return *this;
	}

	child_iterator child_iterator::operator++(int)
	{
		impl* prev = new impl(m_pimpl->iterator);

		m_pimpl->iterator++;

		return child_iterator(prev);
	}

	child_iterator child_iterator::operator--(int)
	{
		impl* prev = new impl(m_pimpl->iterator);

		m_pimpl->iterator--;

		return child_iterator(prev);
	}

	bool operator==(const const_child_iterator& lhs, const const_child_iterator& rhs)
	{
		return lhs.m_pimpl->iterator == rhs.m_pimpl->iterator;
	}

	const entity& const_child_iterator::operator*()
	{
		return *m_pimpl->iterator;
	}

	const entity* const_child_iterator::operator->()
	{
		return &*m_pimpl->iterator;
	}

	const_child_iterator& const_child_iterator::operator++()
	{
		++m_pimpl->iterator;
		return *this;
	}

	const_child_iterator& const_child_iterator::operator--()
	{
		--m_pimpl->iterator;
		return *this;
	}

	const_child_iterator const_child_iterator::operator++(int)
	{
		impl* prev = new impl(m_pimpl->iterator);

		m_pimpl->iterator++;

		return const_child_iterator(prev);
	}

	const_child_iterator const_child_iterator::operator--(int)
	{
		impl* prev = new impl(m_pimpl->iterator);

		m_pimpl->iterator--;

		return const_child_iterator(prev);
	}

	bool operator==(const child_reverse_iterator& lhs, const child_reverse_iterator& rhs)
	{
		return lhs.m_pimpl->iterator == rhs.m_pimpl->iterator;
	}

	entity& child_reverse_iterator::operator*()
	{
		return *m_pimpl->iterator;
	}

	entity* child_reverse_iterator::operator->()
	{
		return &*m_pimpl->iterator;
	}

	child_reverse_iterator& child_reverse_iterator::operator++()
	{
		++m_pimpl->iterator;
		return *this;
	}

	child_reverse_iterator& child_reverse_iterator::operator--()
	{
		--m_pimpl->iterator;
		return *this;
	}

	child_reverse_iterator child_reverse_iterator::operator++(int)
	{
		impl* prev = new impl(m_pimpl->iterator);

		m_pimpl->iterator++;

		return child_reverse_iterator(prev);
	}

	child_reverse_iterator child_reverse_iterator::operator--(int)
	{
		impl* prev = new impl(m_pimpl->iterator);

		m_pimpl->iterator--;

		return child_reverse_iterator(prev);
	}

	bool operator==(const const_child_reverse_iterator& lhs, const const_child_reverse_iterator& rhs)
	{
		return lhs.m_pimpl->iterator == rhs.m_pimpl->iterator;
	}

	const entity& const_child_reverse_iterator::operator*()
	{
		return *m_pimpl->iterator;
	}

	const entity* const_child_reverse_iterator::operator->()
	{
		return &*m_pimpl->iterator;
	}

	const_child_reverse_iterator& const_child_reverse_iterator::operator++()
	{
		++m_pimpl->iterator;
		return *this;
	}

	const_child_reverse_iterator& const_child_reverse_iterator::operator--()
	{
		--m_pimpl->iterator;
		return *this;
	}

	const_child_reverse_iterator const_child_reverse_iterator::operator++(int)
	{
		impl* prev = new impl(m_pimpl->iterator);

		m_pimpl->iterator++;

		return const_child_reverse_iterator(prev);
	}

	const_child_reverse_iterator const_child_reverse_iterator::operator--(int)
	{
		impl* prev = new impl(m_pimpl->iterator);

		m_pimpl->iterator--;

		return const_child_reverse_iterator(prev);
	}

	/* child_iterator entity::begin()
   {
	   return child_iterator(new child_iterator::impl(children.begin()));
   }

   const_child_iterator entity::begin() const
   {
	   return const_child_iterator(new const_child_iterator::impl(children.cbegin()));
   }

   const_child_iterator entity::cbegin() const
   {
	   return const_child_iterator(new const_child_iterator::impl(children.cbegin()));
   }

   child_reverse_iterator entity::rbegin()
   {
	   return child_reverse_iterator(new child_reverse_iterator::impl(children.rbegin()));
   }

   const_child_reverse_iterator entity::rbegin() const
   {
	   return const_child_reverse_iterator(new const_child_reverse_iterator::impl(children.crbegin()));
   }

   const_child_reverse_iterator entity::crbegin() const
   {
	   return const_child_reverse_iterator(new const_child_reverse_iterator::impl(children.crbegin()));
   }

   child_iterator entity::end()
   {
	   return child_iterator(new child_iterator::impl(children.end()));
   }

   const_child_iterator entity::end() const
   {
	   return const_child_iterator(new const_child_iterator::impl(children.cend()));
   }

   const_child_iterator entity::cend() const
   {
	   return const_child_iterator(new const_child_iterator::impl(children.cend()));
   }

   child_reverse_iterator entity::rend()
   {
	   return child_reverse_iterator(new child_reverse_iterator::impl(children.rend()));
   }

   const_child_reverse_iterator entity::rend() const
   {
	   return const_child_reverse_iterator(new const_child_reverse_iterator::impl(children.crend()));
   }

   const_child_reverse_iterator entity::crend() const
   {
	   return const_child_reverse_iterator(new const_child_reverse_iterator::impl(children.crend()));
   }*/

	void entity::addComponent(rsl::id_type compId)
	{
		return Registry::createComponent(data->id, compId);
	}

	bool entity::hasComponent(rsl::id_type compId)
	{
		return Registry::hasComponent(data->id, compId);
	}
}