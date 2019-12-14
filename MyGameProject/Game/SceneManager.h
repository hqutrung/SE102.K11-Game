#ifndef __SCENE_MANAGER__
#define __SCENE_MANAGER__

#include "Scene.h"
#include "Scene1.h"
#include "RevivingScene.h"
#include"IntroScene.h"

class SceneManager
{
	void CreateScene(int sceneID);

	static SceneManager* instance;
	Scene* currentScene;
	Scene* playScene;
	float destSceneID;
	int sceneLv = 1;


	bool isTransitioning;
	bool firstTime;
	float timeTransition;


public:
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