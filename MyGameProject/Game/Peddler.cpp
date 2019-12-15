#include "Peddler.h"
#include "Player.h"

Peddler::Peddler() : Item()
{
	Textures* textures = Textures::GetInstance();
	textures->Add(TEX_PEDDLER, "Resources/Enemys/enemy.png", D3DCOLOR_XRGB(255, 0, 255));
	animation->AddFramesA(textures->GetTexture(TEX_PEDDLER), 1, 1, 2, 10, 10, 8, 10, 0.1f, D3DCOLOR_XRGB(255, 0, 255));
	SetTag(PEDDLER);
	disToPlayer = D3DXVECTOR2(this->GetPosition() - Player::GetInstance()->GetPosition());
}

Peddler::~Peddler()
{

}

void Peddler::Update(float dt)
{
	D3DXVECTOR2 dis = GetDisToPlayer();

	//Enemy::Update(dt);
	// SetState

	if (Support::LengthOfVector(dis) <= 155)
	{
		Item::Update(dt);
	}
	else {
		if (!animation->IsEndFrame(6, dt))
			Item::Update(dt);
	}
	disToPlayer = D3DXVECTOR2(this->GetPosition() - Player::GetInstance()->GetPosition());
}
