//
// Created by gofor on 12.03.2023.
//

#ifndef HELLO_GRAPH_PATH_H
#define HELLO_GRAPH_PATH_H

#include <vector>
#include <map>
#include <ostream>

#include "graph_source.h"

class Path {
public:
    explicit Path(Vertex *const v) {
        mPath.push_back(v);
        mLength = 0;
        mEntries[v] = true;
        mCyclical = false;
    }

    void add(Edge e) {
        mPath.push_back(e.v2);
        mLength += e.w;

        auto it = mEntries.find(e.v2);
        if (it == mEntries.end()) {
            mEntries[e.v2] = true;
            return;
        }

        mCyclical = true;
    }

    [[nodiscard]] uint32_t getLength() const { return mLength; }

    [[nodiscard]] bool isCyclical() const { return mCyclical; }

    bool isFinished(Vertex *start, Vertex *end) {
        return mPath.front() == start && mPath.back() == end;
    }

private:
    std::vector<Vertex *> mPath;
    uint32_t mLength;
    std::map<Vertex *, bool> mEntries;
    bool mCyclical;

    friend std::ostream &operator<<(std::ostream &os, const Path &path);
};

std::ostream &operator<<(std::ostream &os, const Path &path) {
    os << "Nodes: " << path.mPath.size() << " length: " << path.mLength << " ";
    os << "[ ";
    for (const auto id: path.mPath) {
        os << id << " ";
    }
    os << "]";
    return os;
}

#endif //HELLO_GRAPH_PATH_H
