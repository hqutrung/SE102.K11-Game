#pragma once
#include"FatGuard.h"
#include"EnemyState.h"

class FatGuardAttackState : public EnemyState
{
public:
	FatGuardAttackState(EnemyData* data);
	void Update(float dt) override;
	void ResetState() override;
private:

};

