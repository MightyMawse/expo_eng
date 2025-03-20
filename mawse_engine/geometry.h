#pragma once
#include <vector>
#include <nlohmann/json.hpp>
#include "typedef.h"
#include "globals.h"
using json = nlohmann::json;

class Geometry {
public:
	Geometry(json mapData);
	~Geometry();

	std::vector<Vertex> GetWalls();
public:
	json m_mapData;
};