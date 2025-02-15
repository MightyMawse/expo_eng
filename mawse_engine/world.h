#pragma once
#include "typedef.h"
#include <vector>
#include <map>

class World {
public:
	World();
	~World();

	void LoadMap(std::string path);
	void DynamicAddWall(Vertex &v);
	void ReloadWallHash();
	bool IsWall(Vertex v);
private:
	std::vector<Vertex> walls;
	std::vector<Vertex> entities;
	std::map<Vertex, bool> wallHash;
};