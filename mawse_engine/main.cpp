#include <iostream>

#include "graphics.h"
#include "globals.h"

int main(int argc, char* argv[]) {
	Vertex wall1 = Vertex(3, 2);
	Vertex wall2 = Vertex(4, 2);
	Vertex wall3 = Vertex(5, 1);
	Vertex wall4 = Vertex(3, 3);
	Vertex wall5 = Vertex(-2, -2);

	Vertex wall6 = Vertex(-3, 2);
	Vertex wall7 = Vertex(-4, 2);
	Vertex wall8 = Vertex(-5, 1);
	Vertex wall9 = Vertex(1, -1);
	
	// Init world
	pWorld = new World();
	pWorld->DynamicAddWall(wall1); 
	pWorld->DynamicAddWall(wall2);
	pWorld->DynamicAddWall(wall3);
	pWorld->DynamicAddWall(wall4);
	pWorld->DynamicAddWall(wall5);
	pWorld->DynamicAddWall(wall6);
	pWorld->DynamicAddWall(wall7);
	pWorld->DynamicAddWall(wall8);
	pWorld->DynamicAddWall(wall9);
	pWorld->ReloadWallHash();

	// Init player
	pPlayer = new Player(1, 1, "player");
	pPlayer->RotateTo(0);

	InitWindow();
	Graphics::Init();
	InitGameLoop(); // Open SDL window

	return 0;
}