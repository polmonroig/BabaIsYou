#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"

 Game& Game::instance()
{
	static Game G;
	
	return G;
}

void Game::init()
{
	bPlay = true;
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearColor(0.094f, 0.094f, 0.129f, 1.0f);
	scene = new Scene();
	scene->init();
}

bool Game::update(int deltaTime){

	
	scene->update(deltaTime);

	
		
	return bPlay;
}

void Game::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	scene->render();
}

void Game::keyPressed(int key)
{
	if (key == 27) // Escape code
		bPlay = false;
	if (key == 'r')
		scene->restart();

	keys[key] = true;
}

void Game::keyReleased(int key){

	if (key == 13)scene->selectElement();
	keys[key] = false;
}

void Game::specialKeyPressed(int key){
	
	specialKeys[key] = true;
}

void Game::specialKeyReleased(int key){

	if (key == GLUT_KEY_RIGHT)
		scene->move(Direction(DirectionType::RIGHT));
	else if (key == GLUT_KEY_LEFT)
		scene->move(Direction(DirectionType::LEFT));
	else if (key == GLUT_KEY_UP)
		scene->move(Direction(DirectionType::UP));
	else if (key == GLUT_KEY_DOWN)
		scene->move(Direction(DirectionType::DOWN));
	specialKeys[key] = false;
}

void Game::mouseMove(int x, int y)
{
}

void Game::mousePress(int button){

}

void Game::mouseRelease(int button)
{
}

bool Game::getKey(int key) const
{
	return keys[key];
}

bool Game::getSpecialKey(int key) const
{
	
	return specialKeys[key];
}





