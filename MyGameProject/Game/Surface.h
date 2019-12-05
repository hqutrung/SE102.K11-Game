#pragma once
#include "Entity.h"
#include "Sprites.h"
#include "Textures.h"

class Surface : public Entity
{
protected:
	Sprites* sprite;
	BoxCollider spawnBox;
public:
	Surface();
	~Surface();
	void Render() override;
	virtual void SetSpawnBox(BoxCollider box);
	virtual BoxCollider GetSpawnBox();
	BoxCollider GetRect() override;
};