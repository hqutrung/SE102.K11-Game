#pragma once
#include "Animation.h"

class Effect;
struct EffectChain {
	Effect* data;
	EffectChain* pNext, * pPrev;
	EffectChain(Effect* data) : data(data), pPrev(NULL), pNext(NULL) {}
};

class Effect {
public:
	D3DXVECTOR3 pos;
	Animation* animation;
	Effect(D3DXVECTOR3 pos);
	virtual ~Effect();
	virtual bool Update(float dt);
	virtual void Render();
};
