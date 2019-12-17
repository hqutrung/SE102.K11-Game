#include "ObjectPooling.h"

ObjectPooling* ObjectPooling::instance = NULL;

ObjectPooling::ObjectPooling()
{
	if (instance != NULL)
		delete this;
	instance = this;
}

ObjectPooling* ObjectPooling::GetInstance()
{
	if (instance == NULL)
		instance = new ObjectPooling();
	return instance;
}

void ObjectPooling::AddApple(int number)
{
	Unit* unit;
	pool[APPLE_WEAPON_INDEX].clear();
	for (int i = 0; i < number; i++) {
		AppleWeapon* appleWeapon = new AppleWeapon();
		unit = new Unit(Grid::GetInstance(), appleWeapon);
		pool[APPLE_WEAPON_INDEX].push_back(unit);
	}
}

void ObjectPooling::AddSkeleton(int number)
{
	Unit* unit;
	pool[SKELETON_WEAPON_INDEX].clear();
	for (int i = 0; i < number; i++) {
		SkeletonWeapon* skeletonWeapon = new SkeletonWeapon();
		unit = new Unit(Grid::GetInstance(), skeletonWeapon);
		pool[SKELETON_WEAPON_INDEX].push_back(unit);
	}
}

void ObjectPooling::AddSnakeWeapon(int number)
{
	Unit* unit;
	pool[SNAKE_WEAPON_INDEX].clear();
	for (int i = 0; i < number; i++) {
		SnakeJafarWeapon* snakeJafarWeapon = new SnakeJafarWeapon();
		unit = new Unit(Grid::GetInstance(), snakeJafarWeapon);
		pool[SNAKE_WEAPON_INDEX].push_back(unit);
	}
}

void ObjectPooling::AddFire(int number)
{
	Unit* unit;
	pool[FIRE_INDEX].clear();
	for (int i = 0; i < number; i++) {
		Fire* fire = new Fire();
		unit = new Unit(Grid::GetInstance(), fire);
		pool[FIRE_INDEX].push_back(unit);
	}
}

void ObjectPooling::AddJafarWeapon(int number)
{
	Unit* unit;
	pool[JAFAR_WEAPON_INDEX].clear();
	for (int i = 0; i < number; i++) {
		JafarWeapon* jafarWeapon = new JafarWeapon();
		unit = new Unit(Grid::GetInstance(), jafarWeapon);
		pool[JAFAR_WEAPON_INDEX].push_back(unit);
	}
}

int ObjectPooling::CheckQuantity(int index)
{
	int count = 0;
	auto weapons = pool[index];
	for (size_t i = 0; i < weapons.size(); i++)
		if (!weapons[i]->GetEntity()->IsActived())
			count++;
	return count;
}

bool ObjectPooling::SingleInstantiate(int index, D3DXVECTOR3 position)
{
	auto weapons = pool[index];
	for (size_t i = 0; i < weapons.size(); i++) {
		Weapon* weapon = (Weapon*)weapons[i]->GetEntity();
		if (!weapon->IsActived()) {
			weapon->Instantiate(position);
			weapons[i]->Move(weapon->GetPosition());
			return true;
		}
	}
	return false;
}

void ObjectPooling::MultiInstantiate(int index, D3DXVECTOR3 position)
{
	auto weapons = pool[index];
	for (size_t i = 0; i < weapons.size(); i++) {
		Weapon* weapon = (Weapon*)weapons[i]->GetEntity();
		if (!weapon->IsActived()) {
			weapon->Instantiate(position);
			weapons[i]->Move(weapon->GetPosition());
		}
	}
}
