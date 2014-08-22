/*
 * CStateIntro.cpp
 *
 *  Created on: 19/06/2013
 *      Author: andref
 */

#include "CStateIntro.hpp"
#include "CStateManager.hpp"
#include <iostream>

CStateIntro CStateIntro::instance;

CStateIntro::CStateIntro() {

}

void CStateIntro::OnActivation() {
	try {
		tempoInicio.restart();

		this->logo.Structure(sf::Vector2f(1150,640));
		this->logo.InitialPos(0,0);
		this->logo.LoadTexture("img/mAle_-_logo.png");

	} catch(int e) {

	}
}

void CStateIntro::OnDeactivation() {
	this->logo.Unload();
}

void CStateIntro::OnLoop() {
	sf::Time elapsed1 = tempoInicio.getElapsedTime();
	//std::cout << "Na intro" << std::endl;
	if (elapsed1.asSeconds() > 3) {
		CStateManager::SetActiveState(STATE_MENU);
	}
}

void CStateIntro::OnRender(sf::RenderWindow * window) {
	window->clear();
	window->draw(this->logo);
	//Do something;
	window->display();
}

CStateIntro * CStateIntro::GetIntance() {
	return & instance;
}

void CStateIntro::KeyPressed(sf::Event::KeyEvent keyEvent) {
	CStateManager::SetActiveState(STATE_MENU);
}
