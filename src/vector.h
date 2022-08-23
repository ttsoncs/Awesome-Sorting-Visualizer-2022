#ifndef VECTOR_H
#define VECTOR_H

#include "../lib/raylib-4.2.0/src/raylib.h"
#include <algorithm>
#include <cstdint>
#include <random>
#include <vector>

class Vector {
  private:
    std::vector<std::pair<int, std::pair<float, Color>>> v_;

    static Color getRandomColor() {
        std::random_device rd;
        std::mt19937 g(rd());
        std::uniform_int_distribution<int> rgb(0, 255);
        return {static_cast<unsigned char>(rgb(g)),
                static_cast<unsigned char>(rgb(g)),
                static_cast<unsigned char>(rgb(g)), 255};
    }

  public:
    explicit Vector(int size) : v_(size) {
        generate();
        randomShuffle();
    }

    void generate() {
        auto [r1, g1, b1, a1] = getRandomColor();
        auto [r2, g2, b2, a2] = getRandomColor();
        auto size{v_.size()};
        auto deltaRed{static_cast<float>(r2 - r1) / static_cast<float>(size)};
        auto deltaGreen{static_cast<float>(g2 - g1) / static_cast<float>(size)};
        auto deltaBlue{static_cast<float>(b2 - b1) / static_cast<float>(size)};
        auto deltaHeight{static_cast<float>(GetScreenHeight()) / size};
        auto barHeight{0.0f};
        for (auto i{0}; i != size; ++i) {
            barHeight = static_cast<float>(i + 1) * deltaHeight;
            v_[i] = {i,
                     {barHeight,
                      {static_cast<unsigned char>(r1 + i * deltaRed),
                       static_cast<unsigned char>(g1 + i * deltaGreen),
                       static_cast<unsigned char>(b1 + i * deltaBlue), 255}}};
        }
    }

    void randomShuffle() {
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(v_.begin(), v_.end(), g);
    }

    void reverseSortedShuffle() { std::reverse(v_.begin(), v_.end()); }

    void almostSortedShuffle() {
        std::random_device rd;
        std::mt19937 g(rd());
        std::uniform_int_distribution<int> dSize((v_.size() / 4), (v_.size() / 2));
        std::uniform_int_distribution<int> dIndex(0, v_.size() - 1);
        auto size{dSize(g)};
        for (auto i{0}; i != size; ++i) {
            auto firstIndex{dIndex(g)};
            auto secondIndex{dIndex(g)};
            std::swap(v_[firstIndex], v_[secondIndex]);
        }
    }

    auto getVector() { return v_; }
};

#endif