#include "SceneManager.h"
#include"LevelComplete.h"

SceneManager* SceneManager::instance = NULL;

SceneManager::SceneManager()
{
	currentScene = NULL;
	sultanDungeon = new Scene1();
	//jafarPalace = new JafarPalace();
	hp = 0, scores = 0, lifes = 0, gems = 0, apples = 0;

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

	// delete Scene1
	if (isEndScene1 == true)
	{
		// save PlayerData
		auto player = Player::GetInstance();
		hp = player->GetHp();
		scores = player->GetScores();
		lifes = player->GetLifes();
		apples = player->GetApples();
		gems = player->GetGems();

		// delete 
		delete sultanDungeon;
		sultanDungeon = NULL;
		jafarPalace = new JafarPalace();
		isEndScene1 = false;
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
	CreateScene(sceneID);
}

Scene* SceneManager::GetCurrentScene()
{
	return currentScene;
}


int SceneManager::GetSceneID()
{
	return currentScene->GetSceneID();
}
