#pragma once
#include <Windows.h>
#include <string>
#include "Exception.h"

enum class SOUND { JUMP = 0, ADD_SCORE_G =  1, ADD_SCORE_B = 2,  DEAL_DMG = 3, SELECT = 4 };

struct Sound
{
	static void Play(const std::string& filename, const HMODULE& hmod = NULL, const DWORD& fdwSound = SND_ASYNC | SND_ALIAS);
	static void Stop();
	static std::string GetSoundFilename(SOUND soundName);
};

