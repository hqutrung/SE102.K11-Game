#pragma once
#include"Jafar.h"
#include"EnemyState.h"

class JafarIdleState : public EnemyState
{
public:
	JafarIdleState() {};
	JafarIdleState(EnemyData* data);
	~JafarIdleState() {};
	void Update(float dt) override;
	void Render() override;
	void ResetState() override;
private:

};

