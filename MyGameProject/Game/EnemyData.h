#pragma once
class Enemy;

class EnemyData
{
public:
	EnemyData();
	~EnemyData();
	Enemy* enemy;
	EnemyState* enemyState;
};