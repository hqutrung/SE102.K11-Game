class Enemy;
class EnemyState;

class EnemyData
{
public:
	EnemyData();
	~EnemyData();
	Enemy* enemy;
	EnemyState* enemyState;
};