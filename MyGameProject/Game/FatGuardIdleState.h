#pragma once
#include"FatGuard.h"
#include"EnemyState.h"

class FatGuardIdleState : public EnemyState
{
public:
	FatGuardIdleState(EnemyData* data);
	void Update(float dt) override;
	void ResetState() override;
private:

};

