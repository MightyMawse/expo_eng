#pragma once
#include "base_entity.h"

class Base_actor : public Base_entity {
public:
	Base_actor(float x, float y, std::string name);
	~Base_actor();

	virtual void Move() = 0;
	void RotateTo(float a);
	void RotateBy(float a);
public:
	int health = 100;
	float a = 1;
};