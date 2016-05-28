// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <type_traits>
#include <vrm/pp/cat.hpp>
#include <ecst/config.hpp>
#include <ecst/aliases.hpp>

ECST_NAMESPACE
{
    namespace impl
    {
        template <typename TF>
        struct scope_guard : public TF
        {
            template <typename TFFwd>
            scope_guard(TFFwd&& f)                                 // .
                noexcept(std::is_nothrow_move_constructible<TF>{}) // .
                : TF{FWD(f)}
            {
            }

            ~scope_guard() noexcept(                      // .
                noexcept(std::declval<TF>().operator()()) // .
                )

            {
                this->operator()();
            }
        };

        template <typename TF>
        auto make_scope_guard(TF&& f) // .
            noexcept(std::is_nothrow_move_constructible<TF>{})
        {
            return scope_guard<ECST_DECAY_DECLTYPE(f)>{std::move(f)};
        }
    }
}
ECST_NAMESPACE_END

// TODO: docs
#define ECST_SCOPE_GUARD(...)               \
    auto VRM_PP_CAT(scope_guard, __LINE__)( \
        ::ecst::impl::make_scope_guard(__VA_ARGS__))
