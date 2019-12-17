#pragma once
#include "Enemy.h"
#include "Textures.h"
#include "JafarIdleState.h"
#include "JafarAttackState.h"
#include "SnakeAttackState.h"

class Jafar : public Enemy {
	bool isSnake;
protected:
	EnemyState	* jafarIdleState,
				* jafarAttackState,
				* snakeAttackState;
public:
	Jafar();
	~Jafar();
	void Update(float dt) override;
	void OnCollision(Entity* impactor, SideCollision side, float collisionTime, float dt = 1.0f / 60) override;
	void SetState(EnemyState::eState state);
	void SetSpawnBox(BoxCollider box, int direction) override;
	void Spawn();
	void OnDestroy() override;
	bool IsSnake() { return isSnake; }
	void TurnOutSnake();
};
