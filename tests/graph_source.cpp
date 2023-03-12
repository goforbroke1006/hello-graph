//
// Created by gofor on 12.03.2023.
//

#include <gtest/gtest.h>

#include "../graph_source.h"

TEST(GraphSource_closest, sample_1) {
    GraphSource graph;
    graph.addEdge("a", "i", 1);
    graph.addEdge("i", "b", 1);
    graph.addEdge("i", "c", 1);
    graph.addEdge("a", "b", 1);
    ASSERT_EQ(2, graph.outE(graph.get("i")).size());
}

TEST(GraphSource_closest, sample_2) {
    GraphSource graph;
    graph.addEdge("a", "i", 1);
    graph.addEdge("i", "b", 1);
    graph.addEdge("i", "c", 1);
    graph.addEdge("a", "b", 1);
    ASSERT_EQ(0, graph.outE(graph.get("b")).size());
}