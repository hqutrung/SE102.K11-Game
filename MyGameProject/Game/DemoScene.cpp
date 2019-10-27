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

	demoObject = new DemoObject();
	demoObject->SetPosition(0, SCREEN_HEIGHT / 2);

	/*Textures* texture = Textures::GetInstance();
	texture->Add(1, "Resources/running.png", D3DCOLOR_XRGB(255, 163, 177));
	texture->Add(2, "Resources/spartaspritesheet.png", D3DCOLOR_XRGB(255, 163, 177));
	texture->Add(3, "Resources/mario.png", D3DCOLOR_XRGB(255, 255, 255));

	marioAni = new Animation(0.1f);
	marioAni->AddFrames(texture->GetTexture(3), 1, 15, 0, D3DCOLOR_XRGB(255, 255, 255));
	
	spartaAni = new Animation(0.1f);
	spartaAni->AddFrames(texture->GetTexture(2), 1, 4, 0, D3DCOLOR_XRGB(255, 255, 255));*/

}

void DemoScene::Update(float dt)
{
	//marioAni->Update(dt);
	//spartaAni->Update(dt);
	demoObject->Update(dt);
	ProcessInput();
}

void DemoScene::Render()
{
	//marioAni->Render(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0));
	//spartaAni->Render(D3DXVECTOR3(SCREEN_WIDTH / 2 - 20, SCREEN_HEIGHT / 2 + 10, 0));

	demoObject->Render();

	//Sprites* sp1 = new Sprites(Textures::GetInstance()->GetTexture(1), BoxCollider());
	////sp->NormalDraw(D3DXVECTOR3(0, 0, 0));
	//sp1->Draw(D3DXVECTOR3(sp1->GetWidth() / 2, sp1->GetHeight() / 2, 0), BoxCollider(), D3DCOLOR_XRGB(255,255,255), true);

	//Sprites* sp2 = new Sprites(Textures::GetInstance()->GetTexture(2), BoxCollider(0, 33, 65, 42));
	//sp2->Draw();
	//sp2->Draw(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));

	//Sprites* sp3 = new Sprites(Textures::GetInstance()->GetTexture(3), BoxCollider());
	//sp3->Draw(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));

}

int DemoScene::GetSceneID()
{
	return 1;
}

void DemoScene::ProcessInput()
{
	KeyBoard* input = KeyBoard::GetInstance();
	demoObject->HandleInput();
}
