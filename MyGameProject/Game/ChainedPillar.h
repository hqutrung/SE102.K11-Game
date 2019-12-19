#pragma once
#include "Surface.h"
#include "Camera.h"

class ChainedPillar : public Surface {
public:
	ChainedPillar();
	void Update(float dt) override;
};