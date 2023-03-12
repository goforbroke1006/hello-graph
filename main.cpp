#include <iostream>
#include <string>

#include "graph_source.h"
#include "Dijkstra.h"

int main() {
    GraphSource graph;

    size_t edgesCount;
    std::cin >> edgesCount;

    for (size_t idx = 0; idx < edgesCount; ++idx) {
        std::string vertexId1, vertexId2;
        WeighType weight;

        std::cin >> vertexId1 >> vertexId2 >> weight;

        graph.addEdge(vertexId1, vertexId2, weight);
        graph.addEdge(vertexId2, vertexId1, weight);
    }

    std::string vertexStart, vertexDestination;
    std::cin >> vertexStart >> vertexDestination;

    std::map<Vertex *, WeighType> dist;
    std::map<Vertex *, Edge> pred;

    Dijkstra(graph, graph.get(vertexStart), dist, pred);

    std::cout << dist << std::endl;
    std::cout << pred << std::endl;

    return 0;
}
