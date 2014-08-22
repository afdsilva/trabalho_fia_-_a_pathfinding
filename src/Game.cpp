/*
 * Game.cpp
 *
 *  Created on: 18/06/2013
 *      Author: andref
 */

#include "Game.hpp"

#include <iostream>

int main(int argc, char **argv) {

	Game aPath ;
	return aPath.GameExec();
}

Game::Game() {
}

int Game::GameExec() {
	int retorno = 0;
	try {
		if (GameInit() == false)
			throw 1;

		sf::Event event;
		while(this->window.isOpen()) {
			while(this->window.pollEvent(event)) {
				// Close window : exit
				GameEvent(&event);
			}
			GameLoop();
			GameRender();
		}
		retorno = EXIT_SUCCESS;
	} catch(int e) {
		retorno = EXIT_FAILURE;
	}

	GameCleanup();

	return retorno;
}

bool Game::GameInit() {
	bool retorno;
	try {
		//1150, 640 - tamanho sem overlay
		this->window.create(sf::VideoMode(1150, 640), "A Pathfinding");

		CStateManager::SetActiveState(STATE_SPLASH);

		retorno = true;
	} catch(int e) {
		retorno = false;
	}
	return retorno;
}

void Game::GameEvent(sf::Event * event) {
	CEvent::GameEvent(event);
	CStateManager::GetActiveState()->GameEvent(event);
}

void Game::Closed() {
	this->window.close();
}
void Game::KeyPressed(sf::Event::KeyEvent keyEvent) {
}
void Game::KeyReleased(sf::Event::KeyEvent keyEvent) {

}

void Game::GameLoop() {
	CFPS::FPSControl.OnLoop();
	CStateManager::GetActiveState()->OnLoop();
	this->window.setFramerateLimit(CFPS::FPSControl.maxFrame);


}
void Game::GameRender() {
	CStateManager::GetActiveState()->OnRender(&window);
}
void Game::GameCleanup() {

}
