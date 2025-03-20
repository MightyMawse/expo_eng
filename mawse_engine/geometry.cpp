#include "geometry.h"

Geometry::Geometry(json mapData) {
	m_mapData = mapData;
}

Geometry::~Geometry() {}

//--------------------------------------------------
// GetWalls()
// purpose: Read json map file and return walls
//--------------------------------------------------
std::vector<Vertex> Geometry::GetWalls() {
	std::vector<std::string> geometry = m_mapData["geometry"].template get<std::vector<std::string>>();
	std::vector<Vertex> walls;

	for (int y = 0; y < geometry.size(); y++) {
		std::string row = geometry[y];
		for (int x = 0; x < row.size(); x++) {
			if (row[x] == '1') { // FIX: Change map elements later
				walls.push_back(Vertex(x, y));
			}
		}
	}

	return walls;
}