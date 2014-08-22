/*
 * CStateGame.hpp
 *
 *  Created on: 21/07/2013
 *      Author: andref
 */

#ifndef CSTATEGAME_HPP_
#define CSTATEGAME_HPP_

#include <SFML/Graphics.hpp>
#include "CState.hpp"
#include "CEntity.hpp"
#include "CTileMap.hpp"

class CStateGame: public CState {
private:
	static CStateGame instance;
private:
	CStateGame();

	CPlayer p1;
	sf::Vector2i lastMousePosition;
	sf::Vector2f currentMousePoints;
	bool leftButton;
	bool rightButton;
	bool samePosition;


public:
	void OnActivation();
	void OnDeactivation();
	void OnLoop();
	void OnRender(sf::RenderWindow * window);

public:
	static CStateGame * GetIntance();

	void KeyPressed(sf::Event::KeyEvent keyEvent);
	void MouseMoved(sf::Event::MouseMoveEvent mouseMoveEvent);
	void MouseButtonPressed(sf::Event::MouseButtonEvent mouseButtonEvent);
	void MouseButtonReleased(sf::Event::MouseButtonEvent mouseButtonEvent);
};

#endif /* CSTATEGAME_HPP_ */
