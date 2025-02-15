#pragma once
#include "world.h"
#include "graphics.h"
#include "player.h"

extern World* pWorld;
extern Player* pPlayer;
extern SDL_Window* pMainWin;

void InitGameLoop();
void InitWindow();