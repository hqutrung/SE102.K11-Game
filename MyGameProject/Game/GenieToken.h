#pragma once
#include "Item.h"
#include "Textures.h"
#include "BigItemExplosion.h"

class GenieToken : public Item {
public:
	GenieToken();
	~GenieToken();
	void Update(float dt) override;
	void OnDestroy() override;
};