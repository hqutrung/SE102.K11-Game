#include "Item.h"

Item::Item() : Entity()
{
	effect = NULL;
	isDisappeared = false;
	SetStatic(true);
	SetType(ItemType);
	animation = new Animation(0.1f);
	SetVx(0);
	SetVy(0);
}

Item::~Item()
{
	delete animation;
	animation = NULL;
	delete effect;
	effect = NULL;
}

void Item::Update(float dt)
{
	if (isActived) {
		animation->Update(dt);
		Entity::Update(dt);
	}
}

void Item::Render()
{
	animation->Render(this->GetPosition());
}

void Item::SetSpawnBox(BoxCollider box)
{
	spawnBox = box;
	position = D3DXVECTOR3(box.getCenter());
	collider.top = box.top - position.y;
	collider.left = box.left - position.x;
	collider.bottom = box.bottom - position.y;
	collider.right = box.right - position.x;
}

BoxCollider Item::GetSpawnBox()
{
	return spawnBox;
}

BoxCollider Item::GetRect()
{
	BoxCollider r;
	r.top = position.y + collider.top;
	r.bottom = position.y + collider.bottom;
	r.left = position.x + collider.left;
	r.right = position.x + collider.right;
	return r;
}

void Item::SetActive(bool active)
{
	if (isActived == active)
		return;
	if (active && !isDisappeared)
		Spawn();
	else
		MakeInactive();
}

void Item::MakeInactive()
{
	isActived = false;
	animation->ResetAnimation();
}

void Item::Spawn()
{
	isActived = true;
}

void Item::OnDestroy()
{
	isDisappeared = true;
	effect = new EffectChain(new SmallItemExplosion(position));
	Grid::GetInstance()->AddEffect(effect);
	SetActive(false);
	Player::GetInstance()->AddScores(points);
}





