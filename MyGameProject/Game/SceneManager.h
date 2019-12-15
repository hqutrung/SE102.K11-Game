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

	float destSceneID;
	int sceneLv = 1;


	bool isTransitioning;
	bool firstTime;
	float timeTransition;


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

	//void UpdateTransition(double dt);
	bool IsTransitioning();
	int GetSceneID();
};

#endif