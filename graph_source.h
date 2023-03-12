//
// Created by gofor on 12.03.2023.
//

#ifndef HELLO_DIJKSTRA_ALGORITHM_DOMAIN_H
#define HELLO_DIJKSTRA_ALGORITHM_DOMAIN_H

#include <string>
#include <map>
#include <vector>
#include <ostream>

#include "domain.h"

class GraphSource {
public:
    virtual ~GraphSource() {
        for (auto it = this->mEdges.cbegin(); it != this->mEdges.cend();) {
            it = mEdges.erase(it);
        }

        for (auto it = this->mVerticesIndex.cbegin(); it != this->mVerticesIndex.cend();) {
            delete it->second;
            it = mVerticesIndex.erase(it);
        }
    }

    [[nodiscard]] std::vector<Vertex *> getVertices() const {
        std::vector<Vertex *> result;
        result.reserve(this->mVerticesIndex.size());

        for (const auto &pair: this->mVerticesIndex)
            result.push_back(pair.second);

        return result;
    }

    void addEdge(const std::string &id1, const std::string &id2, WeighType w) {
        Vertex *v1 = getOrCreate(id1);
        Vertex *v2 = getOrCreate(id2);
        mEdges.push_back({v1, v2, w});
    }

    [[nodiscard]] Vertex *get(const std::string &id) const {
        Vertex *v = nullptr;
        const auto &it = mVerticesIndex.find(id);
        if (it != mVerticesIndex.end()) {
            v = it->second;
        }
        return v;
    }

    std::vector<Edge> outE(const Vertex *const v) const {
        std::vector<Edge> result;
        for (const auto &edge: mEdges) {
            if (edge.v1 == v) {
                result.push_back(edge);
            }
        }
        return result;
    }

private:
    Vertex *getOrCreate(const std::string &id) {
        Vertex *v;
        if (mVerticesIndex.find(id) != mVerticesIndex.end()) {
            v = mVerticesIndex[id];
        } else {
            v = new Vertex{id};
            mVerticesIndex[id] = v;
        }
        return v;
    }

    std::map<std::string, Vertex *> mVerticesIndex;
    std::vector<Edge> mEdges;
};


#endif //HELLO_DIJKSTRA_ALGORITHM_DOMAIN_H
