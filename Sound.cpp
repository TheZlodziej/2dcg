#include "Sound.h"

#include <thread>
void Sound::Play(const std::string& filename, const HMODULE& hmod, const DWORD& fdwSound)
{
	//convert std::string to LPCWSTR
	std::wstring temp(filename.begin(), filename.end());
	LPCWSTR convertedFilename = temp.c_str();

	if (!PlaySound(convertedFilename, hmod, fdwSound))
	{
		throw new Exception(5, "[SOUND] Sound playback error.");
	}
}

void Sound::Stop()
{
	PlaySound(NULL, 0, 0);
}

std::string Sound::GetSoundFilename(SOUND soundName)
{
	switch (soundName)
	{
	case SOUND::JUMP:
		return "sounds/jump.wav";

	case SOUND::ADD_SCORE_G:
		return "sounds/add_score_g.wav";

	case SOUND::ADD_SCORE_B:
		return "sounds/add_score_b.wav";

	case SOUND::DEAL_DMG:
		return "sounds/deal_dmg.wav";

	case SOUND::SELECT:
		return "sounds/select.wav";

	case SOUND::WIN:
		return "sounds/win.wav";

	case SOUND::LOSE:
		return "sounds/lose.wav";

	default:
		throw new Exception(5, "[SOUND] Unknown sound name.");
		break;
	}
}