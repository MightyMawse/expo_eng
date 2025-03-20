#include "system.h"
#include "globals.h"
#include <cstring>
#include <SDL.h>

std::string gameInfo_game;
std::string gameInfo_title;
std::string searchPath_maps;
std::string searchPath_sound;

//--------------------------------------------------
// LoadGameInfo()
// purpose: Load all data from gameinfo.json into system
//--------------------------------------------------
void System::LoadGameInfo() {
	json jGameInfo = Globals::ParseJson("gameinfo.json");

	if (jGameInfo == NULL)
		return;

	gameInfo_game = jGameInfo["game"].template get<std::string>();
	gameInfo_title = jGameInfo["title"].template get<std::string>();
	searchPath_maps = jGameInfo["search_paths"]["maps"].template get<std::string>();
	searchPath_sound = jGameInfo["search_paths"]["sound"].template get<std::string>();
}

//--------------------------------------------------
// Assert()
// purpose: Engine assertions
//--------------------------------------------------
void System::Assert(int asrt, const char* msg) {
	switch (asrt)
	{
	case ASRT_ERROR: {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Engine Error", msg, pMainWin);
		break;
	}
	case ASRT_INF: {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Engine", msg, pMainWin);
		break;
	}
	case ASRT_WARNING: {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, "Engine Warning", msg, pMainWin);
		break;
	}
	default:
		break;
	}
}