#pragma once
#include "typedef.h"
#include <vector>

class Geometry;

class World {
public:
	World();
	~World();

	void LoadMap(const char* path);
	void DynamicAddWall(Vertex &v);
	bool IsWall(Vertex v);
private:
	Geometry* pGeometry = nullptr;
	std::vector<Vertex> walls;
	std::vector<Vertex> entities;
};