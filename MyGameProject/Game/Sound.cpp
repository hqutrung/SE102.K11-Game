#include "Sound.h"

Sound* Sound::instance = NULL;

Sound::Sound()
{
	g_pDS = NULL;
}

Sound::~Sound()
{
}

Sound* Sound::GetInstance()
{
	if (instance == NULL)
		instance = new Sound();
	return instance;
}

void Sound::LoadSound(HWND hwnd)
{
	if (!InitDirectSound(hwnd))
	{
		//MessageBox(NULL, "Unable to init DirectSound", "ERROR", MB_OK);
	}
	DSBuffer[SULTAN_DUNGEON] = LoadWaveToSoundBuffer((char*)"Resources/Sounds/SultanDungeon.wav");
	DSBuffer[JAFAR_PALACE] = LoadWaveToSoundBuffer((char*)"Resources/Sounds/JafarPalace.wav");
	DSBuffer[INTRO] = LoadWaveToSoundBuffer((char*)"Resources/Sounds/Intro.wav");
	DSBuffer[REVIVING] = LoadWaveToSoundBuffer((char*)"Resources/Sounds/AladinReviving.wav");
	DSBuffer[LEVEL_COMPLETE] = LoadWaveToSoundBuffer((char*)"Resources/Sounds/LevelComplete.wav");
	DSBuffer[STONE_RUMBLE] = LoadWaveToSoundBuffer((char*)"Resources/Sounds/StoneRumble.wav");
	DSBuffer[GENIE_EXPLOSIVE] = LoadWaveToSoundBuffer((char*)"Resources/Sounds/GenieExplosive.wav");
	DSBuffer[HEART_COLLECT] = LoadWaveToSoundBuffer((char*)"Resources/Sounds/HeartCollect.wav");
	DSBuffer[CONTINUE_POINT] = LoadWaveToSoundBuffer((char*)"Resources/Sounds/ContinuePoint.wav");
	DSBuffer[APPLE_COLLECT] = LoadWaveToSoundBuffer((char*)"Resources/Sounds/AppleCollect.wav");
	DSBuffer[GEM_COLLECT] = LoadWaveToSoundBuffer((char*)"Resources/Sounds/GemCollect.wav");
	DSBuffer[COMING_OUT] = LoadWaveToSoundBuffer((char*)"Resources/Sounds/ComingOut.wav");
	DSBuffer[SKELETON_EXPLOSIVE] = LoadWaveToSoundBuffer((char*)"Resources/Sounds/SkeletonExplosive.wav");
	DSBuffer[SPIKES] = LoadWaveToSoundBuffer((char*)"Resources/Sounds/Spikes.wav");
	DSBuffer[GUARD_INJURED] = LoadWaveToSoundBuffer((char*)"Resources/Sounds/GuardInjured.wav");
	DSBuffer[SPLASH_WALL] = LoadWaveToSoundBuffer((char*)"Resources/Sounds/SplashWall.wav");
	DSBuffer[WOW] = LoadWaveToSoundBuffer((char*)"Resources/Sounds/Wow.wav");
	DSBuffer[APPPLE_EXPLOSIVE] = LoadWaveToSoundBuffer((char*)"Resources/Sounds/AppleExplosive.wav");
	DSBuffer[COME_ON] = LoadWaveToSoundBuffer((char*)"Resources/Sounds/ComeOn.wav");
	DSBuffer[ALADDIN_IDLE_SPLASH] = LoadWaveToSoundBuffer((char*)"Resources/Sounds/splash.wav");
	DSBuffer[ALADDIN_DUCK_SPLASH] = LoadWaveToSoundBuffer((char*)"Resources/Sounds/AladinDuckAttack.wav");
	DSBuffer[ALADDIN_THROW_APPLE] = LoadWaveToSoundBuffer((char*)"Resources/Sounds/ThrowApple.wav");
	DSBuffer[ALADDIN_INJURED] = LoadWaveToSoundBuffer((char*)"Resources/Sounds/AladdinHurt.wav");
	DSBuffer[ALADDIN_OOF] = LoadWaveToSoundBuffer((char*)"Resources/Sounds/AladdinOof.wav");
	DSBuffer[ALADDIN_PUSH] = LoadWaveToSoundBuffer((char*)"Resources/Sounds/AladdinPush.wav");
	DSBuffer[SKELETON_COLIISION] = LoadWaveToSoundBuffer((char*)"Resources/Sounds/SkeletonCollision.wav");
	DSBuffer[APPLE_EXPLOSIVE] = LoadWaveToSoundBuffer((char*)"Resources/Sounds/AppleExplosive.wav");
	DSBuffer[MONKEY] = LoadWaveToSoundBuffer((char*)"Resources/Sounds/Monkey.wav");
	DSBuffer[ENEMY_EXPLOSIVE] = LoadWaveToSoundBuffer((char*)"Resources/Sounds/EnemyExplosive.wav");
	DSBuffer[JAFAR_TRACTOR] = LoadWaveToSoundBuffer((char*)"Resources/Sounds/JafarTractor1.wav");
	DSBuffer[JAFAR_INJURED] = LoadWaveToSoundBuffer((char*)"Resources/Sounds/JafarInjured.wav");
	DSBuffer[JAFAR_DESTROY] = LoadWaveToSoundBuffer((char*)"Resources/Sounds/JafarDestroy.wav");
	DSBuffer[PEDDLE_SHOP] = LoadWaveToSoundBuffer((char*)"Resources/Sounds/PeddlerShop.wav");

	if (!DSBuffer)
	{
		MessageBox(NULL, "Unable to load sound", "ERROR", MB_OK);
	}
}

