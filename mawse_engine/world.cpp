#include "world.h"
#include "globals.h"
#include "system.h"
#include "geometry.h"
#include <fstream>

World::World() {
	// TODO: Load map from file

}

World::~World(){}

//--------------------------------------------------
// IsWall()
// purpose: Is there a wall here?
//--------------------------------------------------
bool World::IsWall(Vertex v) {
	//return wallHash[v];

	// BROKEN: wallHash no working :(

	for (Vertex& w : walls) {
		Vertex fl = v.Trunc();
		bool wallCollison = (v.m_x >= w.m_x && v.m_x <= w.m_x + 1) && (v.m_y >= w.m_y && v.m_y <= w.m_y + 1);
		if (wallCollison)
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
// LoadMap()
// purpose: Load map from file
//--------------------------------------------------
void World::LoadMap(const char* path) {
	json mapData = Globals::ParseJson(searchPath_maps + path);  

	if (mapData == NULL)
		return;

	Geometry* pGeometry = new Geometry(mapData);
	walls = pGeometry->GetWalls();
}