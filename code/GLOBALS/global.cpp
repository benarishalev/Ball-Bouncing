#include "global.hpp"

int Global::WIDTH = 0;
int Global::HEIGHT = 0;
SDL_Renderer* Global::renderer;
SDL_Window* Global::window;
std::string Global::mode = "gameloop";

// all
Point Global::mousePosition = Point(0, 0);

SDL_Texture* Global::ballTexture;

// static variables (?const)
int Global::bigBallSize = 50;
float Global::g = 9.81;

void Global::init(const int width, const int height) {
    SDL_Init(SDL_INIT_VIDEO);
    WIDTH = width;
    HEIGHT = height;
    window = SDL_CreateWindow("Circle Ball Bounce", WIDTH, HEIGHT, 0); 
    renderer = SDL_CreateRenderer(window, nullptr);

    ballTexture = IMG_LoadTexture(renderer, "imgs/ball.png");
    if (!ballTexture) {
        std::cerr << "Error loading ball texture: " << SDL_GetError() << std::endl;
        return;
    }
}

void Global::quit() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_DestroyTexture(ballTexture);
    SDL_Quit();
}

void Global::cleanWindow() {
    SDL_SetRenderDrawColor(Global::renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}

void Global::presentWindow() {
    SDL_RenderPresent(renderer);
}

void Global::runLoop() {
    SDL_Event event;
    bool running = true;
    while (running) {
        if (mode == "gameloop") {
            runGameLoop();
        } else if (mode == "quit") {
            running = false;
        }
    }
    quit();
}

void Global::setMousePosition() {
    float x, y;
    SDL_GetMouseState(&x, &y);
    mousePosition = Point(x, y);
}

float Global::getDistance(Point a, Point b) {
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

void Global::runGameLoop() {
    SDL_Event event;
    bool running = true;

    Ball ball;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
                mode = "quit";
            }
        }

        setMousePosition();

        ball.Update();

        cleanWindow();

        ball.Draw();

        presentWindow();
    }
}