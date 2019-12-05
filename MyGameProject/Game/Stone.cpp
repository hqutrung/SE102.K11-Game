#include "Stone.h"
#include "SceneManager.h"

Stone::Stone() : Obstacles() {
	SetTag(STONE);

	Textures* textures = Textures::GetInstance();
	textures->Add(TEX_STONE, "Resources/Items/stone.png", D3DCOLOR_XRGB(255, 255, 255));
	animation->AddFrames(textures->GetTexture(TEX_STONE), 1, 8, 0.25f, D3DCOLOR_XRGB(255, 255, 255));
}

Stone::~Stone()
{
}

void Stone::Update(float dt)
{
	if (delayTime <= 0)
	{
		if (animation->GetCurrentFrameID() == 0 || animation->GetCurrentFrameID() == 4)
			animation->SetDefaultTime(1.25f);
		else
			animation->SetDefaultTime(0.2f);
		int frameID = animation->GetCurrentFrameID();
		if (frameID == 3 || frameID == 4 || frameID == 5)
			isCollidable = true;
		else
			isCollidable = false;
		animation->Update(dt);
		return;
	}
	delayTime -= dt;
	
}

void Stone::SetSpawnBox(BoxCollider box, int id)
{
	Obstacles::SetSpawnBox(box, id);
	if (id == 1)
		delayTime = 2.05f;
	else
		delayTime = 0;
}

void Stone::OnCollision(Entity* impactor, SideCollision side, float collisionTime, double dt)
{
}
