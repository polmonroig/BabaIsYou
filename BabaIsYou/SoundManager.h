#ifndef SOUND_MANAGER_H
#define SOUND_MANAGER_H

#include <vector>
#include <string>
#include <irrKlang.h>
#pragma comment(lib, "irrKlang.lib")


class SoundManager{

public:
	void init();

	void playLoad();

	void playMove();

	void playWin();

	void playReset();

	void playBackground();

	void stopBackground();



private: 
	std::vector<std::string> BABA_MOVE_SOUND = { "sound/043.ogg", "sound/044.ogg", "sound/045.ogg", "sound/046.ogg" };
	std::string  WIN_SOUND = "sound/042.ogg";
	std::string  RESET_SOUND = "sound/085.ogg";
	std::string  LOAD_SOUND = "sound/026.ogg"; // 26
	std::string  THEME_SOUND = "sound/theme_soundtrack.mp3";


	bool move_played;

	static irrklang::ISoundEngine* engine;
	static  irrklang::ISound* backgroundMusic;
};


#endif 

