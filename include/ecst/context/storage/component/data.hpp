// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <type_traits>
#include <ecst/config.hpp>
#include <ecst/aliases.hpp>
#include <ecst/mp/list.hpp>
#include <ecst/settings.hpp>
#include "./chunk.hpp"

ECST_CONTEXT_STORAGE_COMPONENT_NAMESPACE
{
    namespace impl
    {
        template <typename TSettings>
        class data
        {
        public:
            using chunk_tuple = chunk_tuple_type<TSettings>;
            using chunk_metadata_tuple = chunk_metadata_tuple_type<TSettings>;

        private:
            chunk_tuple _chunk_tuple;

            /// @brief Returns a chunk by chunk ID.
            template <typename TID>
            auto& chunk_by_id(TID) noexcept
            {
                return bh::at(_chunk_tuple, TID{});
            }

            /// @brief Returns the chunk storing `TComponent`.
            template <typename TComponent>
            auto& chunk_for() noexcept
            {
                constexpr auto csl =
                    settings::component_signature_list(TSettings{});

                constexpr auto id =
                    signature_list::component::id_by_type<TComponent>(csl);

                auto& chunk = chunk_by_id(id);

                using component = chunk::component<ECST_DECAY_DECLTYPE(chunk)>;

                ECST_S_ASSERT(std::is_same<component, TComponent>{});

                return chunk;
            }

            /// @brief Executes `f` on the chunk storing `TComponent`.
            template <typename TComponent, typename TSelf,
                typename TEntityChunkMetadata, typename TF>
            decltype(auto) chunk_fn_impl(
                TSelf&& self, entity_id eid, TEntityChunkMetadata& ecm, TF&& f)
            {
                decltype(auto) c(self.template chunk_for<TComponent>());
                using metadata = chunk::metadata<ECST_DECAY_DECLTYPE(c)>;

                auto& chunk_md = std::get<metadata>(ecm);
                return f(c, eid, chunk_md);
            }

            template <typename TComponent, typename TSelf,
                typename TEntityChunkMetadata>
            decltype(auto) get_impl(
                TSelf&& self, entity_id eid, const TEntityChunkMetadata& ecm)
            {
                return chunk_fn_impl<TComponent>(FWD(self), eid, ecm,
                    [](auto& xc, auto x_eid, const auto& x_md) -> decltype(auto)
                    {
                        return xc.get(x_eid, x_md);
                    });
            }

            template <typename TComponent, typename TSelf,
                typename TEntityChunkMetadata>
            decltype(auto) add_impl(
                TSelf&& self, entity_id eid, TEntityChunkMetadata& ecm)
            {
                ELOG(                                                    // .
                    debug::lo_component() << "Creating for eID: " << eid // .
                                          << "\n";                       // .
                    );

                return chunk_fn_impl<TComponent>(FWD(self), eid, ecm,
                    [](auto& zc, auto z_eid, auto& z_md) -> decltype(auto)
                    {
                        return zc.add(z_eid, z_md);
                    });
            }

        public:
            /// @brief Given an "entity id" and an "entity chunk metadata",
            /// return a reference to a component.
            template <typename TComponent, typename... Ts>
                auto& get(Ts&&... xs) & noexcept
            {
                return get_impl<TComponent>(*this, FWD(xs)...);
            }

            /// @brief Given an "entity id" and an "entity chunk metadata",
            /// return a const reference to a component.
            template <typename TComponent, typename... Ts>
            const auto& get(Ts&&... xs) const& noexcept
            {
                return get_impl<TComponent>(*this, FWD(xs)...);
            }

            /// @brief Given an "entity id" and an "entity chunk metadata",
            /// creates a component and returns a reference to it.
            template <typename TComponent, typename... Ts>
                decltype(auto) add(Ts&&... xs) & noexcept
            {
                return add_impl<TComponent>(*this, FWD(xs)...);
            }
        };
    }
}
ECST_CONTEXT_STORAGE_COMPONENT_NAMESPACE_END
