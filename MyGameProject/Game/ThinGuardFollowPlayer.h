#pragma once
#include"ThinGuard.h"
#include"EnemyState.h"

class ThinGuardFollowPlayerState : public EnemyState
{
public:
	ThinGuardFollowPlayerState(EnemyData* data);
	void Update(float dt) override;
	void ResetState() override;
private:

};

