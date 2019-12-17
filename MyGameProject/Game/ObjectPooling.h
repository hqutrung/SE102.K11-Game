#pragma once
#include "AppleWeapon.h"
#include "SkeletonWeapon.h"
#include "SnakeJafarWeapon.h"
#include "JafarWeapon.h"
#include "Fire.h"
#include <map>
#include "Unit.h"

class ObjectPooling {
public:
	ObjectPooling();
	static ObjectPooling* GetInstance();
	void AddApple(int number = 1);
	void AddSkeleton(int number = 1);
	void AddSnakeWeapon(int number = 1);
	void AddFire(int number = 1);
	void AddJafarWeapon(int number = 1);
	int CheckQuantity(int index);
	bool SingleInstantiate(int index, D3DXVECTOR3 position);
	void MultiInstantiate(int index, D3DXVECTOR3 position);
private:
	static ObjectPooling *instance;
	std::map<int, std::vector<Unit*>> pool;
};
