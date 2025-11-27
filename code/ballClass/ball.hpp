#ifndef BALL_APP
#define BALL_APP

#include "../pointClass/point.hpp"
#include "../GLOBALS/global.hpp"

class Ball {
    public:
        Point position;
        Point velocity;
        float mass;

    Ball(Point pos);

    void Draw();
    void Update();
    void HandlePhysics();
    void Bounce(Point &F);
};


#endif