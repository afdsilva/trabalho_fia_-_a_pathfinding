/*
 * CEvent.cpp
 *
 *  Created on: 18/06/2013
 *      Author: andref
 */

#include "CEvent.hpp"

CEvent::CEvent() {

}
CEvent::~CEvent() {
}

void CEvent::GameEvent(sf::Event * event) {
	if (event->type == sf::Event::Closed) {
		Closed();
	}
	if (event->type == sf::Event::Resized) {
		Resized(event->size);
	}
	if (event->type == sf::Event::LostFocus) {
		LostFocus();
	}
	if (event->type == sf::Event::GainedFocus) {
		GainedFocus();
	}
	if (event->type == sf::Event::TextEntered) {
		TextEntered(event->text);
	}
	if (event->type == sf::Event::KeyPressed) {
		KeyPressed(event->key);
	}
	if (event->type == sf::Event::KeyReleased) {
		KeyReleased(event->key);
	}
	if (event->type == sf::Event::MouseWheelMoved) {
		MouseWheelMoved(event->mouseWheel);
	}
	if (event->type == sf::Event::MouseButtonPressed) {
		MouseButtonPressed(event->mouseButton);
	}
	if (event->type == sf::Event::MouseButtonReleased) {
		MouseButtonReleased(event->mouseButton);
	}
	if (event->type == sf::Event::MouseMoved) {
		MouseMoved(event->mouseMove);
	}
	if (event->type == sf::Event::MouseEntered) {
		MouseEntered();
	}
	if (event->type == sf::Event::MouseLeft) {
		MouseLeft();
	}
	if (event->type == sf::Event::JoystickButtonPressed) {
		JoystickButtonPressed(event->joystickButton);
	}
	if (event->type == sf::Event::JoystickButtonReleased) {
		JoystickButtonReleased(event->joystickButton);
	}
	if (event->type == sf::Event::JoystickMoved) {
		JoystickMoved(event->joystickMove);
	}
	if (event->type == sf::Event::JoystickConnected) {
		JoystickConnected(event->joystickConnect);
	}
	if (event->type == sf::Event::JoystickDisconnected) {
		JoystickDisconnected(event->joystickConnect);
	}
}
void CEvent::Closed() {
}
void CEvent::Resized(sf::Event::SizeEvent size) {
}
void CEvent::LostFocus() {
}
void CEvent::GainedFocus() {
}
void CEvent::TextEntered(sf::Event::TextEvent text) {
}
void CEvent::KeyPressed(sf::Event::KeyEvent keyEvent) {
}
void CEvent::KeyReleased(sf::Event::KeyEvent keyEvent) {
}
void CEvent::MouseWheelMoved(sf::Event::MouseWheelEvent mouseWheelEvent) {
}
void CEvent::MouseButtonPressed(sf::Event::MouseButtonEvent mouseButtonEvent) {
}
void CEvent::MouseButtonReleased(sf::Event::MouseButtonEvent mouseButtonEvent) {
}
void CEvent::MouseMoved(sf::Event::MouseMoveEvent mouseMoveEvent) {
}
void CEvent::MouseEntered() {
}
void CEvent::MouseLeft() {
}
void CEvent::JoystickButtonPressed(sf::Event::JoystickButtonEvent joyButtonEvent) {
}
void CEvent::JoystickButtonReleased(sf::Event::JoystickButtonEvent joyButtonEvent) {
}
void CEvent::JoystickMoved(sf::Event::JoystickMoveEvent joyMoveEvent) {
}
void CEvent::JoystickConnected(sf::Event::JoystickConnectEvent joyConnectEvent) {
}
void CEvent::JoystickDisconnected(sf::Event::JoystickConnectEvent joyConnectEvent) {
}
