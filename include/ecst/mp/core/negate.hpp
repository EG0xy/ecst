// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <ecst/config.hpp>
#include <ecst/mp/core/aliases.hpp>

ECST_MP_NAMESPACE
{
    /// @brief Returns a predicate which is the negation of `p`.
    template <typename TPredicate>
    constexpr auto negate(TPredicate p) noexcept
    {
        (void)p;

        return [=](auto... axs)
        {
            return bool_v<!(decltype(p(axs...)){})>;
        };
    }
}
ECST_MP_NAMESPACE_END