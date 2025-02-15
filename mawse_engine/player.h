#include "base_actor.h"

class Player : public Base_actor {
public:
	Player(float x, float y, std::string name);
	~Player();

	void Move() override;
	void MoveBy(float f);
};