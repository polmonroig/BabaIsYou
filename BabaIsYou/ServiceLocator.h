#ifndef SERVICE_LOCATOR_H
#define SERVICE_LOCATOR_H

#include "ShaderManager.h"
#include "AnimationsManager.h"


class ServiceLocator{

public:

	static ShaderManager* getShaderManager();
	static AnimationsManager* getAnimationsManager();
	static bool isGameEnd();
	static void endGame();


private:


	static bool gameEnd;
	static ShaderManager* shaders;
	static AnimationsManager* animations;

};



#endif