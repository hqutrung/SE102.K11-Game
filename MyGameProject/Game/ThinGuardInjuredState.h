#pragma once
#include"ThinGuard.h"
#include"EnemyState.h"

class ThinGuardInjuredState : public EnemyState
{
public:
	ThinGuardInjuredState() {};
	ThinGuardInjuredState(EnemyData* data);
	~ThinGuardInjuredState() {};
	void Update(float dt) override;
	void ResetState() override;
private:

};

