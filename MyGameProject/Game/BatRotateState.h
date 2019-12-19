#pragma once
#include"Bat.h"
#include"EnemyState.h"

class BatRotateState : public EnemyState
{
public:
	BatRotateState(EnemyData* data);
	void Update(float dt) override;
	void ResetState() override;
private:

};

