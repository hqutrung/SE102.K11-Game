#pragma once
#include "EnemyData.h"
#include "Animation.h"
#include "Entity.h"

class EnemyState{
public:
	enum eState {
		Idle,
		Run,
		Attack,
		Follow,
		Provoke,
		Injured,
		Rotate
	};
	EnemyState() {};
	EnemyState(EnemyData* data);
	virtual ~EnemyState();

	virtual void Update(float dt);
	virtual void Render();
	virtual void ResetState();
	Animation* GetAnimation() { return e_Animation; };
protected:
	Animation* e_Animation;
	EnemyData* enemyData;
};
