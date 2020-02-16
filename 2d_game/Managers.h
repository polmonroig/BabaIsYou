#ifndef MANAGERS_H
#define MANAGERS_H

#include "AnimationsManager.h"
#include "ShaderManager.h"

// monostate class that contains the game managers

class Managers{

public:

	// Managers 
	static ShaderManager shaderManager;
	static AnimationsManager animationsManager;
	
};

#endif 

