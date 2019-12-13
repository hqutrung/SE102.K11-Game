#pragma once
#include "AppleWeapon.h"
#include "SkeletonWeapon.h"
#include <map>
#include "Unit.h"

class ObjectPooling {
public:
	ObjectPooling();
	static ObjectPooling* GetInstance();
	void AddApple(int number = 1);
	void AddSkeleton(int number = 1);
	bool Instantiate(int index, D3DXVECTOR3 position);
private:
	static ObjectPooling *instance;
	std::map<int, std::vector<Unit*>> pool;
};
