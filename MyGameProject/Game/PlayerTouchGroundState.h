#pragma once
#include "Player.h"
#include"KeyBoard.h"
#include"PlayerIdleState.h"
class PlayerTouchGroundState : public PlayerIdleState
{

public:
	PlayerTouchGroundState() {};
	PlayerTouchGroundState(PlayerData* data);
	~PlayerTouchGroundState();
	void Update(float dt) override;
	State GetStateName() override;
	void ResetState(int dummy) override;
};