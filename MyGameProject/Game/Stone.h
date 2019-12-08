#pragma once
#include "Obstacles.h"
#include "Textures.h"
#include "Animation.h"

class Stone : public Obstacles {
public:
	Stone();
	~Stone();
	void SetSpawnBox(BoxCollider box, int id) override;
	void Update(float dt) override;
};
