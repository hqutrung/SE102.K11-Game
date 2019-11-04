#include "SceneManager.h"

SceneManager* SceneManager::instance = NULL;


SceneManager::SceneManager()
{
	currentScene = NULL;
	timeTransition = 0;
	firstTime = true;
}

SceneManager::~SceneManager()
{
}

SceneManager* SceneManager::GetInstance()
{
	if (!instance)
		instance = new SceneManager();
	return instance;
}

void SceneManager::CreateScene(int sceneID)
{
	if (currentScene != NULL)
		delete currentScene;
	currentScene = NULL;

	switch (sceneID) {
	case 0:
		//CurrentScene = new IntroScene();
		break;
	case DEMO_SCENE:
		currentScene = new DemoScene();
		break;
	}
}
void SceneManager::LoadScene(int sceneID)
{
	destSceneID = sceneID;
	if (firstTime) {
		CreateScene(sceneID);
		firstTime = false;
	}
	else
		isTransitioning = true;
}

Scene* SceneManager::GetCurrentScene()
{
	return currentScene;
}

bool SceneManager::IsTransitioning()
{
	return isTransitioning;
}

int SceneManager::GetSceneID()
{
	return currentScene->GetSceneID();
}
