#ifndef __SCENE_MANAGER__
#define __SCENE_MANAGER__

#include "Scene.h"
#include "Scene1.h"
#include "RevivingScene.h"
#include"IntroScene.h"
#include "Jafar'sPalace.h"

class SceneManager
{
	void CreateScene(int sceneID);

	static SceneManager* instance;
	Scene* currentScene;
	Scene* sultanDungeon;
	Scene* jafarPalace;
	int sceneLv = 1;

	// Save PlayerData 

	int hp, scores, lifes, gems, apples;


public:
	bool isEndScene1 = false;
	static SceneManager* GetInstance();
	SceneManager();
	~SceneManager();
	Scene* GetPlayScene();
	Scene* GetCurrentScene();

	void SetSceneLv(int lv) { sceneLv = lv; }
	int GetSceneLv() { return sceneLv; }
	void LoadScene(int sceneID);
	int GetSceneID();

	int GetLifes() { return lifes; }
	int GetScores() { return scores; }
	int GetApples() { return apples; }
	int GetGems() { return gems; }
	int GetHp() { return hp; }
};

#endif