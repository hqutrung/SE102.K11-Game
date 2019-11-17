#pragma once
#include "Item.h"
#include "Sprites.h"
#include "Textures.h"

class Ball : public Item {
	Sprites* sprite;
public:
	Ball();
	~Ball();
	void Update(float dt) override;
	void Render() override;

};