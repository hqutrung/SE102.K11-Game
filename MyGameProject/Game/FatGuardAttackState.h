#pragma once
#include"FatGuard.h"
#include"EnemyState.h"

class FatGuardAttackState : public EnemyState
{
public:
	FatGuardAttackState(EnemyData* data);
	~FatGuardAttackState() {};
	void Update(float dt) override;
	void ResetState() override;
private:

};

