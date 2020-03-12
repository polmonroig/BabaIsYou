#include "GameProgram.h"

// STATIC VARIABLES 
int GameProgram::prevTime;




// =============================
//       PUBLIC METHODS 
// =============================

void GameProgram::init(int argc, char** argv) {
	glut(argc, argv);
	addCallbacks();
	runLoop();
	

}

// =============================
//       PRIVATE METHODS 
// =============================

void GameProgram::runLoop() {
	// GLEW will take care of OpenGL extension functions
	glewExperimental = GL_TRUE;
	glewInit();

	// Game instance initialization
	Game::instance().init();
	GameProgram::prevTime = glutGet(GLUT_ELAPSED_TIME);
	// GLUT gains control of the application
	glutMainLoop();
}

void GameProgram::glut(int argc, char** argv) {
	// GLUT initialization
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(720, 720);

	glutCreateWindow(argv[0]);
}

void GameProgram::addCallbacks() {
	// add callbacks 
	glutDisplayFunc(drawCallback);
	glutIdleFunc(idleCallback);
	glutKeyboardFunc(keyboardDownCallback);
	glutKeyboardUpFunc(keyboardUpCallback);
	glutSpecialFunc(specialDownCallback);
	glutSpecialUpFunc(specialUpCallback);
	glutMouseFunc(mouseCallback);
	glutMotionFunc(motionCallback);
}


// =============================
//       STATIC CALLBACK METHODS 
// =============================

void GameProgram::keyboardDownCallback(unsigned char key, int x, int y){
	Game::instance().keyPressed(key);
}

// If a key is released this callback is called

void GameProgram::keyboardUpCallback(unsigned char key, int x, int y){
	Game::instance().keyReleased(key);
}

// If a special key is pressed this callback is called

void GameProgram::specialDownCallback(int key, int x, int y){
	Game::instance().specialKeyPressed(key);
}

// If a special key is released this callback is called

void GameProgram::specialUpCallback(int key, int x, int y){
	Game::instance().specialKeyReleased(key);
}

// Same for changes in mouse cursor position

void GameProgram::motionCallback(int x, int y)
{
	Game::instance().mouseMove(x, y);
}

// Same for mouse button presses or releases

void GameProgram::mouseCallback(int button, int state, int x, int y){
	if (state == GLUT_DOWN)
		Game::instance().mousePress(button);
	else if (state == GLUT_UP)
		Game::instance().mouseRelease(button);
}

void GameProgram::drawCallback(){
	Game::instance().render();
	glutSwapBuffers();
}

void  GameProgram::idleCallback(){
	int currentTime = glutGet(GLUT_ELAPSED_TIME);
	int deltaTime = currentTime - GameProgram::prevTime;

	if (deltaTime > TIME_PER_FRAME)
	{
		// Every time we enter here is equivalent to a game loop execution
		if (!Game::instance().update(deltaTime))
			exit(0);
		GameProgram::prevTime = currentTime;
		glutPostRedisplay();
	}
}