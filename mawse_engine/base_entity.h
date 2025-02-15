#pragma once
#include "typedef.h"

class Base_entity {
public:
	Base_entity(float x, float y, std::string name);
	~Base_entity();

	void SetPosition(Vertex v);
	Vertex& GetPosition();
public:
	float m_x = 0;
	float m_y = 0;
	std::string m_name = "ent";
	Vertex pos;
};