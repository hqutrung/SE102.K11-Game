#pragma once
#include"Bat.h"
#include"EnemyState.h"

class BatFollowPlayerState : public EnemyState
{
public:
	BatFollowPlayerState() {};
	BatFollowPlayerState(EnemyData* data);
	~BatFollowPlayerState() {};
	void Update(float dt) override;
	void ResetState() override;
private:

};

