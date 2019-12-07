#pragma once
#include"FatGuard.h"
#include"EnemyState.h"

class FatGuardFollowPlayerState : public EnemyState
{
public:
	FatGuardFollowPlayerState() {};
	FatGuardFollowPlayerState(EnemyData* data);
	~FatGuardFollowPlayerState() {};
	void Update(float dt) override;
	void ResetState() override;
private:

};

