#include <utility>

//
// Created by goforbroke on 12.03.2023.
//

#ifndef HELLO_GRAPH_DOMAIN_H
#define HELLO_GRAPH_DOMAIN_H

#include <string>
#include <vector>
#include <map>

#define WeighType double

class Vertex {
public:
    explicit Vertex(
            uint64_t id,
            std::string label,
            const std::map<std::string, std::string> &properties = {}
    ) : m_id(id),
        m_label(std::move(label)),
        m_properties(properties) {}

    [[nodiscard]] uint64_t getID() const { return m_id; }

    [[nodiscard]] std::string getLabel() const { return m_label; }

    [[nodiscard]] std::string getProperty(const std::string &key) const {
        const auto &it = m_properties.find(key);
        if (it == m_properties.end()) {
            return "";
        }

        return it->second;
    }

private:
    uint64_t m_id;
    std::string m_label;
    std::map<std::string, std::string> m_properties;

    friend std::ostream &operator<<(std::ostream &os, Vertex *v) {
        os << "V[" << v->m_id << "]";
        return os;
    }
};

class Edge {
public:
    explicit Edge(uint64_t id, std::string label,
                  const Vertex *const from,
                  const Vertex *const to,
                  WeighType weight = 0,
                  const std::map<std::string, std::string> &properties = {})
            : m_id(id),
              m_label(std::move(label)),
              m_vertexFrom(from),
              m_vertexTo(to),
              m_weight(weight),
              m_properties(properties) {}

    [[nodiscard]] uint64_t getID() const { return m_id; }

    [[nodiscard]] const std::string &getLabel() const { return m_label; }

    [[nodiscard]] const Vertex *getVertexFrom() const { return m_vertexFrom; }

    [[nodiscard]] const Vertex *getVertexTo() const { return m_vertexTo; }

    [[nodiscard]] std::string getProperty(const std::string &key) const {
        const auto &it = m_properties.find(key);
        if (it == m_properties.end()) {
            return "";
        }

        return it->second;
    }

    [[nodiscard]] double getWeight() const { return m_weight; }

private:
    uint64_t m_id;
    std::string m_label;
    std::map<std::string, std::string> m_properties;

    const Vertex *m_vertexFrom;
    const Vertex *m_vertexTo;
    WeighType m_weight;

    friend std::ostream &operator<<(std::ostream &os, Edge *e) {
        os << "E[" << e->getID() << "] "
           << e->getVertexFrom() << "->" << e->getVertexTo() << " "
           << "w=" << e->getWeight();
        return os;
    }
};


#endif //HELLO_GRAPH_DOMAIN_H
