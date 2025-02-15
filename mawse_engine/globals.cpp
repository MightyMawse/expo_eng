#include "globals.h"
#include <iostream>
#include <cstdlib>
#include <cstdio>

World* pWorld;
Player* pPlayer;
SDL_Window* pMainWin = nullptr;

void InitWindow() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "Failed to initialize the SDL2 library\n";
        std::cout << "SDL2 Error: " << SDL_GetError() << "\n";
        return;
    }

    pMainWin = SDL_CreateWindow("WIN",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WIN_WIDTH, WIN_HEIGHT,
        SDL_WINDOW_SHOWN);

    if (!pMainWin)
    {
        std::cout << "Failed to create window\n";
        std::cout << "SDL2 Error: " << SDL_GetError() << "\n";
        return;
    }
}

void InitGameLoop() {

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
                switch (e.key.keysym.sym)
                {
                case SDLK_LEFT: {
                    pPlayer->RotateBy(-2);
                    Graphics::Render();
                    break;
                }
                case SDLK_RIGHT: {
                    pPlayer->RotateBy(2);
                    Graphics::Render();
                    break;
                }
                case SDLK_UP: {
                    pPlayer->MoveBy(0.1f);
                    Graphics::Render();
                    break;
                }
                case SDLK_DOWN: {
                    pPlayer->MoveBy(-0.1f);
                    Graphics::Render();
                    break;
                }
                }
            }
            }

            SDL_UpdateWindowSurface(pMainWin);
        }
    }
}