#include "SoundManager.h"

irrklang::ISoundEngine* SoundManager::engine;
irrklang::ISound* SoundManager::backgroundMusic;

void SoundManager::init() {

	if (!engine) {
		engine = irrklang::createIrrKlangDevice();
	}	
	move_played = false;
}


void SoundManager::playMove() {
	if (!move_played && engine) {
		engine->play2D(BABA_MOVE_SOUND[std::rand() % BABA_MOVE_SOUND.size()].c_str(), false);
		move_played = true;
	}
}

void SoundManager::playLoad() {
	if (engine)engine->play2D(LOAD_SOUND.c_str(), false);
}

void SoundManager::playWin() {
	if (engine)engine->play2D(WIN_SOUND.c_str(), false);
}

void SoundManager::playReset() {
	if (engine)engine->play2D(RESET_SOUND.c_str(), false);
}

void SoundManager::playBackground() {
	backgroundMusic = engine->play2D(THEME_SOUND.c_str(), true, false, true);

}


void SoundManager::stopBackground() {
	backgroundMusic->stop();
	backgroundMusic->drop();
}