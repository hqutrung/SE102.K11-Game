#include "GenieToken.h"

GenieToken::GenieToken() : Item()
{
	Textures* textures = Textures::GetInstance();
	textures->Add(TEX_GENIETOKEN, "Resources/Items/genietoken.png", D3DCOLOR_XRGB(255, 255, 255));
	animation = new Animation();
	animation->AddFrames(textures->GetTexture(TEX_GENIETOKEN), 1, 4, 0.2f, D3DCOLOR_XRGB(255, 255, 255));
	D3DSURFACE_DESC desc;

	textures->GetTexture(TEX_GENIETOKEN)->GetLevelDesc(0, &desc);
	width = desc.Width / 4;
	height = desc.Height;
}

GenieToken::~GenieToken()
{
}

void GenieToken::Update(float dt)
{
	if (animation->GetCurrentFrameID() == 0 || animation->GetCurrentFrameID() == 4)
		animation->SetDefaultTime(1.2f);
	else
		animation->SetDefaultTime(0.2f);
	animation->Update(dt);
	Entity::Update(dt);
}

void GenieToken::Render()
{
	animation->Render(this->GetPosition(), BoxCollider(), D3DCOLOR_XRGB(255, 255, 255), false);
}

void GenieToken::OnCollision(Entity* impactor, SideCollision side, float collisionTime, double dt)
{
}