bool Sound::InitDirectSound(HWND hwnd)
{
	HRESULT res;
	res = DirectSoundCreate8(NULL, &g_pDS, NULL);
	if (FAILED(res))
		return false;

	res = g_pDS->SetCooperativeLevel(hwnd, DSSCL_PRIORITY);
	if (FAILED(res))
		return false;

	currentBackground = -1;
}

LPDIRECTSOUNDBUFFER Sound::LoadWaveToSoundBuffer(char* wavFilename)
{
	LPDIRECTSOUNDBUFFER sound = NULL;
	CWaveFile* wavFile;
	HRESULT res;

	wavFile = new CWaveFile();
	wavFile->Open(wavFilename, NULL, WAVEFILE_READ);

	DSBUFFERDESC dsbd;
	ZeroMemory(&dsbd, sizeof(DSBUFFERDESC));
	dsbd.dwSize = sizeof(DSBUFFERDESC);
	dsbd.dwFlags = 0;
	dsbd.dwBufferBytes = wavFile->GetSize();
	dsbd.guid3DAlgorithm = GUID_NULL;
	dsbd.lpwfxFormat = wavFile->m_pwfx;

	res = g_pDS->CreateSoundBuffer(&dsbd, &sound, NULL);

	if (FAILED(res)) {
		MessageBox(NULL, "unable to create sound buffer", "ERROR", MB_OK);
		return NULL;
	}
	VOID* pDSLockedBuffer = NULL; // Pointer to locked buffer memory
	DWORD   dwDSLockedBufferSize = 0;    // Size of the locked DirectSound buffer
	DWORD   dwWavDataRead = 0;    // Amount of data read from the wav file 

	res = sound->Lock(0, wavFile->GetSize(),
		&pDSLockedBuffer, &dwDSLockedBufferSize,
		NULL, NULL, 0L);

	if (FAILED(res))
		return NULL;
	// Reset the wave file to the beginning 
	wavFile->ResetFile();

	// Read the wave file
	res = wavFile->Read((BYTE*)pDSLockedBuffer,
		dwDSLockedBufferSize,
		&dwWavDataRead);

	// Check to make sure that this was successful
	if (FAILED(res))
		return NULL;

	// Check to make sure the wav file is not empty
	if (dwWavDataRead == 0)
	{
		// Wav is blank, so just fill with silence
		FillMemory((BYTE*)pDSLockedBuffer,
			dwDSLockedBufferSize,
			(BYTE)(wavFile->m_pwfx->wBitsPerSample == 8 ? 128 : 0));
	}

	else if (dwWavDataRead < dwDSLockedBufferSize)
	{
		// Don't repeat the wav file, just fill in silence 
		FillMemory((BYTE*)pDSLockedBuffer + dwWavDataRead,
			dwDSLockedBufferSize - dwWavDataRead,
			(BYTE)(wavFile->m_pwfx->wBitsPerSample == 8 ? 128 : 0));
	}

	// Unlock the buffer, we don't need it anymore.
	sound->Unlock(pDSLockedBuffer, dwDSLockedBufferSize, NULL, 0);

	// Clean up
	delete wavFile;
	wavFile = NULL;

	return sound;
}

void Sound::PlayFX(int id)
{
	long volumn = (0.1) / 100 * (-DSBVOLUME_MIN) + DSBVOLUME_MIN;
	if (DSBuffer[id]->GetCurrentPosition(NULL, NULL) != 0)
		DSBuffer[id]->SetCurrentPosition(0);
	if (id == JAFAR_TRACTOR)
		DSBuffer[id]->SetVolume(volumn);
	DSBuffer[id]->Play(0, 0, 0);
}

void Sound::StopFX(int id)
{
	DSBuffer[id]->Stop();
}

void Sound::PlayMusic(int id)
{
	StopMusic();
	currentBackground = id;
	DSBuffer[currentBackground]->Play(0, 0, DSBPLAY_LOOPING);
}

void Sound::StopMusic()
{
	if (currentBackground != -1)
		DSBuffer[currentBackground]->Stop();
}
