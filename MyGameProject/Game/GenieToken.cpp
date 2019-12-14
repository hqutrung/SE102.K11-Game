#include "GenieToken.h"

GenieToken::GenieToken() : Item()
{
	SetTag(GENIETOKEN);
	Textures* textures = Textures::GetInstance();
	textures->Add(TEX_GENIETOKEN, "Resources/Items/genietoken.png", D3DCOLOR_XRGB(255, 0, 255));
	animation->AddFrames(textures->GetTexture(TEX_GENIETOKEN), 1, 4, 0.2f, D3DCOLOR_XRGB(255, 0, 255));
	velocity.y = GENIETOKEN_SPEED;

}

GenieToken::~GenieToken()
{
}

void GenieToken::Update(float dt)
{
	startPosY = spawnBox.getCenter().y;
	if (!Support::IsContainedIn(position.y, startPosY - GENIETOKEN_MAX_Y, startPosY + GENIETOKEN_MAX_Y))
		SetVy(-GetVy());


	//
	if (animation->GetCurrentFrameID() == 0 || animation->GetCurrentFrameID() == 4)
		animation->SetDefaultTime(1.2f);
	else
		animation->SetDefaultTime(0.2f);
	Item::Update(dt);
}

void GenieToken::OnDestroy()
{
	isDisappeared = true;
	effect = new EffectChain(new BigItemExplosion(position));
	Grid::GetInstance()->AddEffect(effect);
	SetActive(false);
	//gnhpSound::GetInstance()->PlayFX(SOUND_DAMAGE);
	//return EarnedData(point);
}
