#include "Data.h"

Data::Data()
{
	auto texs = Textures::GetInstance();
	// _Hp,_Score,_apple
	texs->Add(6000, "Resources/PlayerData/Hp.png", D3DCOLOR_XRGB(255, 0, 255));
	_Hp = new Animation();
	_Hp->AddFramesA(texs->GetTexture(6000), 1, 1, 3, 11, 11, 3, 11, 0.08f, D3DCOLOR_XRGB(255, 0, 255));
	posHp = D3DXVECTOR3(2, -20, 0);
	// life 190,17
	texs->Add(6001, "Resources/PlayerData/life.png", D3DCOLOR_XRGB(255, 0, 255));
	_Life = new Sprites(texs->GetTexture(6001), BoxCollider());
	posLife = D3DXVECTOR3(17, 192, 0);
	//apple 268.5, 196 // ,232
	texs->Add(6002, "Resources/PlayerData/apple.png", D3DCOLOR_XRGB(255, 0, 255));
	_Apple = new Sprites(texs->GetTexture(6002), BoxCollider());
	posApple = D3DXVECTOR3(270, 200, 0);
	//_gem // ,232
	texs->Add(6003, "Resources/PlayerData/gem.png", D3DCOLOR_XRGB(255, 0, 255));
	_Gem = new Sprites(texs->GetTexture(6003), BoxCollider());
	posGem = D3DXVECTOR3(234, 200, 0);

	auto player = Player::GetInstance();
	scores = player->GetScores();
	lifes = player->GetLifes();
	apples = player->GetApples();
	gems = player->GetGems();
}

Data::~Data()
{
}

void Data::Update(float dt)
{
	auto player = Player::GetInstance();
	// _Hp Update
	auto IDframe = _Hp->GetCurrentFrameID();
	int firstFrame = (9 - player->GetHp()) * 4;
	//update lai frame dau tien
	if (player->isInjured)
		_Hp->SetCurrentFrame(firstFrame);

	if (_Hp->IsEndFrame(firstFrame + 3, dt))
		_Hp->SetCurrentFrame(firstFrame);
	else
		if (player->GetHp() == 1)
			if (_Hp->IsLastFrame(dt))
				_Hp->SetCurrentFrame(_Hp->GetCurrentFrameID() - 1);

	_Hp->Update(dt);

	scores = player->GetScores();
	lifes = player->GetLifes();
	apples = player->GetApples();
	gems = player->GetGems();
}

void Data::Render()
{
	auto graphic = Graphic::GetInstance();

	_Hp->NormalRender(posHp);
	graphic->DrawString(std::to_string(scores), D3DXVECTOR3(220, 34, 0), TEX_FONT2);

	_Life->NormalDraw(posLife);
	graphic->DrawString(std::to_string(lifes), posLife + D3DXVECTOR3(26, 24, 0), TEX_FONT1);
	
	_Apple->NormalDraw(posApple);
	graphic->DrawString(std::to_string(apples), posApple + D3DXVECTOR3(18, 16, 0), TEX_FONT1);
	
	_Gem->NormalDraw(posGem);
	graphic->DrawString(std::to_string(gems), posGem + D3DXVECTOR3(19, 16, 0), TEX_FONT1);

}
