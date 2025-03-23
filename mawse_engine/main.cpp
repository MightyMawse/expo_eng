#include <iostream>
#include "graphics.h"
#include "globals.h"
#include "system.h"

int main(int argc, char* argv[]) {

	// Load system
	System::Init();
	
	// Init world
	pWorld = new World();
	pWorld->LoadMap("test_map.json");

	// Init player
	pPlayer = new Player(5, 7, "player");
	pPlayer->RotateTo(180);

	Globals::InitWindow();
	Graphics::Init();
	Globals::InitGameLoop(); // Open SDL window

	return 0;
}