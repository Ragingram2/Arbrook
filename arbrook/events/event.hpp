#pragma once
#include <unordered_map>

#include "types/primitives.hpp"
#include "types/type_util.hpp"
#include "platform/platform.hpp"
#include "containers/delegate.hpp"

/**
 * @file event.hpp
 */

namespace rythe::core::events
{
    /**@class event_base
     * @brief Base class of all events for polymorphic storage.
     */
    struct event_base
    {
        virtual ~event_base() = default;

        /**@brief Get's the type id of an event. (only available in event_base)
         */
        virtual id_type get_id() RYTHE_PURE;
    };

    /**@class event
     * @brief Base class all user defined events should inherit from. This ensures that each event has it's type id and that it can statically be requested.
     */
    template<typename Self>
    struct event : public event_base
    {
        friend class EventBus;

        inline static const id_type id = typeHash<Self>();

        virtual ~event() = default;
    private:
        virtual id_type get_id()
        {
            return id;
        }
    };
}
