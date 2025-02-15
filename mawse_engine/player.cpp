#include "player.h"
#include "typedef.h"
#include "graphics.h"
#include "utils.h"

#include <iostream>

Player::Player(float x, float y, std::string name) : Base_actor(x, y, name) {}

Player::~Player() {
	delete this;
}

void Player::Move() {
	return;
}

void Player::MoveBy(float f) {
	Vertex forward = Graphics::StepFoward(this->GetPosition(), f, this->a);
	this->SetPosition(forward);
}