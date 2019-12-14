#include "SnakePillar.h"
#include "Player.h"
#include "SceneManager.h"

SnakePillar::SnakePillar() : Surface()
{
	Textures* textures = Textures::GetInstance();
	textures->Add(TEX_SNAKEPILLAR, "Resources/Items/snakePillar.png", D3DCOLOR_XRGB(255, 0, 255));
	sprite = new Sprites(textures->GetTexture(TEX_SNAKEPILLAR), BoxCollider());
	SetTag(SNAKEPILLAR);
}

SnakePillar::~SnakePillar()
{
}

void SnakePillar::Update(float dt)
{
	auto cam = Camera::GetInstance();
	auto player = Player::GetInstance();
	auto camVeloc = Camera::GetInstance()->GetVelocity();
	if (cam->GetPosition().x >= cam->GetWidth() / 2 || cam->GetPosition().x <= SceneManager::GetInstance()->GetCurrentScene()->GetGameMap()->GetWidth() - cam->GetWidth() / 2)
		SetVx(-(camVeloc.x/7));
	else
		SetVx(0);
	if (cam->GetPosition().y >= cam->GetHeight() / 2 || cam->GetPosition().y <= SceneManager::GetInstance()->GetCurrentScene()->GetGameMap()->GetHeight() - cam->GetHeight() / 2)
		SetVy((camVeloc.y/2));
	else
		SetVy(0);
	Entity::Update(dt);
}
