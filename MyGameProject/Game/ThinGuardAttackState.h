#pragma once
#include"ThinGuard.h"
#include"EnemyState.h"

class ThinGuardAttackState : public EnemyState
{
public:
	ThinGuardAttackState() {};
	ThinGuardAttackState(EnemyData* data);
	~ThinGuardAttackState() {};
	void Update(float dt) override;
	void ResetState() override;
private:

};

