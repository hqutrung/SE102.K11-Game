#pragma once
#include "PlayerState.h"
#include "Player.h"
#include "PlayerRunState.h"
class PlayerRunAttackState : public PlayerState
{
public:
	PlayerRunAttackState(PlayerData* data);
	~PlayerRunAttackState();
	void Render() override;
	void Update(float dt) override;
	void HandleInput() override;
	void OnCollision(Entity* impactor, Entity::SideCollision side, float collisionTime, double dt = 1.0 / 60) override;
	State GetStateName() override;
	void ResetState(int dummy) override;
};