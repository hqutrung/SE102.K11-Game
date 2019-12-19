#pragma once
#include"Jafar.h"
#include"EnemyState.h"

class JafarIdleState : public EnemyState
{
public:
	JafarIdleState(EnemyData* data);
	void Update(float dt) override;
	void Render() override;
	void ResetState() override;
private:
	float delaytime;
};

