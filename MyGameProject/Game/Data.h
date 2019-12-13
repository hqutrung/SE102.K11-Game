#pragma once
#include "Textures.h"
#include "Animation.h"
#include "Debug.h"
#include "Player.h"
class Data
{
	Animation* _Hp;
	D3DXVECTOR3 posHp;
	Sprites* _Life;
	D3DXVECTOR3 posLife;
	Sprites* _Apple;
	D3DXVECTOR3 posApple;
	Sprites* _Gem;
	D3DXVECTOR3 posGem;



public:
	Data();
	~Data();
	void Update(float dt);
	void Render();

private:

};
