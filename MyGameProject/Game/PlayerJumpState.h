#pragma once
#include "PlayerState.h"
#include "Player.h"

class PlayerJumpState : public PlayerState
{
public:
	PlayerJumpState() {};
	PlayerJumpState(PlayerData* data);
	~PlayerJumpState();
	void Render() override;
	void Update(float dt) override;
	void HandleInput() override;
	void OnCollision(Entity* impactor, Entity::SideCollision side, float collisionTime, double dt = SPF) override;
	State GetStateName() override;
	void ResetState(int dummy) override;
};