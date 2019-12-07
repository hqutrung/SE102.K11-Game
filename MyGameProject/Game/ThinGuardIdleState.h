#pragma once
#include"ThinGuard.h"
#include"EnemyState.h"

class ThinGuardIdleState : public EnemyState
{
public:
	ThinGuardIdleState() {};
	ThinGuardIdleState(EnemyData* data);
	~ThinGuardIdleState() {};
	void Update(float dt) override;
	void ResetState() override;
private:

};

