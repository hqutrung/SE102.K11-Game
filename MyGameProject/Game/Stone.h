#pragma once
#include "Item.h"
#include "Textures.h"
#include "Animation.h"

class Stone : public Item {
	Animation* animation;
public:
	Stone();
	~Stone();
	void Update(float dt) override;
	void Render() override;

};
