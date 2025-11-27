#include "ball.hpp"

Ball::Ball() {
    position = Point(500, 500);
    velocity = Point(0, 0);
    mass = 1.0;
}

void Ball::Draw() {
    if (!Global::ballTexture) {
        return;
    }
    SDL_FRect rect;
    rect.x = position.x;
    rect.y = position.y;
    rect.w = 50;
    rect.h = 50;
    SDL_RenderTexture(Global::renderer, Global::ballTexture, nullptr, &rect);
}

void Ball::Update() {
    position.x += velocity.x;
    position.y += velocity.y;
    HandlePhysics();
}

void Ball::HandlePhysics() {
    Point F(0, 0);

    F.y += mass*1;

    Bounce(F);

    velocity.x += F.x/mass;
    velocity.y += F.y/mass;
}

void Ball::Bounce(Point &F) {
    // distance from the ball to the middle of the screen
    float distance = Global::getDistance(position, {Global::WIDTH/2.0f, Global::HEIGHT/2.0f});
    if (distance > Global::bigBallSize) {
        double angle = atan2(position.y - Global::HEIGHT/2, position.x - Global::WIDTH/2);
        F.x += cos(angle)*10;
        F.y += sin(angle)*10;
    }
}