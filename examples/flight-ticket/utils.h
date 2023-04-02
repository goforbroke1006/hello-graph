//
// Created by goforbroke on 12.03.2023.
//

#ifndef HELLO_GRAPH_UTILS_H
#define HELLO_GRAPH_UTILS_H

#include <cstdint>
#include <string>
#include <map>
#include <regex>
#include <istream>

class Duration {
public:
    explicit Duration(int64_t mDurationSeconds = 0) : mDurationSeconds(mDurationSeconds) {}

    static Duration parse(const std::string &s) {
        std::map<std::string, int> multipliers = {
                {"h", 3600},
                {"m", 60},
                {"s", 1},
        };

        std::regex durPart(R"((\d+)([a-z]+))");
        auto parts_begin = std::sregex_iterator(s.begin(), s.end(), durPart);
        auto parts_end = std::sregex_iterator();

        int64_t seconds = 0;
        for (auto it = parts_begin; it != parts_end; ++it) {
            const std::smatch &match = *it;

            int num = std::stoi(match[1].str());
            std::string dim = match[2].str();

            if (multipliers.find(dim) == multipliers.end())
                throw std::logic_error("invalid duration " + s);

            seconds += num * multipliers[dim];
        }
        return Duration(seconds);
    }

    [[nodiscard]] std::string toString() const {
        int64_t rem = mDurationSeconds;
        std::stringstream ss;

        if (rem > 3600) {
            int64_t hours = rem / 3600;
            ss << hours << "h";
            rem = rem % 3600;
        }

        if (rem > 60) {
            int64_t minutes = rem / 60;
            ss << minutes << "m";
            rem = rem % 60;
        }

        if (rem > 0) {
            ss << rem << "s";
        }

        return ss.str();
    }

    [[nodiscard]] uint64_t seconds() const {
        return mDurationSeconds;
    }

private:
    int64_t mDurationSeconds;
};

std::istream &operator>>(std::istream &is, Duration &d) {
    std::string payload;
    is >> payload;
    d = Duration::parse(payload);
    return is;
}

#endif //HELLO_GRAPH_UTILS_H
