#include "SceneManager.h"
#include"LevelComplete.h"

SceneManager* SceneManager::instance = NULL;

SceneManager::SceneManager()
{
	currentScene = NULL;
	timeTransition = 0;
	firstTime = true;
	sultanDungeon = new Scene1();
	//jafarPalace = new JafarPalace();
}

SceneManager::~SceneManager()
{
}

Scene* SceneManager::GetPlayScene()
{
	if (sceneLv == 1)
		return sultanDungeon;
	if (sceneLv == 2)
		return jafarPalace;
}

SceneManager* SceneManager::GetInstance()
{
	if (!instance)
		instance = new SceneManager();
	return instance;
}

void SceneManager::CreateScene(int sceneID)
{
	if (currentScene != NULL && currentScene != sultanDungeon && currentScene != jafarPalace)
	{
		delete currentScene;
		currentScene = NULL;
	}
	if (isEndScene1 == true)
	{
		sceneLv = 2;
		jafarPalace = new JafarPalace();
		delete sultanDungeon;
		sultanDungeon = NULL;
	}

	switch (sceneID)
	{
	case ID_INTRO_SCENE:
		currentScene = new IntroScene();
		break;
	case SCENE_1:
		currentScene = sultanDungeon;
		break;
	case ID_RIVIVING_SCENE:
		sceneLv = 1;
		currentScene = new RevivingScene();
		break;
	case JAFAR_PALACE:
		currentScene = jafarPalace;
		break;
	case ID_COMPLETE_SCENE:
		currentScene = new LevelComplele();
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
