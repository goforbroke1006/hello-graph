//
// Created by gofor on 12.03.2023.
//

#include <gtest/gtest.h>

#include "../path.h"

TEST(Path_closest, sample_1) {
    GraphSource graph;
    graph.addEdge("a", "i", 1);
    graph.addEdge("i", "b", 1);
    graph.addEdge("i", "c", 1);
    graph.addEdge("a", "b", 1);

    Path path(graph.get("i"));

    ASSERT_FALSE(path.isCyclical());
}

TEST(Path_closest, sample_2) {
    GraphSource graph;
    graph.addEdge("a", "i", 1);
    graph.addEdge("i", "b", 1);
    graph.addEdge("i", "c", 1);
    graph.addEdge("a", "b", 1);

    Vertex *pVertexI = graph.get("i");
    Path path = Path(pVertexI);
    for (const auto e: graph.outE(pVertexI)) {
        path.add(e);
    }

    ASSERT_FALSE(path.isCyclical());
}

TEST(Path_closest, sample_3) {
    GraphSource graph;
    graph.addEdge("a", "i", 1);
    graph.addEdge("i", "b", 1);
    graph.addEdge("b", "a", 1);

    Vertex *pVertexI = graph.get("a");
    Path path = Path(pVertexI);
    for (const auto e: graph.outE(pVertexI)) {
        path.add(e);
    }
    for (const auto e: graph.outE(graph.get("i"))) {
        path.add(e);
    }
    for (const auto e: graph.outE(graph.get("b"))) {
        path.add(e);
    }

    ASSERT_TRUE(path.isCyclical());
}
