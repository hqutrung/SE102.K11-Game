#include "ChainedPillar.h"
#include "Player.h"

ChainedPillar::ChainedPillar() : Surface() {
	Textures* textures = Textures::GetInstance();
	textures->Add(TEX_CHAINEDPILLAR, "Resources/Items/chainedpillar.png", D3DCOLOR_XRGB(255, 0, 255));
	sprite = new Sprites(textures->GetTexture(TEX_CHAINEDPILLAR), BoxCollider());
	SetTag(CHAINEDPILLAR);
}

ChainedPillar::~ChainedPillar()
{
}

#include "SceneManager.h"
void ChainedPillar::Update(float dt)
{
	auto cam = Camera::GetInstance();
	auto player = Player::GetInstance();
	auto camVeloc = Camera::GetInstance()->GetVelocity();	
	if (cam->GetPosition().x >= cam->GetWidth()/2 || cam->GetPosition().x <= SceneManager::GetInstance()->GetCurrentScene()->GetGameMap()->GetWidth() - cam->GetWidth() / 2)
		SetVx(-(camVeloc.x/10 * 8));
	else
		SetVx(0);
	Entity::Update(dt);
}
