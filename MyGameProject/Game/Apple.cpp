#include "Apple.h"

Apple::Apple()
{
	auto player = Player::GetInstance();

	if (player->GetMoveDirection() == Entity::MoveDirection::LeftToRight)
		position.x = player->GetPosition().x + 44 / 2 + 2;
	else position.x = player->GetPosition().x - 44 / 2 - 2;

	position.y = player->GetPosition().y + 60 / 2;

	auto texs = Textures::GetInstance();
	texs->Add(1031, "Resources/apple/apple.png", D3DCOLOR_XRGB(255, 0, 255));
	a_Animation = new Animation();
	a_Animation->AddFrames(texs->GetTexture(1031), 1, 4, 0.1, D3DCOLOR_XRGB(255, 255, 255));
	Is_Throw = true;
}

Apple::~Apple()
{
}

void Apple::Update(float dt)
{
	auto player = Player::GetInstance();
	if (player->GetMoveDirection() == Entity::MoveDirection::LeftToRight)
		SetVx(10);
	else  SetVx(-10);

	SetVy(GetVy() - 1);
	
	//collision tam thoi
	if(position.y<=player->GetPosition().y)
	{ 
		Is_Throw = false;
	}
	//
	a_Animation->Update(dt);
}

void Apple::Render()
{
	auto player = Player::GetInstance();
	if (Is_Throw == true)
	{
		a_Animation->Render(position, BoxCollider(), D3DCOLOR_XRGB(255, 255, 255), player->GetMoveDirection() == Entity::MoveDirection::RightToLeft);
	}
}
