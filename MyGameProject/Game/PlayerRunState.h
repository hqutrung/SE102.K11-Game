#pragma once
#include "PlayerState.h"
#include "Player.h"

class PlayerRunState : public PlayerState
{
public:
	PlayerRunState() {};
	PlayerRunState(PlayerData* data);
	~PlayerRunState();
	void Render() override;
	void Update(float dt) override;
	void HandleInput() override;
	//void OnCollision(Entity* impactor, Entity::SideCollision side, float collisionTime, double dt = 1.0 / 60) override;
	//State GetState() override;
	//void ResetState(int dummy) override;
};