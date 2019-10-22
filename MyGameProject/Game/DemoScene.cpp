#include "DemoScene.h"

DemoScene::DemoScene()
{
	LoadContent();
}

DemoScene::~DemoScene()
{
}

void DemoScene::LoadContent()
{
	Textures* t = Textures::GetInstance();
	t->Add(1, L"Resources/player.png", D3DCOLOR_XRGB(255, 255, 255));
}

void DemoScene::Update(float dt)
{
	//cong don thoi gian lai 60 FPS = 1 / 60 giay trong 1 lan goi update
	mTimeCounter += dt;

	//update sau 1 giay
	if (mTimeCounter >= 1.0f)
	{

		//set lai counter
		mTimeCounter = 0;
	}
}

void DemoScene::Render()
{
	Sprites* sp = new Sprites(1, BoxCollider(), Textures::GetInstance()->GetTexture(1));
		sp->NormalDraw(D3DXVECTOR3(0, 0, 0));
		sp->Draw(D3DXVECTOR3(sp->GetWidth()/2,sp->GetHeight()/2,0));
}