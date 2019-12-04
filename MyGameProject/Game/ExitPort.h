#pragma once
#include "Surface.h"

class ExitPort : public Surface {
public:
	ExitPort();
	~ExitPort();
	//void OnCollision(Entity* impactor, SideCollision side, float collisionTime, double dt = 1.0 / 60) override;
	void SetSpawnBox(BoxCollider box) override;
};