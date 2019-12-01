#pragma once
#include "DemoObjectData.h"
#include "Animation.h"
#include "Textures.h"
#include "Entity.h"
#include "GameConfig.h"
#include "KeyBoard.h"

class DemoObjectState
{
public:
	enum State {
		Idle,
		Running,
		Slash,
		Crouch,
		CrouchSlash,
		Jump,
		Falling,
		Climb,
		UseItem,
		Injured,
	};
	virtual void Update(float dt);
	virtual void Render();
	virtual void HandleInput();
	//virtual void OnCollision(Entity* impactor, Entity::SideCollision side, float collisionTime, float dt = 1.0 / 60);
	virtual State GetState();
	//virtual void ResetState(int dummy);
	virtual int GetAnimationHeight();
	virtual int GetAnimationWidth();
	//virtual BoxCollider GetBody();
	Animation* GetAnimation() { return m_Animation; }
	~DemoObjectState();
protected:
	Animation* m_Animation;
	DemoObjectState();
	DemoObjectState(DemoObjectData* data);
	DemoObjectData* demoObjectData;
};