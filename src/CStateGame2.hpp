/*
 * CStateGame2.hpp
 *
 *  Created on: 20/08/2013
 *      Author: andref
 */

#ifndef CSTATEGAME2_HPP_
#define CSTATEGAME2_HPP_

#include <SFML/Graphics.hpp>
#include "CState.hpp"
#include "CEntity.hpp"

class CStateGame2: public CState  {
private:
	static CStateGame2 instance;

	sf::Clock clock;

	sf::Vector2i mousePos;
	bool leftClick;
	bool rightClick;
	bool middleClick;

	int selectedP1;
	int selectedP2;


public:
	void OnActivation();
	void OnDeactivation();
	void OnLoop();
	void OnRender(sf::RenderWindow * window);

public:
	static CStateGame2 * GetIntance();

	void KeyPressed(sf::Event::KeyEvent keyEvent);
	void MouseMoved(sf::Event::MouseMoveEvent mouseMoveEvent);
	void MouseButtonPressed(sf::Event::MouseButtonEvent mouseButtonEvent);
	void MouseButtonReleased(sf::Event::MouseButtonEvent mouseButtonEvent);
};

#endif /* CSTATEGAME2_HPP_ */
