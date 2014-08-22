/*
 * CEvent.hpp
 *
 *  Created on: 18/06/2013
 *      Author: andref
 */

#ifndef CEVENT_HPP_
#define CEVENT_HPP_

#include <SFML/Window/Event.hpp>

class CEvent {
public:
	CEvent();
	virtual ~CEvent();

	virtual void GameEvent(sf::Event * event);

	virtual void Closed();
	virtual void Resized(sf::Event::SizeEvent size);
	virtual void LostFocus();
	virtual void GainedFocus();
	virtual void TextEntered(sf::Event::TextEvent text);
	virtual void KeyPressed(sf::Event::KeyEvent keyEvent);
	virtual void KeyReleased(sf::Event::KeyEvent keyEvent);
	virtual void MouseWheelMoved(sf::Event::MouseWheelEvent mouseWheelEvent);
	virtual void MouseButtonPressed(sf::Event::MouseButtonEvent mouseButtonEvent);
	virtual void MouseButtonReleased(sf::Event::MouseButtonEvent mouseButtonEvent);
	virtual void MouseMoved(sf::Event::MouseMoveEvent mouseMoveEvent);
	virtual void MouseEntered();
	virtual void MouseLeft();
	virtual void JoystickButtonPressed(sf::Event::JoystickButtonEvent joyButtonEvent);
	virtual void JoystickButtonReleased(sf::Event::JoystickButtonEvent joyButtonEvent);
	virtual void JoystickMoved(sf::Event::JoystickMoveEvent joyMoveEvent);
	virtual void JoystickConnected(sf::Event::JoystickConnectEvent joyConnectEvent);
	virtual void JoystickDisconnected(sf::Event::JoystickConnectEvent joyConnectEvent);

};

#endif /* CEVENT_HPP_ */
