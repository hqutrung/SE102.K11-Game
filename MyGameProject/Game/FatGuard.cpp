#include "FatGuard.h"

FatGuard::FatGuard()
{
	Enemy();
	SetTag(FATGUARD);

	Textures* textures = Textures::GetInstance();
	textures->Add(TEX_FATGUARD, "Resources/Enemys/fatguard.png", D3DCOLOR_XRGB(255, 0, 255));
	animation->AddFramesA(textures->GetTexture(TEX_FATGUARD), 1, 1, 1, 8, 8, 4, 8, 0.06f, D3DCOLOR_XRGB(255, 0, 255));
}

FatGuard::~FatGuard()
{
}

void FatGuard::Update(float dt)
{
	auto player = Player::GetInstance();
	disToPlayer = position - player->GetPosition();

	if (!followPlayer(disToPlayer))
	{

		if (abs(disToPlayer.x) < 80 && abs(disToPlayer.y) < 20)
		{
			//state danh
		}
		else if (abs(disToPlayer.y) > 20)
		{
			//state khieukhich
		}
		SetVx(0);
	}
	else
	{
		if (abs(player->GetPosition().x - firstPos.x) > 250 && abs(disToPlayer.y) < 20)
		{
			//Dung yen
		}
	}
	



	Enemy::Update(dt);
}

bool FatGuard::followPlayer(D3DXVECTOR3 dispos)
{
	if (dispos.x > 0)
	{
		SetVx(-FATGUARD_RUNSPEED);
		SetMoveDirection(Entity::MoveDirection::RightToLeft);
	}
	else
	{
		SetVx(FATGUARD_RUNSPEED);
		SetMoveDirection(Entity::MoveDirection::LeftToRight);
	}

	if (abs(dispos.x) < 80 || abs(dispos.y) > 20)
	{
		return false;
	}


	return true;
}
