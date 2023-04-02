//
// Created by goforbroke on 12.03.2023.
//

#include <gtest/gtest.h>

#include "../graph_source.h"

TEST(GraphSource_addV, sample_1) {
    auto *graph = new GraphSource();

    graph
            ->addV("point", {{"sign", "A"}})
            ->addV("point", {{"sign", "B"}})
            ->addV("point", {{"sign", "C"}})
            ->addV("point", {{"sign", "I"}});

    ASSERT_EQ("A", graph->V(0)->getProperty("sign"));
    ASSERT_EQ("B", graph->V(1)->getProperty("sign"));
    ASSERT_EQ("C", graph->V(2)->getProperty("sign"));
    ASSERT_EQ("I", graph->V(3)->getProperty("sign"));

    delete graph;
}

TEST(GraphSource_addE, sample_1) {
    auto *graph = new GraphSource();

    graph
            ->addV("point", {{"sign", "A"}})
            ->addV("point", {{"sign", "B"}})
            ->addV("point", {{"sign", "C"}})
            ->addV("point", {{"sign", "I"}});

    graph
            ->addE("and", graph->V(0), graph->V(3)) // A and I
            ->addE("and", graph->V(3), graph->V(1)) // I and B
            ->addE("and", graph->V(3), graph->V(2)) // I and C
            ->addE("and", graph->V(0), graph->V(1)) // A and B
            ;

    ASSERT_EQ(4, graph->getEdges().size());

    ASSERT_EQ("A", graph->E(0)->getVertexFrom()->getProperty("sign"));
    ASSERT_EQ("I", graph->E(1)->getVertexFrom()->getProperty("sign"));
    ASSERT_EQ("I", graph->E(2)->getVertexFrom()->getProperty("sign"));
    ASSERT_EQ("A", graph->E(3)->getVertexFrom()->getProperty("sign"));

    delete graph;
}

TEST(GraphSource_outE, sample_1) {
    auto *graph = new GraphSource();

    graph
            ->addV("point", {{"sign", "A"}})
            ->addV("point", {{"sign", "B"}})
            ->addV("point", {{"sign", "C"}})
            ->addV("point", {{"sign", "I"}});

    graph
            ->addE("and", graph->V(0), graph->V(3)) // A and I
            ->addE("and", graph->V(3), graph->V(1)) // I and B
            ->addE("and", graph->V(3), graph->V(2)) // I and C
            ->addE("and", graph->V(0), graph->V(1)) // A and B
            ;

    ASSERT_EQ(2, graph->outE(graph->V("point", {{"sign", "A"}})).size());
    ASSERT_EQ(2, graph->outE(graph->V("point", {{"sign", "I"}})).size());
    ASSERT_EQ(0, graph->outE(graph->V("point", {{"sign", "B"}})).size());
    ASSERT_EQ(0, graph->outE(graph->V("point", {{"sign", "C"}})).size());

    delete graph;
}