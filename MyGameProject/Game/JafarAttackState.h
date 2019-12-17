#pragma once
#include"Jafar.h"
#include"EnemyState.h"

class JafarAttackState : public EnemyState
{
public:
	JafarAttackState() {};
	JafarAttackState(EnemyData* data);
	~JafarAttackState() {};
	void Update(float dt) override;
	void Render() override;
	void ResetState() override;
private:
	void UseWeapon();
	float delayTime;
};

