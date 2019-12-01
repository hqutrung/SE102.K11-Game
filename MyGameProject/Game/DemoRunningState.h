#pragma once
#include "DemoObjectState.h"
#include "DemoObject.h"

class DemoRunningState : public DemoObjectState
{
public:
	DemoRunningState(DemoObjectData *data);
	~DemoRunningState();
	void Update(float dt) override;
	void Render() override;
	void HandleInput() override;
	//void OnCollision(Entity* impactor, Entity::SideCollision side, float collisionTime, float dt = 1.0 / 60) override;
	State GetState() override;
	//void ResetState(int dummy) override;
};
