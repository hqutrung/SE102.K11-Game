#pragma once
#include "Item.h"
#include "Sprites.h"
#include "Textures.h"

class Stone : public Item {
	Sprites* sprite;
public:
	Stone();
	~Stone();
	void Update(float dt) override;
	void Render() override;

};
