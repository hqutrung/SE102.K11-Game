#pragma once

#include"EnemyData.h"
#include"Animation.h"
#include"Entity.h"
class EnemyState
{

public:
	enum eState {
		Run,
		Attack,
		Fllow
	};
	~EnemyState() ;
	EnemyState(EnemyData* data);

	virtual void Update(float dt);
	virtual void Render();
	virtual void ResetState(int dummy);
	Animation* GetAnimation() { return e_Animation; };
protected:
	Animation* e_Animation;
	EnemyData* enemyData;
};
