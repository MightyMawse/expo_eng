#pragma once
#include <nlohmann/json.hpp>
#include "world.h"
#include "graphics.h"
#include "player.h"
using json = nlohmann::json;

extern World* pWorld;
extern Player* pPlayer;
extern SDL_Window* pMainWin;

static class Globals {
public:
	static void InitGameLoop();
	static void InitWindow();
	static json ParseJson(std::string path);
};