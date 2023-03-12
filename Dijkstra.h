//
// Created by gofor on 12.03.2023.
//

#ifndef HELLO_GRAPH_DIJKSTRA_H
#define HELLO_GRAPH_DIJKSTRA_H

#include <map>
#include <cfloat>
#include <queue>
#include <ostream>
#include <algorithm> // std::reverse(...)

#include "graph_source.h"

void Dijkstra(
        const GraphSource &graph, Vertex *const vStart,
        std::map<Vertex *, WeighType> &distOut,
        std::map<Vertex *, Edge> &predOut
) {
    for (const auto v: graph.getVertices())
        distOut[v] = 1000000;
    distOut[vStart] = 0;

    std::map<Vertex *, void *> marked;

    std::queue<Vertex *> pq;
    pq.push(vStart);

    while (!pq.empty()) {
        Vertex *current = pq.front();
        pq.pop();
        if (marked.find(current) != marked.end())
            continue;
        marked[current] = nullptr;

        for (const auto &e: graph.outE(current)) {
            WeighType length = distOut[current] + e.w;
            if (length < distOut[e.v2]) {
                distOut[e.v2] = length;
                predOut[e.v2] = e;
                pq.push(e.v2);
            }
        }
    }
}

std::ostream &operator<<(std::ostream &os, const std::map<Vertex *, WeighType> &dist) {
    for (auto it = dist.begin(); it != dist.end(); ++it) {
        os.precision(2);
        os << it->first->id << " " << std::fixed << it->second;
        if (it != --dist.end())
            os << std::endl;
    }
    return os;
}

std::ostream &operator<<(std::ostream &os, const std::map<Vertex *, Edge> &pred) {
    for (auto it = pred.begin(); it != pred.end(); ++it) {
        os << "Edge to " << it->first->id << " (" << it->second << ")";
        if (it != --pred.end())
            os << std::endl;
    }
    return os;
}

std::vector<Vertex *>
extractPath(Vertex *const start, Vertex *const destination, const std::map<Vertex *, Edge> &pred) {
    std::vector<Vertex *> result;

    Vertex *localDestination = destination;
    while (true) {
        result.push_back(localDestination);

        if (localDestination == start)
            break; // find full chain

        const auto &it = pred.find(localDestination);
        if (it == pred.end())
            return {};

        localDestination = (*it).second.v1;
    }

    std::reverse(result.begin(), result.end());

    return result;
}

std::ostream &operator<<(std::ostream &os, const std::vector<Vertex *> &path) {
    os << "[ ";
    for (auto it = path.begin(); it != path.end(); ++it) {
        os << (*it)->id;
        if (it != --path.end())
            os << " -> ";
    }
    os << " ]";
    return os;
}

#endif //HELLO_GRAPH_DIJKSTRA_H
