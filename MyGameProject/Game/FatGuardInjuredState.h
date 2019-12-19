#pragma once
#include"FatGuard.h"
#include"EnemyState.h"

class FatGuardInjuredState : public EnemyState
{
public:
	FatGuardInjuredState(EnemyData* data);
	void Update(float dt) override;
	void ResetState() override;
private:

};

