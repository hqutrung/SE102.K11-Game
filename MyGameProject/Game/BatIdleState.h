#pragma once
#include"Bat.h"
#include"EnemyState.h"

class BatIdleState : public EnemyState
{
	float delayTime;
public:
	BatIdleState(EnemyData* data);
	void Update(float dt) override;
	void ResetState() override;
private:

};

