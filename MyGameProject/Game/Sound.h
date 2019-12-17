#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include <DxErr.h>
#include <dsound.h>
#include "GameConfig.h"
#include "dsutil.h"

class Sound {
private:
	int currentBackground;
	int counter[100];
	static Sound* instance;
public:
	LPDIRECTSOUND8 g_pDS;
	LPDIRECTSOUNDBUFFER DSBuffer[50];

	Sound();
	~Sound();
	static Sound* GetInstance();

	void LoadSound(HWND hwnd);
	bool InitDirectSound(HWND hwnd);
	LPDIRECTSOUNDBUFFER LoadWaveToSoundBuffer(char* wavFilename);
	void PlayFX(int id);
	void StopFX(int id);
	void PlayMusic(int id);
	void StopMusic();
};


