#include "Stone.h"
#include "SceneManager.h"

Stone::Stone() : Obstacles() {
	SetTag(STONE);

	Textures* textures = Textures::GetInstance();
	animation->AddFramesA(textures->GetTexture(TEX_OBSTACLES), 2, 1, 2, 8, 28, 2, 28, 0.1f, D3DCOLOR_XRGB(255, 0, 255));
}

Stone::~Stone()
{
}

void Stone::Update(float dt)
{
	if (delayTime <= 0)
	{
		if (animation->GetCurrentFrameID() == 0 || animation->GetCurrentFrameID() == 4)
			animation->SetDefaultTime(2.0f);
		else
			animation->SetDefaultTime(1.0f / 6);
		int frameID = animation->GetCurrentFrameID();
		if (frameID == 2 || frameID == 3 || frameID == 4 || frameID == 5 || frameID == 6)
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
		delayTime = 2.0f + 4.0f / 6;
	else
		delayTime = 0;
	collider.top = 7;
	collider.left = -15;
	collider.bottom = -8;
	collider.right = 22;
}

void Stone::OnCollision(Entity* impactor, SideCollision side, float collisionTime, double dt)
{
}