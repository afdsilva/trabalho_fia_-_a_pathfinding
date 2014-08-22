/*
 * CStateMenu.hpp
 *
 *  Created on: 01/07/2013
 *      Author: andref
 */

#ifndef CSTATEMENU_HPP_
#define CSTATEMENU_HPP_

#include <SFML/Graphics.hpp>
#include "CState.hpp"
#include "CEntity.hpp"
#include "CTileMap.hpp"

class CStateMenu : public CState {
private:
	static CStateMenu instance;
private:
	CStateMenu();

public:
	void OnActivation();
	void OnDeactivation();
	void OnLoop();
	void OnRender(sf::RenderWindow * window);

public:
	static CStateMenu * GetIntance();

	void KeyPressed(sf::Event::KeyEvent keyEvent);
	void MouseMoved(sf::Event::MouseMoveEvent mouseMoveEvent);
	void MouseButtonPressed(sf::Event::MouseButtonEvent mouseButtonEvent);
	void MouseButtonReleased(sf::Event::MouseButtonEvent mouseButtonEvent);

	void JoystickButtonPressed(sf::Event::JoystickButtonEvent joyButtonEvent);
	void JoystickButtonReleased(sf::Event::JoystickButtonEvent joyButtonEvent);
	void JoystickMoved(sf::Event::JoystickMoveEvent joyMoveEvent);
	void JoystickConnected(sf::Event::JoystickConnectEvent joyConnectEvent);
	void JoystickDisconnected(sf::Event::JoystickConnectEvent joyConnectEvent);


};

#endif /* CSTATEMENU_HPP_ */

