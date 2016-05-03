// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <ecst/config.hpp>
#include <ecst/aliases.hpp>

ECST_INNER_PARALLELISM_STRATEGY_NAMESPACE
{
    namespace none
    {
        namespace impl
        {
            template <typename TParameters>
            struct executor
            {
                template <typename TInstance, typename TContext, typename TF>
                void execute(TInstance& inst, TContext& sp, TF&& f)
                {
                    inst.execute_single(sp, FWD(f));
                }
            };
        }
    }
}
ECST_INNER_PARALLELISM_STRATEGY_NAMESPACE_END