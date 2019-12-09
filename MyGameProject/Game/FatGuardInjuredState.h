#pragma once
#include"FatGuard.h"
#include"EnemyState.h"

class FatGuardInjuredState : public EnemyState
{
public:
	FatGuardInjuredState() {};
	FatGuardInjuredState(EnemyData* data);
	~FatGuardInjuredState() {};
	void Update(float dt) override;
	void ResetState() override;
private:

};

