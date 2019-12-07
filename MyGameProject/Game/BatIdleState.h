#pragma once
#include"Bat.h"
#include"EnemyState.h"

class BatIdleState : public EnemyState
{
	float delayTime;
public:
	BatIdleState() {};
	BatIdleState(EnemyData* data);
	~BatIdleState() {};
	void Update(float dt) override;
	void ResetState() override;
private:

};

