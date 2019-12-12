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

bool ObjectPooling::Instantiate(int index, D3DXVECTOR3 position)
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
