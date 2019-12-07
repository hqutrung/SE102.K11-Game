#include "BatFollowPlayerState.h"

BatFollowPlayerState::BatFollowPlayerState(EnemyData* data) : EnemyState(data)
{
	Textures* textures = Textures::GetInstance();
	textures->Add(TEX_BAT, "Resources/Enemy/bat.png", D3DCOLOR_XRGB(255, 255, 255));
	e_Animation = new Animation();
	e_Animation->AddFrames(textures->GetTexture(TEX_BAT), 1, 9, 0.1f, D3DCOLOR_XRGB(255, 255, 255));
	/*e_Animation = new Animation();
	e_Animation->AddFramesA(Textures::GetInstance()->GetTexture(TEX_ENEMY), 1, 1, 2, 1, 10, 8, 10, 0.08, D3DCOLOR_XRGB(255, 0, 255));*/
}

void BatFollowPlayerState::Update(float dt)
{
	//....
	e_Animation->Update(dt);
	if (e_Animation->GetCurrentFrameID() == 0)
		e_Animation->SetCurrentFrame(2);
}

void BatFollowPlayerState::ResetState()
{
}
