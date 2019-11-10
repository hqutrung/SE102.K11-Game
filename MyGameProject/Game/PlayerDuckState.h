#pragma once
#include "PlayerState.h"
#include "Player.h"
#include"KeyBoard.h"
class PlayerDuckState : public PlayerState
{

public:
	PlayerDuckState() {};
	PlayerDuckState(PlayerData* data);
	~PlayerDuckState();
	void Render() override;
	void Update(float dt) override;
	void HandleInput() override;
	//void OnCollision(Entity* impactor, Entity::SideCollision side, float collisionTime, double dt = 1.0 / 60) override;
	//State GetState() override;
	//void ResetState(int dummy) override;
};