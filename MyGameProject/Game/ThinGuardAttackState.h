#pragma once
#include"ThinGuard.h"
#include"EnemyState.h"

class ThinGuardAttackState : public EnemyState
{
public:
	ThinGuardAttackState(EnemyData* data);
	void Update(float dt) override;
	void ResetState() override;
private:

};

