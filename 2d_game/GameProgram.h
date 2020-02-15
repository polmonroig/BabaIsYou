#ifndef GAME_PROGRAM_H 
#define GAME_PROGRAM_H 

#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"


//Remove console (only works in Visual Studio)
// #pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")


#define TIME_PER_FRAME 1000.f / 60.f // Approx. 60 fps

class GameProgram {

public:

	void init(int argc, char** argv);


private:

	void runLoop();
	void glut(int argc, char** argv);
	void addCallbacks();

	static void keyboardDownCallback(unsigned char key, int x, int y);
	static void keyboardUpCallback(unsigned char key, int x, int y);
	static void specialDownCallback(int key, int x, int y);
	static void specialUpCallback(int key, int x, int y);
	static void motionCallback(int x, int y);
	static void mouseCallback(int button, int state, int x, int y);
	static void drawCallback();
	static void idleCallback();
	static int prevTime;
};


#endif 