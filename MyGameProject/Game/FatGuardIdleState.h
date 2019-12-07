#pragma once
#include"FatGuard.h"
#include"EnemyState.h"

class FatGuardIdleState : public EnemyState
{
public:
	FatGuardIdleState() {};
	FatGuardIdleState(EnemyData* data);
	~FatGuardIdleState() {};
	void Update(float dt) override;
	void ResetState() override;
private:

};

