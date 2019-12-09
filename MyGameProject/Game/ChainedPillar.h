#pragma once
#include "Surface.h"
#include "Camera.h"

class ChainedPillar : public Surface {
public:
	ChainedPillar();
	~ChainedPillar();
	void Update(float dt) override;
};