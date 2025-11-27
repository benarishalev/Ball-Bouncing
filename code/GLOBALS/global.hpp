#ifndef GLOBAL_APP
#define GLOBAL_APP

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <string>
#include <vector>
#include <iostream>
#include <map>

#include "../pointClass/point.hpp"
#include "../ballClass/ball.hpp"
#include <cmath>

class Global {
    public:
        static int WIDTH;
        static int HEIGHT;
        static SDL_Renderer* renderer;
        static SDL_Window* window;
        static std::string mode;

        // all
        static Point mousePosition;

        static SDL_Texture* ballTexture;
        static SDL_Texture* bigBallTexture;
        static Point center;
        static int bigBallSize;
        static float g;
        static float forceStrength;

    static void init(int width, int height);
    static void quit();
    static void cleanWindow();
    static void presentWindow();
    static void runLoop();
    static void runGameLoop();

    // all
    static void setMousePosition();
    static float getDistance(Point a, Point b);
    static float getAngle(Point a, Point b);
    static void drawBigBall();
};

#endif