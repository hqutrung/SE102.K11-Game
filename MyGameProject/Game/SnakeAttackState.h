#pragma once
#include"Jafar.h"
#include"EnemyState.h"

class SnakeAttackState : public EnemyState
{
public:
	SnakeAttackState(EnemyData* data);
	void Update(float dt) override;
	void Render() override;
	void ResetState() override;
private:
	void PuffFire();
};

