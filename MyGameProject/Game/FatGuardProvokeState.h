#pragma once
#include"FatGuard.h"
#include"EnemyState.h"

class FatGuardProvokeState : public EnemyState
{
public:
	FatGuardProvokeState() {};
	FatGuardProvokeState(EnemyData* data);
	~FatGuardProvokeState() {};
	void Update(float dt) override;
	void ResetState() override;
private:

};

