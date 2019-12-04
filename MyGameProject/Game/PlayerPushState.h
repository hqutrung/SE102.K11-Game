#pragma once
#include "PlayerState.h"
#include "Player.h"
#include"KeyBoard.h"
class PlayerPushState : public PlayerState
{

public:
	PlayerPushState() {};
	PlayerPushState(PlayerData* data);
	~PlayerPushState();
	void Render() override;
	void Update(float dt) override;
	void HandleInput() override;
	void OnCollision(Entity* impactor, Entity::SideCollision side, float collisionTime, float dt = 1.0 / 60) override;
	State GetStateName() override;
	void ResetState(int dummy) override;
};