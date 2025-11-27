#include "global.hpp"

int Global::WIDTH = 0;
int Global::HEIGHT = 0;
SDL_Renderer* Global::renderer;
SDL_Window* Global::window;
std::string Global::mode = "gameloop";

// all
Point Global::mousePosition = Point(0, 0);

SDL_Texture* Global::ballTexture;
SDL_Texture* Global::bigBallTexture;

// static variables (?const)
Point Global::center;
int Global::bigBallSize = 400;
float Global::g = 0.81;
float Global::forceStrength = 0.0001;

void Global::init(const int width, const int height) {
    SDL_Init(SDL_INIT_VIDEO);
    WIDTH = width;
    HEIGHT = height;
    Global::center = Point(WIDTH/2.0f, HEIGHT/2.0f);
    window = SDL_CreateWindow("Circle Ball Bounce", WIDTH, HEIGHT, 0); 
    renderer = SDL_CreateRenderer(window, nullptr);

    ballTexture = IMG_LoadTexture(renderer, "imgs/ball.png");
    bigBallTexture = IMG_LoadTexture(renderer, "imgs/outline_ball.png");
    if (!ballTexture || !bigBallTexture) {
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

float Global::getAngle(Point a, Point b) {
    return atan2(b.y - a.y, b.x - a.x);
}

void Global::drawBigBall() {
    SDL_FRect rect;
    float ballSize = bigBallSize*2 + 175;
    rect.x = center.x - ballSize/2;
    rect.y = center.y - ballSize/2;
    rect.w = ballSize;
    rect.h = ballSize;
    SDL_RenderTexture(renderer, bigBallTexture, nullptr, &rect);
}

void Global::runGameLoop() {
    SDL_Event event;
    bool running = true;

    std::vector<Ball> balls;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
                mode = "quit";
            }
            if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
                balls.emplace_back(mousePosition);
            }
        }

        setMousePosition();

        cleanWindow();

        for (auto &ball : balls) {
            ball.Draw();
            ball.Update();
        }
        drawBigBall();

        presentWindow();
    }
}