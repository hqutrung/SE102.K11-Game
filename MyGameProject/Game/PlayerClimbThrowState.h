
#include "PlayerState.h"
#include "Player.h"
#include"PlayerIdleState.h"

class PlayerClimbThrowState : public PlayerIdleState
{

public:

	PlayerClimbThrowState(PlayerData* data);
	~PlayerClimbThrowState() {};
	void Render() override;
	void Update(float dt) override;
	void HandleInput() override;

	//void OnCollision(Entity* impactor, Entity::SideCollision side, float collisionTime, double dt = 1.0 / 60) override;
	State GetStateName() override;
	void ResetState() override;
};