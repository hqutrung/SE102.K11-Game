#pragma once
#include"FatGuard.h"
#include"EnemyState.h"
#include"EnemyData.h"

class FatGuardAttackState : public EnemyState
{

public:
	FatGuardAttackState() {};
	FatGuardAttackState(EnemyData* data);
	~FatGuardAttackState() {};



	void Update(float dt)override;
	void ResetState(int dummy)override;
	Animation* GetAnimation() { return e_Animation; };

private:

};

