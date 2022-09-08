//  Copyright (c) Microsoft Corporation.
//  Licensed under the MIT License.

#pragma once

#include <queue>
#include <string>
#include <vector>

#include "nnfusion/core/graph/gnode.hpp"
#include "nnfusion/core/graph/graph.hpp"

namespace nnfusion
{
    namespace frontend
    {
        namespace stencil_import
        {
            class GraphBuild
            {
            public:
                GraphBuild();
                std::shared_ptr<nnfusion::graph::Graph> get_graph() { return m_graph; }
            private:
                nnfusion::graph::GNodeVector m_graph_outputs;

                std::shared_ptr<nnfusion::graph::Graph> m_graph;
            };
        } // namespace stencil_import
    }     // namespace frontend
} // namespace nnfusion
