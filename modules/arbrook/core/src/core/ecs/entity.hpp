#pragma once
#include <format>
#include <unordered_map>
#include <unordered_set>

#include <rsl/primitives>
#include <rsl/hash>
#include <rsl/containers>

#include "core/containers/pointer.hpp"

namespace rythe::core::ecs
{
    struct entity;
}

namespace std
{
	template<> struct hash<rythe::core::ecs::entity>
	{
		std::size_t operator()(rythe::core::ecs::entity const& handle) const noexcept;
	};
}

namespace rythe::core::ecs
{
	struct entity_data;
	using entity_set = rsl::hashed_sparse_set<entity>;

    struct child_iterator
    {
        friend struct entity;
    private:
        struct impl;

        std::shared_ptr<impl> m_pimpl;
        child_iterator(impl* implptr);

    public:

        friend bool operator==(const child_iterator& lhs, const child_iterator& rhs);

        friend bool operator!=(const child_iterator& lhs, const child_iterator& rhs) { return !(lhs == rhs); }

        entity& operator*();

        entity* operator->();

        child_iterator& operator++();
        child_iterator& operator--();
        child_iterator operator++(int);
        child_iterator operator--(int);

    };

    struct const_child_iterator
    {
        friend struct entity;
    private:
        struct impl;

        std::shared_ptr<impl> m_pimpl;
        const_child_iterator(impl* implptr);

    public:

        friend bool operator==(const const_child_iterator& lhs, const const_child_iterator& rhs);

        friend bool operator!=(const const_child_iterator& lhs, const const_child_iterator& rhs) { return !(lhs == rhs); }

        const entity& operator*();

        const entity* operator->();

        const_child_iterator& operator++();
        const_child_iterator& operator--();
        const_child_iterator operator++(int);
        const_child_iterator operator--(int);

    };

    struct child_reverse_iterator
    {
        friend struct entity;
    private:
        struct impl;

        std::shared_ptr<impl> m_pimpl;
        child_reverse_iterator(impl* implptr);

    public:

        friend bool operator==(const child_reverse_iterator& lhs, const child_reverse_iterator& rhs);

        friend bool operator!=(const child_reverse_iterator& lhs, const child_reverse_iterator& rhs) { return !(lhs == rhs); }

        entity& operator*();

        entity* operator->();

        child_reverse_iterator& operator++();
        child_reverse_iterator& operator--();
        child_reverse_iterator operator++(int);
        child_reverse_iterator operator--(int);

    };

    struct const_child_reverse_iterator
    {
        friend struct entity;
    private:
        struct impl;

        std::shared_ptr<impl> m_pimpl;
        const_child_reverse_iterator(impl* implptr);

    public:

        friend bool operator==(const const_child_reverse_iterator& lhs, const const_child_reverse_iterator& rhs);

        friend bool operator!=(const const_child_reverse_iterator& lhs, const const_child_reverse_iterator& rhs) { return !(lhs == rhs); }

        const entity& operator*();

        const entity* operator->();

        const_child_reverse_iterator& operator++();
        const_child_reverse_iterator& operator--();
        const_child_reverse_iterator operator++(int);
        const_child_reverse_iterator operator--(int);

    };

    struct entity
    {
        entity_data* data;

        template<typename T>
        [[nodiscard]] bool operator==(T val) const;
        template<typename T>
        [[nodiscard]] bool operator!=(T val) const;

        [[nodiscard]] operator rsl::id_type () const noexcept;

        [[nodiscard]] entity_data* operator->() noexcept;
        [[nodiscard]] const entity_data* operator->() const noexcept;


		template<typename componentType>
		componentType& addComponent();

        template<typename componentType>
        componentType& addComponent(componentType&& value);

        template<typename componentType>
        componentType& addComponent(const componentType& value);

        void addComponent(rsl::id_type compId);

		template<typename componentType>
		componentType& getComponent();

		template<typename componentType>
		bool hasComponent();

        bool hasComponent(rsl::id_type compId);

		template<typename componentType>
		void destroyComponent();

       std::unordered_set<rsl::id_type>& component_composition();
       const std::unordered_set<rsl::id_type>& component_composition() const;

		///**@brief Gets iterator to the first child.
		// */
		//[[nodiscard]] child_iterator begin();
		//[[nodiscard]] const_child_iterator begin() const;
		//[[nodiscard]] const_child_iterator cbegin() const;

		///**@brief Gets reverse iterator to the last child.
		// */
		//[[nodiscard]] child_reverse_iterator rbegin();
		//[[nodiscard]] const_child_reverse_iterator rbegin() const;
		//[[nodiscard]] const_child_reverse_iterator crbegin() const;

		///**@brief Gets iterator to the last child.
		// */
		//[[nodiscard]] child_iterator end();
		//[[nodiscard]] const_child_iterator end() const;
		//[[nodiscard]] const_child_iterator cend() const;

		///**@brief Gets reverse iterator to the first child.
		// */
		//[[nodiscard]] child_reverse_iterator rend();
		//[[nodiscard]] const_child_reverse_iterator rend() const;
		//[[nodiscard]] const_child_reverse_iterator crend() const;


        //entity& operator=(const entity& other);
	};
}

#include "entity.inl"