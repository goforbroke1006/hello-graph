//
// Created by goforbroke on 12.03.2023.
//

#include <gtest/gtest.h>

#include "../path.h"

TEST(Path_isCyclical, sample_1) {
    auto *graph = new GraphSource();
    graph
            ->addV("point", {{"sign", "A"}})
            ->addV("point", {{"sign", "B"}})
            ->addV("point", {{"sign", "C"}})
            ->addV("point", {{"sign", "I"}})
            ->addE("and", graph->V(0), graph->V(3)) // A and I
            ->addE("and", graph->V(3), graph->V(1)) // I and B
            ->addE("and", graph->V(3), graph->V(2)) // I and C
            ->addE("and", graph->V(0), graph->V(1)) // A and B
            ;

    Path path(graph->V(0));

    ASSERT_FALSE(path.isCyclical());
}

TEST(Path_isCyclical, sample_2) {
    auto *graph = new GraphSource();
    graph
            ->addV("point", {{"sign", "A"}})
            ->addV("point", {{"sign", "B"}})
            ->addV("point", {{"sign", "C"}})
            ->addV("point", {{"sign", "I"}})
            ->addE("and", graph->V(0), graph->V(3)) // A and I
            ->addE("and", graph->V(3), graph->V(1)) // I and B
            ->addE("and", graph->V(3), graph->V(2)) // I and C
            ->addE("and", graph->V(0), graph->V(1)) // A and B
            ;

    Vertex *pVertexI = graph->V(3); // I
    Path path = Path(pVertexI);
    for (const auto e: graph->outE(pVertexI)) {
        path.add(e);
    }

    ASSERT_FALSE(path.isCyclical());
}

TEST(Path_isCyclical, sample_3) {
    auto *graph = new GraphSource();
    graph
            ->addV("point", {{"sign", "A"}})
            ->addV("point", {{"sign", "B"}})
            ->addV("point", {{"sign", "I"}})
            ->addE("and", graph->V(0), graph->V(3)) // A and I
            ->addE("and", graph->V(3), graph->V(1)) // I and B
            ->addE("and", graph->V(1), graph->V(0)) // B and A
            ;

    Vertex *pVertexA = graph->V(0);
    Path path = Path(pVertexA);
    for (const auto e: graph->outE(pVertexA))
        path.add(e);
    for (const auto e: graph->outE(graph->V(1)))
        path.add(e);
    for (const auto e: graph->outE(graph->V(2)))
        path.add(e);

    ASSERT_TRUE(path.isCyclical());
}
