#pragma once
#include "Item.h"
#include "Textures.h"

class Peddler : public Item {
	Animation* peddler1;
	D3DXVECTOR2 disToPlayer;
	D3DXVECTOR3 posPeddler1;
public:
	Peddler();
	~Peddler();
	void Update(float dt) override;
	void Render()override;
	void OnDestroy() override {};
	D3DXVECTOR2 GetDisToPlayer() { return disToPlayer; }
};