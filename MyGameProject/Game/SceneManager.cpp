#include "SceneManager.h"
#include"LevelComplete.h"
#include"ContinueScene.h"
#include"MenuScene.h"

SceneManager* SceneManager::instance = NULL;

SceneManager::SceneManager()
{
	currentScene = NULL;
	ResetData();
	startPos = D3DXVECTOR3(0, 0, 0);
}

SceneManager::~SceneManager()
{
	delete currentScene;
	currentScene = NULL;
}

Scene* SceneManager::GetPlayScene()
{
	if (sceneLv == 1)
		return sultanDungeon;
	if (sceneLv == 2)
		return jafarPalace;
}

void SceneManager::DeletePlayScene()
{
	delete sultanDungeon;
	sultanDungeon = NULL;
	delete jafarPalace;
	jafarPalace = NULL;
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
	if (sultanDungeon == NULL && isCompleteSultanDungeon == false)
		sultanDungeon = new SultanDungeon();
	else if (jafarPalace == NULL && isCompleteScene2 == false && isCompleteSultanDungeon)
		jafarPalace = new JafarPalace();

	// delete SultanDungeon
	if (isEndSultanDungeon == true)
	{
		delete sultanDungeon;
		sultanDungeon = NULL;
		jafarPalace = new JafarPalace();
		isEndSultanDungeon = false;
	}

	switch (sceneID)
	{
	case ID_INTRO_SCENE:
		currentScene = new IntroScene();
		Sound::GetInstance()->PlayMusic(INTRO1);
		break;
	case ID_SULTAN_DUNGEON:
		Sound::GetInstance()->PlayMusic(SULTAN_DUNGEON);
		startPos = D3DXVECTOR3(100, 100, 0);
		currentScene = sultanDungeon;
		break;
	case ID_RIVIVING_SCENE:
		currentScene = new RevivingScene();
		Sound::GetInstance()->PlayMusic(MONKEY);
		break;
	case SCENE_JAFAR_PALACE:
		startPos = D3DXVECTOR3(710, 306, 0);
		currentScene = jafarPalace;
		Sound::GetInstance()->PlayMusic(JAFAR_PALACE);
		break;
	case ID_COMPLETE_SCENE:
		currentScene = new LevelComplele();
		Sound::GetInstance()->PlayMusic(LEVEL_COMPLETE);
		break;
	case ID_CONTINUE_SCENE:
		ResetData();
		DeletePlayScene();
		Sound::GetInstance()->PlayMusic(CONTINUE);
		currentScene = new ContinueScene();
		break;
	case ID_MENU_SCENE:
		ResetData();
		DeletePlayScene();
		currentScene = new MenuScene();
		break;

	}


}
void SceneManager::LoadScene(int sceneID)
{
	if (currentScene!=NULL)
		idPrevScene = currentScene->GetSceneID();
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

void SceneManager::SaveData()
{
	// save PlayerData
	auto player = Player::GetInstance();
	hp = player->GetHp();
	scores = player->GetScores();
	lifes = player->GetLifes();
	apples = player->GetApples();
	gems = player->GetGems();
}

void SceneManager::ResetData()
{
	hp = 9;
	scores = 1340;
	lifes = 2;
	gems = 5;
	apples = 10;
}
