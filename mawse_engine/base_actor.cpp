#include "base_actor.h"
#include <iostream>

Base_actor::Base_actor(float x, float y, std::string name) : Base_entity{ x, y, name }{}

Base_actor::~Base_actor() {
	delete this;
}

void Base_actor::RotateTo(float a) {
	this->a = a;
}

void Base_actor::RotateBy(float a) {
	this->a = std::fmod(this->a + a + 360.0f, 360.0f);
	std::cout << "Player Rotation: " + std::to_string(this->a) << std::endl;
}