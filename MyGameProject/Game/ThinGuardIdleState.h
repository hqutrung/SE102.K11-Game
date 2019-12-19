#pragma once
#include"ThinGuard.h"
#include"EnemyState.h"

class ThinGuardIdleState : public EnemyState
{
public:
	ThinGuardIdleState(EnemyData* data);
	void Update(float dt) override;
	void ResetState() override;
private:

};

