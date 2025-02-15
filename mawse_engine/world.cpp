#include "world.h"

World::World() {
	// TODO: Load map from file

	// Initialise all walls into hashmap for quicker searching
	ReloadWallHash();
}

//--------------------------------------------------
// IsWall()
// purpose: Is there a wall here?
//--------------------------------------------------
bool World::IsWall(Vertex v) {
	//return wallHash[v];

	// BROKEN: wallHash no working :(

	for (Vertex& w : walls) {
		Vertex fl = v.Trunc();
		if (w == fl)
			return true;
	}
	return false;
}

//--------------------------------------------------
// DynamicAddWall()
// purpose: Dynamically add wall outside of map load
//--------------------------------------------------
void World::DynamicAddWall(Vertex& v) {
	walls.push_back(v);
}

//--------------------------------------------------
// ReloadWallHash()
// purpose: Reload the wall hash, is used when a post
// init change has been made
//--------------------------------------------------
void World::ReloadWallHash() {
	wallHash.clear();
	for (Vertex& w : walls) {
		wallHash.insert({ w, true });
	}
}