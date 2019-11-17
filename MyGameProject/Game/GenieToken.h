#pragma once
#include "Item.h"
#include "Sprites.h"
#include "Textures.h"

class GenieToken : public Item {
	Sprites* sprite;
public:
	GenieToken();
	~GenieToken();
	void Update(float dt) override;
	void Render() override;

};