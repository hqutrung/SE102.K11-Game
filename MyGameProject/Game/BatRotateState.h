#pragma once
#include"Bat.h"
#include"EnemyState.h"

class BatRotateState : public EnemyState
{
public:
	BatRotateState() {};
	BatRotateState(EnemyData* data);
	~BatRotateState() {};
	void Update(float dt) override;
	void ResetState() override;
private:

};

