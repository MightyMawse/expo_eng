#pragma once
#include "typedef.h"

#define ASRT_WARNING 0
#define ASRT_INF 1
#define ASRT_ERROR 2

extern std::string gameInfo_game;
extern std::string gameInfo_title;
extern std::string searchPath_maps;
extern std::string searchPath_sound;

static class System {
public:
	static void LoadGameInfo();
	static void Assert(int asrt, const char* msg);
};