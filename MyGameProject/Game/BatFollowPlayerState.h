#pragma once
#include"Bat.h"
#include"EnemyState.h"

class BatFollowPlayerState : public EnemyState
{
	float time = 0;
	D3DXVECTOR3 startPos;
	int flag;
	int direction;
public:
	BatFollowPlayerState() {};
	BatFollowPlayerState(EnemyData* data);
	~BatFollowPlayerState() {};
	void Update(float dt) override;
	void ResetState() override;
private:

};

