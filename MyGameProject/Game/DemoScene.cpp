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
	Textures* texture = Textures::GetInstance();
	//texture->Add(1, L"Resources/running.png", D3DCOLOR_XRGB(255, 163, 177));
	texture->Add(1, L"Resources/spartaspritesheet.png", D3DCOLOR_XRGB(255, 255, 255));
	texture->Add(2, L"Resources/abcd.png", D3DCOLOR_XRGB(255, 255, 255));
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
	
	//Sprites* sp1 = new Sprites(Textures::GetInstance()->GetTexture(1), BoxCollider());
	//sp->NormalDraw(D3DXVECTOR3(0, 0, 0));
	//sp1->Draw(D3DXVECTOR3(sp1->GetWidth() / 2, sp1->GetHeight() / 2, 0), BoxCollider(), D3DCOLOR_XRGB(255,255,255), true);

	Sprites* sp2 = new Sprites(Textures::GetInstance()->GetTexture(2), BoxCollider(0, 33, 65, 42));
	sp2->Draw();
	sp2->Draw(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));

	Sprites* sp3 = new Sprites(Textures::GetInstance()->GetTexture(1), BoxCollider());
	sp3->Draw(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));

}

int DemoScene::GetSceneID()
{
	return 1;
}
