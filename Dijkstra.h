//
// Created by goforbroke on 12.03.2023.
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
        std::map<const Vertex *, WeighType> &distOut,
        std::map<const Vertex *, const Edge *> &predOut
) {
    for (const auto v: graph.getVertices())
        distOut[v] = 1000000;
    distOut[vStart] = 0;

    std::map<const Vertex *, void *> marked;

    std::queue<const Vertex *> pq;
    pq.push(vStart);

    while (!pq.empty()) {
        const Vertex *current = pq.front();
        pq.pop();
        if (marked.find(current) != marked.end())
            continue;
        marked[current] = nullptr;

        for (const auto *e: graph.outE(current)) {
            WeighType length = distOut[current] + e->getWeight();
            if (length < distOut[e->getVertexTo()]) {
                distOut[e->getVertexTo()] = length;
                predOut[e->getVertexTo()] = e;
                pq.push(e->getVertexTo());
            }
        }
    }
}

std::ostream &operator<<(std::ostream &os, const std::map<Vertex *, WeighType> &dist) {
    for (auto it = dist.begin(); it != dist.end(); ++it) {
        os.precision(2);
        os << it->first->getID() << " " << std::fixed << it->second;
        if (it != --dist.end())
            os << std::endl;
    }
    return os;
}

std::ostream &operator<<(std::ostream &os, const std::map<Vertex *, Edge *> &pred) {
    for (auto it = pred.begin(); it != pred.end(); ++it) {
        os << "Edge to " << it->first->getID() << " (" << it->second << ")";
        if (it != --pred.end())
            os << std::endl;
    }
    return os;
}

std::vector<const Vertex *>
extractPath(Vertex *const start, const Vertex *const destination, const std::map<const Vertex *, Edge> &pred) {
    std::vector<const Vertex *> result;

    const Vertex *localDestination = destination;
    while (true) {
        result.push_back(localDestination);

        if (localDestination == start)
            break; // find full chain

        const auto &it = pred.find(localDestination);
        if (it == pred.end())
            return {};

        localDestination = (*it).second.getVertexFrom();
    }

    std::reverse(result.begin(), result.end());

    return result;
}

std::ostream &operator<<(std::ostream &os, const std::vector<Vertex *> &path) {
    os << "[ ";
    for (auto it = path.begin(); it != path.end(); ++it) {
        os << (*it)->getID();
        if (it != --path.end())
            os << " -> ";
    }
    os << " ]";
    return os;
}

#endif //HELLO_GRAPH_DIJKSTRA_H
