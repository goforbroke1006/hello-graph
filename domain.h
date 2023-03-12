//
// Created by gofor on 12.03.2023.
//

#ifndef HELLO_GRAPH_DOMAIN_H
#define HELLO_GRAPH_DOMAIN_H

#define WeighType double

struct Vertex {
    std::string id;
};

struct Edge {
    Vertex *v1;
    Vertex *v2;
    WeighType w;
};

std::ostream &operator<<(std::ostream &os, Edge e) {
    os << e.v1->id << " -> " << e.w << " -> " << e.v2->id;
    return os;
}

#endif //HELLO_GRAPH_DOMAIN_H
