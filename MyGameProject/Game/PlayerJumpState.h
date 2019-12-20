#pragma once
#include "PlayerState.h"
#include "Player.h"

class PlayerJumpState : public PlayerState
{
public:
	PlayerJumpState() {};
	PlayerJumpState(PlayerData* data);
	void Render() override;
	void Update(float dt) override;
	void HandleInput() override;
	void OnCollision(Entity* impactor, Entity::SideCollision side, float collisionTime, float dt = SPF) override;
	State GetStateName() override;
	void ResetState(int dummy) override;
};