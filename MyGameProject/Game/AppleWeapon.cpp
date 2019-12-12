#include "AppleWeapon.h"

AppleWeapon::AppleWeapon()
{
	auto textures = Textures::GetInstance();
	textures->Add(TEX_APPLE_WEAPON, "Resources/Sprites/shurikenspritesheet.png", D3DCOLOR_XRGB(255, 163, 177));

	PDIRECT3DTEXTURE9 tex = textures->GetTexture(TEX_APPLE_WEAPON);

	anim = new Animation();
	anim->AddFrames(tex, 1, 4, 0.1f);

	tag = PLAYERWEAPON;

	D3DSURFACE_DESC desc;
	tex->GetLevelDesc(0, &desc);

	width = desc.Width / 4;
	height = desc.Height;

	SetColliderTop(width / 2);
	SetColliderBottom(-width / 2);
	SetColliderLeft(-height / 2);

	isActived = false;
}

void AppleWeapon::Update(float dt)
{
}

void AppleWeapon::OnCollision(Entity* impactor, Entity::SideCollision side, float collisionTime, double dt)
{
}

void AppleWeapon::Instantiate(D3DXVECTOR3 position)
{
}

void AppleWeapon::OnDestroy()
{
}
