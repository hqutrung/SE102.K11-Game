#ifndef __SCENE_MANAGER__
#define __SCENE_MANAGER__

#include "Scene.h"

class SceneManager
{
public:
	static SceneManager* GetInstance();
	~SceneManager();

	Scene* GetCurrentScene();
	void Update(float dt);
	void ReplaceScene(Scene* scene);

	//int GetSceneID();

private:
	//void CreateScene(int sceneID);

	SceneManager();
	static SceneManager* mInstace;
	Scene* mCurrentScene;

	//float destSceneID;
};

#endif