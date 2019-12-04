#pragma once
#include "Entity.h"
#include "Sprites.h"
#include "Textures.h"

class Surface : public Entity
{
	BoxCollider collider;
public:
	Sprites* sprite;
	Surface();
	~Surface();
	void Render() override;
	virtual void SetSpawnBox(BoxCollider box);
	virtual void SetColliderTop(int top);
	virtual void SetColliderLeft(int left);
	virtual void SetColliderBottom(int bottom);
	virtual void SetColliderRight(int right);
	BoxCollider GetRect() override;
};