#include "base_entity.h"

Base_entity::Base_entity(float x, float y, std::string name) {
	SetPosition(Vertex(x, y));
	m_name = name;
}

Base_entity::~Base_entity() {
	delete this;
}

void Base_entity::SetPosition(Vertex v) {
	m_x = v.m_x;
	m_y = v.m_y;
	this->pos = Vertex(m_x, m_y);
}

Vertex& Base_entity::GetPosition() {
	return pos;
}