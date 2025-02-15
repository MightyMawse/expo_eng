#pragma once
#include <string>

struct Vertex {
	float m_x = 0;
	float m_y = 0;

	Vertex(){}

	Vertex(float x, float y) {
		m_x = x;
		m_y = y;
	}

	Vertex& Trunc() {
		auto f = Vertex(trunc(m_x), trunc(m_y));
		return f;
	}

	bool operator== (const Vertex& v) const {
		return m_x == v.m_x && m_y == v.m_y;
	}

	bool operator < (const Vertex& v) const {
		return false;
	}
};