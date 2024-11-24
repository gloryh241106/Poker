#pragma once
#include <iostream>

struct Vector2f {
    Vector2f(int p_x, int p_y) : x(p_x), y(p_y) {}
    float x, y;

    void print() {
        std::cout << x << ", " << y << std::endl;
    }
};