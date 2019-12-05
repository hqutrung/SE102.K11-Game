#ifndef __SCENE_MANAGER__
#define __SCENE_MANAGER__

#include "Scene.h"
#include "Scene1.h"

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
	static SceneManager* GetInstance();
	SceneManager();
	~SceneManager();

	Scene* GetCurrentScene();

	void LoadScene(int sceneID);

	//void UpdateTransition(double dt);
	bool IsTransitioning();
	int GetSceneID();
};

#endif