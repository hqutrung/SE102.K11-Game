#pragma once
#include "Entity.h"
#include "Sprites.h"
#include "Textures.h"

class Surface : public Entity
{
public:
	Sprites* sprite;
	Surface();
	~Surface();
	void Render() override;
	void SetSpawnBox(BoxCollider box);
};