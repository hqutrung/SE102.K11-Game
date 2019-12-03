#ifndef __SCENE_MANAGER__
#define __SCENE_MANAGER__

#include "Scene.h"
#include  "DemoScene.h"

class SceneManager
{
	void CreateScene(int sceneID);

	static SceneManager* instance;
	Scene* currentScene;
	float destSceneID;

	bool isTransitioning;
	bool firstTime;
	float timeTransition;

public:
	SceneManager();
	static SceneManager* GetInstance();
	~SceneManager();

	Scene* GetCurrentScene();

	void LoadScene(int sceneID);

	//void UpdateTransition(double dt);
	bool IsTransitioning();
	int GetSceneID();
};

#endif