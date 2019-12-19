#pragma once
#include"Jafar.h"
#include"EnemyState.h"

class JafarAttackState : public EnemyState
{
public:
	JafarAttackState(EnemyData* data);
	void Update(float dt) override;
	void Render() override;
	void ResetState() override;
private:
	void UseWeapon();
	float delaytime, attackTime;
	bool isReloading;
};

