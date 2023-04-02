//
// Created by goforbroke on 12.03.2023.
//

#ifndef HELLO_DIJKSTRA_ALGORITHM_DOMAIN_H
#define HELLO_DIJKSTRA_ALGORITHM_DOMAIN_H

#include <string>
#include <map>
#include <vector>
#include <ostream>
#include <sstream>

#include "domain.h"

class GraphSource {
public:
    virtual ~GraphSource() {
        for (auto it = this->mEdges.cbegin(); it != this->mEdges.cend();) {
            delete *it;
            it = mEdges.erase(it);
        }

        for (auto it = this->mVertices.cbegin(); it != this->mVertices.cend();) {
            delete *it;
            it = mVertices.erase(it);
        }
    }

    [[nodiscard]] std::vector<Vertex *> getVertices() const {
        return mVertices;
    }

    [[nodiscard]] std::vector<Edge *> getEdges() const {
        return mEdges;
    }

    GraphSource *
    addV(const std::string &label, const std::map<std::string, std::string> &properties) {
        const auto &vertices = getVertices(label, properties);
        if (!vertices.empty())
            return this;

        uint64_t nextID = mVertices.size();
        auto *vertex = new Vertex(nextID, label, properties);
        mVertices.push_back(vertex);
        return this;
    }

    [[nodiscard]]
    Vertex *
    V(uint64_t id) {
        return mVertices[id];
    }

    [[nodiscard]]
    Vertex *
    V(const std::string &label, const std::map<std::string, std::string> &properties) {
        for (auto *v: mVertices) {
            if (label != v->getLabel())
                continue;

            bool matchAllProps = true;
            for (const auto &p: properties) {
                if (p.second != v->getProperty(p.first)) {
                    matchAllProps = false;
                    break;
                }
            }

            if (!matchAllProps)
                continue;

            return v;
        }

        return nullptr;
    }

    [[nodiscard]]
    std::vector<const Vertex *>
    getVertices(const std::string &label, const std::map<std::string, std::string> &properties) const {
        std::vector<const Vertex *> result;
        for (const auto *v: mVertices) {
            if (label != v->getLabel())
                continue;

            bool matchAllProps = true;
            for (const auto &p: properties) {
                if (p.second != v->getProperty(p.first)) {
                    matchAllProps = false;
                    break;
                }
            }

            if (!matchAllProps)
                continue;

            result.push_back(v);
        }
        return result;
    }

    GraphSource *
    addE(const std::string &label,
         const Vertex *const from, const Vertex *const to,
         double weight = 0,
         const std::map<std::string, std::string> &properties = {}
    ) {
        auto *edge = this->E(label, from, to, properties);
        if (nullptr != edge)
            return this;

        uint64_t nextID = mEdges.size();
        edge = new Edge(nextID, label, from, to, weight, properties);
        mEdges.push_back(edge);
        return this;
    }

    [[nodiscard]]
    Edge *
    E(uint64_t id) {
        return mEdges[id];
    }

    [[nodiscard]]
    Edge *
    E(const std::string &label,
      const Vertex *const from, const Vertex *const to,
      const std::map<std::string, std::string> &properties) {
        for (auto *edge: mEdges) {
            if (edge->getLabel() != label)
                continue;

            if (edge->getVertexFrom() != from)
                continue;

            if (edge->getVertexTo() != to)
                continue;

            bool matchAllProps = true;
            for (const auto &p: properties) {
                if (p.second != edge->getProperty(p.first)) {
                    matchAllProps = false;
                    break;
                }
            }

            if (!matchAllProps)
                continue;

            return edge;
        }

        return nullptr;
    }

    [[nodiscard]] Vertex *get(uint64_t id) const {
        return mVertices.at(id);
    }

    std::vector<Edge *> outE(const Vertex *const v) const {
        std::vector<Edge *> result;
        for (const auto &edge: mEdges) {
            if (edge->getVertexFrom() == v) {
                result.push_back(edge);
            }
        }
        return result;
    }

private:
    std::vector<Vertex *> mVertices;
    std::vector<Edge *> mEdges;
};


#endif //HELLO_DIJKSTRA_ALGORITHM_DOMAIN_H
