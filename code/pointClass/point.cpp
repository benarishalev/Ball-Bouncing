#include "point.hpp"

Point::Point(float x, float y) {
    this->x = x;
    this->y = y;
}

Point::Point() {
    this->x = 0;
    this->y = 0;
}

bool Point::operator==(const Point& other) {
    if (this->x == other.x && this->y == other.y) {
        return true;
    }
    return false;
}

Point& Point::operator+=(const Point& other) {
    x += other.x;
    y += other.y;
    return *this;
}

Point& Point::operator*=(const float other) {
    x *= other;
    y *= other;
    return *this;
}