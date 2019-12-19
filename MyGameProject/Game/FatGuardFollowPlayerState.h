#pragma once
#include"FatGuard.h"
#include"EnemyState.h"

class FatGuardFollowPlayerState : public EnemyState
{
public:
	FatGuardFollowPlayerState(EnemyData* data);
	void Update(float dt) override;
	void ResetState() override;
private:

};

