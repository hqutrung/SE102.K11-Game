#include "Peddler.h"
#include "Player.h"

Peddler::Peddler() : Item()
{
	Textures* textures = Textures::GetInstance();
	textures->Add(TEX_PEDDLER, "Resources/Items/peddler.png", D3DCOLOR_XRGB(255, 0, 255));
	animation->AddFramesA(textures->GetTexture(TEX_PEDDLER), 1, 1, 4, 7, 10, 4, 10, 0.06f, D3DCOLOR_XRGB(255, 0, 255));

	peddler1 = new Animation();
	textures->Add(TEX_PEDDLER1, "Resources/Items/peddler1.png", D3DCOLOR_XRGB(255, 0, 255));
	peddler1->AddFramesA(textures->GetTexture(TEX_PEDDLER1), 1, 1, 2, 7, 7, 2, 7, 0.12f, D3DCOLOR_XRGB(255, 0, 255));

	SetTag(PEDDLER);
	disToPlayer = D3DXVECTOR2(this->GetPosition() - Player::GetInstance()->GetPosition());
}

Peddler::~Peddler()
{
	delete peddler1;
	peddler1 = NULL;
	Item::~Item();
}

void Peddler::Update(float dt)
{
	D3DXVECTOR2 dis = GetDisToPlayer();

	posPeddler1 = D3DXVECTOR3(GetPosition().x + 41, GetPosition().y+1 , 0);
	if (animation->GetCurrentFrameID() >= 31)
		peddler1->Update(dt);
	else peddler1->ResetAnimation();

	if (Support::LengthOfVector(dis) <= 120)
	{
		if (animation->IsLastFrame(dt))
			return;
		Item::Update(dt);
	}
	else if (Support::LengthOfVector(dis) <= 160) {
		if (!animation->IsEndFrame(6, dt))
			Item::Update(dt);
	}
	disToPlayer = D3DXVECTOR2(this->GetPosition() - Player::GetInstance()->GetPosition());
	if (animation->GetCurrentFrameID() == 8)
		Sound::GetInstance()->PlayFX(ENEMY_EXPLOSIVE);
	if(animation->GetCurrentFrameID() == 30)
		Sound::GetInstance()->PlayFX(PEDDLE_SHOP);
}

void Peddler::Render()
{
	Item::Render();
	if (animation->GetCurrentFrameID() >= 31)
	{
		peddler1->Render(posPeddler1);
	}
}
