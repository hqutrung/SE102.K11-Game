#pragma once
#include "Surface.h"
#include "Camera.h"

class SnakePillar : public Surface {
public:
	SnakePillar();
	void Update(float dt) override;
};