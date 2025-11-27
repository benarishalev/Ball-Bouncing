#ifndef POINT_APP
#define POINT_APP

class Point {
    public:
        float x;
        float y;
    
    Point(float x, float y);
    Point();
    bool operator==(const Point& other);
    Point& operator+=(const Point& other);
    Point& operator*=(const float other);
};

#endif