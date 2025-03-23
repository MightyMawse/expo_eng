#include "system.h"
#include "globals.h"
#include <cstring>
#include <SDL.h>
#include <SDL_ttf.h>

std::string gameInfo_game;
std::string gameInfo_title;
std::string searchPath_maps;
std::string searchPath_sound;
std::string searchPath_res;
std::string searchPath_textures;
bool debugEnabled = false;

TTF_Font* pFont = nullptr;
SDL_Surface* pDebugSurface = nullptr;
SDL_Texture* pDebugText = nullptr;
SDL_Rect* pDebugRect = nullptr;

//--------------------------------------------------
// Init()
// purpose: Initialise system
//--------------------------------------------------
void System::Init() {
	TTF_Init();
	LoadGameInfo();

	if (debugEnabled)
		InitDebugText();
}

//--------------------------------------------------
// LoadGameInfo()
// purpose: Load all data from gameinfo.json into system
//--------------------------------------------------
void System::LoadGameInfo() {
	json gameInfo = Globals::ParseJson("gameinfo.json");

	if (gameInfo == NULL)
		return;

	gameInfo_game    = gameInfo["game"].template get<std::string>();
	gameInfo_title   = gameInfo["title"].template get<std::string>();
	searchPath_maps  = gameInfo["search_paths"]["maps"].template get<std::string>();
	searchPath_sound = gameInfo["search_paths"]["sound"].template get<std::string>();
	searchPath_res   = gameInfo["search_paths"]["resources"].template get<std::string>();
	searchPath_textures = gameInfo["search_paths"]["textures"].template get<std::string>();
	debugEnabled     = gameInfo["debug"].template get<bool>();
}

//--------------------------------------------------
// DisplayPlayerTransform()
// purpose: Display player position and rotation
//--------------------------------------------------
void System::DisplayPlayerTransform() {
	if (!debugEnabled)
		return;

	Player* localPlayer = pPlayer;

	std::string posX_str = std::to_string(localPlayer->m_x);
	std::string posY_str = std::to_string(localPlayer->m_y);
	std::string heading_str = std::to_string(localPlayer->a);
	std::string gridX_str = std::to_string(floor(localPlayer->m_x));
	std::string gridY_str = std::to_string(floor(localPlayer->m_y));

	std::string debugStr = "Pos_x: " + posX_str + " Pos_y: " + posY_str
		+ " Heading: " + heading_str + " Grid:" + gridX_str + " " + gridY_str;

	SDL_Color white = { 255, 255, 255 };

	pDebugSurface = TTF_RenderText_Solid(pFont, debugStr.c_str(), white);
	pDebugText = SDL_CreateTextureFromSurface(pRenderer, pDebugSurface);

	SDL_RenderCopy(pRenderer, pDebugText, NULL, pDebugRect);
	SDL_FreeSurface(pDebugSurface);
	SDL_DestroyTexture(pDebugText);
	SDL_RenderPresent(pRenderer);
}

//--------------------------------------------------
// InitDebugText()
// purpose: Init the debug text
//--------------------------------------------------
void System::InitDebugText() {
	std::string fontPath = searchPath_res + "verdana.ttf";

	pFont = TTF_OpenFont(fontPath.c_str(), 10);

	if (pFont == nullptr) {
		Assert(ASRT_ERROR, std::string(TTF_GetError()).c_str());
	}

	pDebugRect = new SDL_Rect();
	pDebugRect->x = 0;
	pDebugRect->y = 0;
	pDebugRect->w = 600;
	pDebugRect->h = 50;
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