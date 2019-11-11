#pragma once
#include"Entity.h"
#include"Animation.h"
#include"Player.h"
class  Apple : public Entity
{
public:
	 Apple();
	~ Apple();
	void Update(float dt);
	void Render();

private:
	Animation *a_Animation;
	bool Is_Throw;
};
