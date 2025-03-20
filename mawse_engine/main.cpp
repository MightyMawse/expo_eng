#include <iostream>
#include "graphics.h"
#include "globals.h"
#include "system.h"

int main(int argc, char* argv[]) {

	// Load system
	System::LoadGameInfo();

	// Assert test
	System::Assert(ASRT_INF, "Hello Expo engine!");
	
	// Init world
	pWorld = new World();
	pWorld->LoadMap("test_map.json");

	// Init player
	pPlayer = new Player(2, 2, "player");
	pPlayer->RotateTo(90);

	Globals::InitWindow();
	Graphics::Init();
	Globals::InitGameLoop(); // Open SDL window

	return 0;
}