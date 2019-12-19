#pragma once
#include "Surface.h"

class ExitPort : public Surface {
public:
	ExitPort();
	void SetSpawnBox(BoxCollider box) override;
};