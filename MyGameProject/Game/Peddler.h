#pragma once
#include "Item.h"
#include "Textures.h"

class Peddler : public Item {
	
	D3DXVECTOR2 disToPlayer;
public:
	Peddler();
	~Peddler();
	void Update(float dt) override;
	D3DXVECTOR2 GetDisToPlayer() { return disToPlayer; }
};