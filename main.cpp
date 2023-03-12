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

    std::cout << "========== Graph source stat ==========" << std::endl;
    std::cout << "Vertices: " << graph.getVertices().size() << std::endl;

    std::string startVertexID, destVertexID;
    std::cin >> startVertexID >> destVertexID;

    std::map<Vertex *, WeighType> dist;
    std::map<Vertex *, Edge> pred;

    Dijkstra(graph, graph.get(startVertexID), dist, pred);

    std::cout << "Way between: " << startVertexID << " and " << destVertexID << std::endl;
    std::cout << "Distance:    " << dist[graph.get(destVertexID)] << std::endl;
    std::cout << "Path points: " << extractPath(graph.get(startVertexID), graph.get(destVertexID), pred) << std::endl;

    return 0;
}
