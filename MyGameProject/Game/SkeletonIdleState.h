#pragma once
#include"Skeleton.h"
#include"EnemyState.h"

class SkeletonIdleState : public EnemyState
{
public:
	SkeletonIdleState() {};
	SkeletonIdleState(EnemyData* data);
	~SkeletonIdleState() {};
	void Update(float dt) override;
	void Render() override;
	void ResetState() override;
private:
	bool isExplosive;
	bool flag = false;
};

