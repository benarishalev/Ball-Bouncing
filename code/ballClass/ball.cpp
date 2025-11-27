#include "ball.hpp"

Ball::Ball(Point pos) {
    position = pos;
    velocity = Point(0, 0);
    mass = 1.0;
}

void Ball::Draw() {
    if (!Global::ballTexture) {
        return;
    }
    SDL_FRect rect;
    rect.x = position.x-25;
    rect.y = position.y-25;
    rect.w = 50;
    rect.h = 50;
    SDL_RenderTexture(Global::renderer, Global::ballTexture, nullptr, &rect);
}

void Ball::Update() {
    HandlePhysics();
    position.x += velocity.x;
    position.y += velocity.y;
}

void Ball::HandlePhysics() {
    Point F(0, 0);

    F.y += mass*Global::g;

    Bounce(F);

    Point a(F.x/mass, F.y/mass);
    a *= Global::forceStrength;
    velocity += a;
}

void Ball::Bounce(Point &F) {
    // distance from the ball to the middle of the screen
    float distance = Global::getDistance(position, {Global::WIDTH/2.0f, Global::HEIGHT/2.0f});
    if (distance > Global::bigBallSize) {
        double angle = Global::getAngle(position, {Global::WIDTH/2.0f, Global::HEIGHT/2.0f});
        float nx = cos(angle);
        float ny = sin(angle);

        float penetration = distance - Global::bigBallSize;

        float K = 300.0f;
        F.x += nx * K * penetration;
        F.y += ny * K * penetration;

        float vn = velocity.x * nx + velocity.y * ny;
        float damping = 50.0f;
        F.x -= nx * damping * vn;
        F.y -= ny * damping * vn;
    }
}