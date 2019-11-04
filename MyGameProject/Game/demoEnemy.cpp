#include "demoEnemy.h"

DemoEnemy::DemoEnemy()
{
	Textures* textures = Textures::GetInstance();
	textures->Add(TEX_DEMOENEMY, "Resources/spartaspritesheet.png", D3DCOLOR_XRGB(255, 163, 177));

	D3DSURFACE_DESC desc;

	textures->GetTexture(TEX_DEMOENEMY)->GetLevelDesc(0, &desc);
	width = desc.Width / 4;
	height = desc.Height;

	SetActive(true);

	m_Animation = new Animation();
	m_Animation->AddFrames(textures->GetTexture(TEX_DEMOENEMY), 1, 4, 0.1f, D3DCOLOR_XRGB(255, 255, 255));
}

DemoEnemy::~DemoEnemy()
{
}

void DemoEnemy::Update(float dt)
{
	m_Animation->Update(dt);
}

void DemoEnemy::Render()
{
	m_Animation->Render(GetPosition(), BoxCollider(), D3DCOLOR_XRGB(255, 255, 255), GetMoveDirection() == Entity::MoveDirection::RightToLeft);
}
