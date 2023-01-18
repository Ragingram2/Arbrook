#pragma once
#include "events/event.hpp"

namespace rythe::core::events
{
    struct exit final : public event<exit>
    {
        const int exitcode;

        exit(int exitcode = 0) : exitcode(exitcode) {};
    };

}
