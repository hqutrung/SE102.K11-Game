#include "Bat.h"

Bat::Bat() : Enemy(){
	SetTag(BAT);

	auto textures = Textures::GetInstance();
	textures->Add(TEX_BAT, "Resources/Enemys/bat.png", D3DCOLOR_XRGB(255, 255, 255));

	//fatguardAttackState = new BatdAttackState(enemyData);
}

Bat::~Bat()
{
}

void Bat::Update(float dt)
{
}
