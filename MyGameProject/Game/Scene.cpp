#include "Scene.h"


Scene::Scene()
{
	backColor = 0x4866ff;
}

Scene::~Scene()
{

}

void Scene::ProcessInput()
{
}

D3DCOLOR Scene::GetBackcolor()
{
	return backColor;
}

void Scene::SetBackColor(D3DCOLOR backColor)
{
	this->backColor = backColor;
}

float Scene::GetGameTime()
{
	return gameTime;
}
