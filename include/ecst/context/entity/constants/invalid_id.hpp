// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <limits>
#include <ecst/config.hpp>
#include <ecst/aliases.hpp>
#include <ecst/context/types.hpp>

ECST_CONTEXT_ENTITY_NAMESPACE
{
    namespace impl
    {
        // TODO: generalize
        using underlying_entity_id = typename entity_id::underlying_type;

        /// @brief Invalid entity ID used for invalid handles.
        constexpr auto invalid_id =
            std::numeric_limits<underlying_entity_id>::max();
    }

    /// @brief Returns `true` if `eid` is a valid entity ID.
    auto ECST_CONST_FN valid(entity_id eid) noexcept
    {
        return eid != impl::invalid_id;
    }
}
ECST_CONTEXT_ENTITY_NAMESPACE_END