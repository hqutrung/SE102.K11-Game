#pragma once
#include"ThinGuard.h"
#include"EnemyState.h"

class ThinGuardFollowPlayerState : public EnemyState
{
public:
	ThinGuardFollowPlayerState() {};
	ThinGuardFollowPlayerState(EnemyData* data);
	~ThinGuardFollowPlayerState() {};
	void Update(float dt) override;
	void ResetState() override;
private:

};

