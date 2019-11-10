
#include "PlayerState.h"
#include "Player.h"
#include"KeyBoard.h"
#include"Textures.h"

class PlayerDuckAttackState : public PlayerState
{
public:
	PlayerDuckAttackState() {};
	PlayerDuckAttackState(PlayerData* data);
	~PlayerDuckAttackState();
	void Render() override;
	void Update(float dt) override;
	void HandleInput() override;
	//void OnCollision(Entity* impactor, Entity::SideCollision side, float collisionTime, double dt = 1.0 / 60) override;
	//State GetState() override;
	//void ResetState(int dummy) override;
};