#include "SceneManager.h"

SceneManager* SceneManager::instance = NULL;

SceneManager::SceneManager()
{
	currentScene = NULL;
	timeTransition = 0;
	firstTime = true;
	playScene = new Scene1();
}

SceneManager::~SceneManager()
{
}

Scene* SceneManager::GetPlayScene()
{
	return playScene;
}

SceneManager* SceneManager::GetInstance()
{
	if (!instance)
		instance = new SceneManager();
	return instance;
}

void SceneManager::CreateScene(int sceneID)
{
	if (currentScene != NULL && currentScene->GetSceneID() != SCENE_1)
	{
		delete currentScene;
		currentScene = NULL;
	}

	switch (sceneID) {
	case 0:
		//CurrentScene = new IntroScene();
		break;
	case SCENE_1:
		if (playScene != NULL)
			currentScene = playScene;
		break;
	case ID_RIVIVING_SCENE:
		currentScene = new RevivingScene();
		break;
	case JAFAR_PALACE:
		currentScene = new JafarPalace();
		break;
	}
}
void SceneManager::LoadScene(int sceneID)
{
	destSceneID = sceneID;

	CreateScene(sceneID);
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
