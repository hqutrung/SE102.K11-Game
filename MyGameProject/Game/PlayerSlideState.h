#pragma once
#include "PlayerState.h"
#include "Player.h"

class PlayerSlideState : public PlayerState
{
public:
	PlayerSlideState();
	PlayerSlideState(PlayerData* data);
	~PlayerSlideState();
	void Render() override;
	void Update(float dt) override;
	void HandleInput() override;
};