#pragma once
#include"ThinGuard.h"
#include"EnemyState.h"

class ThinGuardInjuredState : public EnemyState
{
public:
	ThinGuardInjuredState(EnemyData* data);
	void Update(float dt) override;
	void ResetState() override;
private:

};

