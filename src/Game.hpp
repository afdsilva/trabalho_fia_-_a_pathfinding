/*
 * Game.hpp
 *
 *  Created on: 18/06/2013
 *      Author: andref
 */

#ifndef GAME_HPP_
#define GAME_HPP_

#include "CStateManager.hpp"
#include "CEvent.hpp"
#include "CFPS.hpp"

#include <SFML/Graphics.hpp>

class Game : public CEvent {
private:
	sf::RenderWindow splash;
	sf::RenderWindow window;

public:
	Game();
	int GameExec();

private:
	bool GameInit();
	void GameEvent(sf::Event * event);
		virtual void Closed();
		virtual void KeyPressed(sf::Event::KeyEvent keyEvent);
		virtual void KeyReleased(sf::Event::KeyEvent keyEvent);
	void GameLoop();
	void GameRender();
	void GameCleanup();

};

#endif /* GAME_HPP_ */
