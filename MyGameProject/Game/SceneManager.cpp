#include "SceneManager.h"

SceneManager* SceneManager::mInstance = NULL;


SceneManager::SceneManager()
{
	mCurrentScene = nullptr;
	timeTransition = 0;
	firstTime = true;
}

SceneManager::~SceneManager()
{
}

SceneManager* SceneManager::GetInstance()
{
	if (!mInstance)
		mInstance = new SceneManager();
	return mInstance;
}

void SceneManager::CreateScene(int sceneID)
{
	if (mCurrentScene != NULL)
		delete mCurrentScene;
	mCurrentScene = NULL;
	/*switch (type) {
	case ToGameOverTo:
		DataManager::HandleGameOver();
		break;
	case Reload:
		DataManager::HandleReload();
		break;
	case Next:
		break;
	}*/
	switch (sceneID) {
	case 0:
		//CurrentScene = new IntroScene();
		break;
	case DEMO_SCENE:
		mCurrentScene = new DemoScene();
		break;
	}
}
void SceneManager::LoadScene(int sceneID)
{
	destSceneID = sceneID;
	if (firstTime) {
		CreateScene(sceneID);
		firstTime = false;
	}
	else
		isTransitioning = true;
}

Scene* SceneManager::GetCurrentScene()
{
	return mCurrentScene;
}

bool SceneManager::IsTransitioning()
{
	return isTransitioning;
}

int SceneManager::GetSceneID()
{
	return mCurrentScene->GetSceneID();
}
