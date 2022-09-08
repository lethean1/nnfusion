# Copyright (c) Microsoft Corporation.
# Licensed under the MIT License.

add_library(stencil_import STATIC
        graph_build.cpp
        graph_build.hpp
)



set_property(TARGET stencil_import PROPERTY POSITION_INDEPENDENT_CODE ON)
target_include_directories(stencil_import PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${GLOBAL_INCLUDE_PATH}
    SYSTEM PRIVATE ${Protobuf_INCLUDE_DIR})
target_link_libraries(stencil_import PRIVATE nnfusion_operators nnfusion_graph)

