//  Copyright (c) Microsoft Corporation.
//  Licensed under the MIT License.

#include "graph_build.hpp"

#include "nnfusion/core/operators/generic_op/generic_op.hpp"

namespace nnfusion
{
    namespace frontend
    {
        namespace stencil_import
        {
            GraphBuild::GraphBuild()
            {
                NNFUSION_LOG(INFO) << "Building Stencil Graph";

                m_graph = std::make_shared<nnfusion::graph::Graph>();
                nnfusion::op::OpConfig::any myConfig;
                auto generic_op_1 = std::make_shared<nnfusion::op::GenericOp>(
                    "hdiffsa_node_1",
                    "hdiffsa_lap", 
                    myConfig);

                auto generic_op_2 = std::make_shared<nnfusion::op::GenericOp>(
                    "hdiffsa_node_2",
                    "hdiffsa_flx", 
                    nnfusion::op::OpConfig::any{});

                auto generic_op_3 = std::make_shared<nnfusion::op::GenericOp>(
                    "hdiffsa_node_3",
                    "hdiffsa_fly", 
                    nnfusion::op::OpConfig::any{});

                auto generic_op_4 = std::make_shared<nnfusion::op::GenericOp>(
                    "hdiffsa_node_4",
                    "hdiffsa_out", 
                    nnfusion::op::OpConfig::any{});

                std::vector<int> const_values_0;
                std::vector<int> const_values_1;

                nnfusion::Shape const_shape_0(2);
                const_shape_0[0] = 64;
                const_shape_0[1] = 64;

                nnfusion::Shape const_shape_1(1);
                const_shape_1[0] = 64;

                for(int i = 0; i < 64; i++){
                    for(int j = 0; j < 64; j++){
                        const_values_0.push_back(i + j);
                    }
                }

                for(int i = 0; i < 64; i++){
                    const_values_1.push_back(i);
                }

                auto constant_op_0 = std::make_shared<nnfusion::op::Constant>(
                        element::i64, const_shape_0, const_values_0);
                constant_op_0->set_name("input_node");

                auto constant_op_1 = std::make_shared<nnfusion::op::Constant>(
                        element::i64, const_shape_1, const_values_1);
                constant_op_1->set_name("crlato_node");

                auto constant_op_2 = std::make_shared<nnfusion::op::Constant>(
                        element::i64, const_shape_1, const_values_1);
                constant_op_2->set_name("crlatu_node");

                auto constant_op_3 = std::make_shared<nnfusion::op::Constant>(
                        element::i64, const_shape_0, const_values_0);
                constant_op_3->set_name("mask_node");

                auto input_gnode = m_graph->add_node_and_edge(constant_op_0, nnfusion::graph::GNodeVector({}));
                auto crlato_gnode = m_graph->add_node_and_edge(constant_op_1, nnfusion::graph::GNodeVector({}));
                auto crlatu_gnode = m_graph->add_node_and_edge(constant_op_2, nnfusion::graph::GNodeVector({}));
                auto mask_gnode = m_graph->add_node_and_edge(constant_op_3, nnfusion::graph::GNodeVector({}));

                auto lap_gnode = m_graph->add_node_and_edge(generic_op_1, {input_gnode, crlato_gnode, crlatu_gnode});
                auto flx_gnode = m_graph->add_node_and_edge(generic_op_2, {lap_gnode});
                auto fly_gnode = m_graph->add_node_and_edge(generic_op_3, {crlato_gnode, lap_gnode});
                auto out_gnode = m_graph->add_node_and_edge(generic_op_4, {input_gnode, flx_gnode, fly_gnode, mask_gnode});

                m_graph_outputs.emplace_back(out_gnode); //??????不确定，忘了
                m_graph->set_outputs(m_graph_outputs);
                m_graph->set_default_parameters();
                NNFUSION_LOG(INFO) << "build graph done";
            }
        } // namespace stencil_import
    }     // namespace frontend
} // namespace nnfusion
