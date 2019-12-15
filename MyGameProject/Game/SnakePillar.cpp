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
	SetVx(-(camVeloc.x / 7));
	SetVy((camVeloc.y / 4 * 3));

	Entity::Update(dt);
}
