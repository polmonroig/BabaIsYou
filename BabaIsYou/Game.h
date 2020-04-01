#ifndef _GAME_INCLUDE
#define _GAME_INCLUDE

// Game is a singleton (a class with a single instance) that represents our whole application


#include "Scene.h"
#include "Direction.h"

class Scene;

class Game{

public:


	static Game& instance();



	void init();
	bool update(int deltaTime);
	void render();


	// Input callback methods
	void keyPressed(int key);
	void keyReleased(int key);
	void specialKeyPressed(int key);
	void specialKeyReleased(int key);
	void mouseMove(int x, int y);
	void mousePress(int button);
	void mouseRelease(int button);
	bool getKey(int key) const;
	bool getSpecialKey(int key) const;

	

private:

	
	int inputDelay;
	int currentInput;
	bool bPlay;                       // Continue to play game?
	Scene* scene;                      // Scene to render
	bool keys[256], specialKeys[256]; // Store key states so that 
									  // we can have access at any time

};


#endif // _GAME_INCLUDE


