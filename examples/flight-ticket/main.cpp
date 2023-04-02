//
// Created by goforbroke on 12.03.2023.
//

#include <iostream>
#include <string>

#include "../../graph_source.h"
#include "../../Dijkstra.h"

#include "utils.h"

int main() {
    uint32_t myOneHourConsts;
    std::cin >> myOneHourConsts;

    size_t flightOptionsCount;
    std::cin >> flightOptionsCount;

    if (0 == flightOptionsCount) {
        std::cerr << "ERROR: Flight options not found!" << std::endl;
        std::cerr << "Stay at home, travelling is not of your cup of tea ;D" << std::endl;
        exit(EXIT_FAILURE);
    }

    auto *graph = new GraphSource();

    for (size_t optionIdx = 0; optionIdx < flightOptionsCount; ++optionIdx) {
        uint32_t flightPrice;
        size_t transfersCount;
        std::cin >> flightPrice >> transfersCount;

        size_t stagesCount = 2 * transfersCount + 1;

        std::vector<const Vertex *> vCache;
        std::string edgeType;
        Duration edgeDuration;

        for (size_t stageIdx = 0; stageIdx < stagesCount; ++stageIdx) {
            if (stageIdx % 2 == 0) {
                // read flight info
                std::string flightNumber, airportDep, airportArr;
                Duration duration;
                std::cin >> flightNumber >> airportDep >> airportArr >> duration;

                graph
                        ->addV("point", {{"code",   airportDep},
                                         {"number", flightNumber},})
                        ->addV("point", {{"code",   airportArr},
                                         {"number", flightNumber},});

                Vertex *from = graph->V("point", {{"code",   airportDep},
                                                  {"number", flightNumber},});
                Vertex *to = graph->V("point", {{"code",   airportArr},
                                                {"number", flightNumber},});
                graph->addE("flight",
                            from,
                            to,
                            static_cast<double>(duration.seconds()), {{"number", flightNumber},});

                vCache.push_back(from);
                vCache.push_back(to);
            } else {
                // read waiting / transfer info
                std::cin >> edgeType >> edgeDuration;
            }

            if (vCache.size() == 4) {
                const Vertex *prevArrVertex = vCache[1];
                const Vertex *nextDepVertex = vCache[2];
                graph->addE(edgeType, prevArrVertex, nextDepVertex, static_cast<double>(edgeDuration.seconds()),
                           {
                                   {"number_arr", prevArrVertex->getProperty("number")},
                                   {"number_dep", nextDepVertex->getProperty("number")},
                           });
                vCache.clear(); // reset cache
            }
        }
    }

    std::cout << "========== Graph source stat ==========" << std::endl;
    std::cout << "Vertices: " << graph->getVertices().size() << std::endl;
    std::cout << "Edges:    " << graph->getEdges().size() << std::endl;

//    std::string startVertexID, destVertexID;
//    std::cin >> startVertexID >> destVertexID;
//
//    std::map<Vertex *, WeighType> dist;
//    std::map<Vertex *, Edge> pred;
//
//    Dijkstra(graph, graph.get(startVertexID), dist, pred);
//
//    int64_t seconds = static_cast<int64_t>(dist[graph.get(destVertexID)]);
//
//    std::cout << "========== Results ==========" << std::endl;
//    std::cout << "Way between: " << startVertexID << " and " << destVertexID << std::endl;
//    std::cout << "Time:        " << Duration(seconds).toString() << std::endl;
//    std::cout << "Path points: " << extractPath(graph.get(startVertexID), graph.get(destVertexID), pred) << std::endl;

    delete graph;

    return 0;
}