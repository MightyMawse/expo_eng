#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <fstream>
#include "globals.h"
#include "system.h"

World* pWorld = nullptr;
Player* pPlayer = nullptr;
SDL_Window* pMainWin = nullptr;

//--------------------------------------------------
// InitWindow()
// purpose: Initialise engine window
//--------------------------------------------------
void Globals::InitWindow() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "Failed to initialize the SDL2 library\n";
        std::cout << "SDL2 Error: " << SDL_GetError() << "\n";
        return;
    }

    pMainWin = SDL_CreateWindow(
        gameInfo_game.c_str(),
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WIN_WIDTH, WIN_HEIGHT,
        SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN);

    if (!pMainWin)
    {
        std::cout << "Failed to create window\n";
        std::cout << "SDL2 Error: " << SDL_GetError() << "\n";
        return;
    }
}

//--------------------------------------------------
// InitGameLoop()
// purpose: Start the game loop and listen for input
//--------------------------------------------------
void Globals::InitGameLoop() {

    bool keep_window_open = true;
    bool rendered = false;
    while (keep_window_open)
    {
        SDL_Event e;

        // TEST: Draw column test
        if (pRenderer != nullptr) {
            if (!rendered) {
                rendered = true;
                Graphics::Render();
            }
        }

        while (SDL_PollEvent(&e) > 0)
        {
            switch (e.type)
            {
            case SDL_QUIT:{
                keep_window_open = false;
                break;
            }
            case SDL_KEYDOWN: { // TODO: move to player?
                SDL_Keycode key = e.key.keysym.sym;

                if (key == SDLK_LEFT) {
                    pPlayer->RotateBy(-pPlayer->rotationSpeed);
                }
                else if (key == SDLK_RIGHT) {
                    pPlayer->RotateBy(pPlayer->rotationSpeed);
                }
                else if (key == SDLK_UP) {
                    pPlayer->MoveBy(pPlayer->movementSpeed);
                }
                else if (key == SDLK_DOWN) {
                    pPlayer->MoveBy(-pPlayer->movementSpeed);
                }

                Graphics::Render();
                System::DisplayPlayerTransform();
            }
            }

            SDL_UpdateWindowSurface(pMainWin);
        }
    }
}

//--------------------------------------------------
// ParseJson()
// purpose: Parse file into json object
//--------------------------------------------------
json Globals::ParseJson(std::string path) {
    std::ifstream f(path);
    std::string msg = "Could not open file: " + path;

    if (!f) {
        System::Assert(ASRT_ERROR, msg.c_str());
        return NULL;
    }

    return json::parse(f);
}