/*
 * CStateMenu.cpp
 *
 *  Created on: 01/07/2013
 *      Author: andref
 */

#include "CStateMenu.hpp"
#include "CStateManager.hpp"
#include <iostream>

CStateMenu CStateMenu::instance;

CStateMenu::CStateMenu() {
}

void CStateMenu::OnActivation() {
	try {
		std::string fontName = "fonts/Serious-1.ttf";
		sf::Font * font = new sf::Font();
		CText * menuText = new CText();
		CButton * jogoBMenu = new CButton();
		CButton * jogo2BMenu = new CButton();
		CButton * exitBMenu = new CButton();

		if (!font->loadFromFile(fontName))
			throw 1;

		menuText->setPosition(10,10);
		menuText->load("Trabalhos \nFundamentos de Inteligencia Artificial",*font,32);
		CText::textList.push_back(menuText);
		jogoBMenu->setPosition(menuText->getPosition().x + 30, menuText->getPosition().y + 80);
		jogoBMenu->load("Jogar A*",*font,28);
		jogoBMenu->SetColor(sf::Color::Black);
		jogoBMenu->SetBackground(sf::Color::White);
		jogoBMenu->SetActionHover(STATE_GAME);

		CButton::buttonList.push_back(jogoBMenu);
		jogo2BMenu->setPosition(jogoBMenu->getPosition().x, jogoBMenu->getPosition().y + 40);
		jogo2BMenu->load("Jogar Conecta 4",*font,28);
		jogo2BMenu->SetColor(sf::Color::Black);
		jogo2BMenu->SetBackground(sf::Color::White);
		jogo2BMenu->SetActionHover(STATE_GAME2);

		CButton::buttonList.push_back(jogo2BMenu);

		exitBMenu->setPosition(jogo2BMenu->getPosition().x, jogo2BMenu->getPosition().y + 40);
		exitBMenu->load("Sair",*font,28);
		exitBMenu->SetColor(sf::Color::Black);
		exitBMenu->SetBackground(sf::Color::White);
		exitBMenu->SetActionHover(STATE_NONE);
		CButton::buttonList.push_back(exitBMenu);

	} catch(int e) {
		std::cout << "Deu erro D:" << std::endl;
	}
}

void CStateMenu::OnDeactivation() {
	for (unsigned int i = 0; i < CEntity::entityList.size(); i++) {
		if (!CEntity::entityList[i])
			continue;
		CEntity::entityList[i]->Unload();
	}
	CEntity::entityList.clear();
	for (unsigned int i = 0; i < CText::textList.size(); i++) {
		if (!CText::textList[i])
			continue;
		CText::textList[i]->Unload();
	}
	for (unsigned int i = 0; i < CButton::buttonList.size(); i++) {
		if (!CButton::buttonList[i])
			continue;
		CButton::buttonList[i]->Unload();
	}
	CButton::buttonList.clear();

//	this->jogoBMenu.~Drawable();
}

void CStateMenu::OnLoop() {
	for (unsigned int i = 0; i < CEntity::entityList.size(); i++) {
		if (!CEntity::entityList[i])
			continue;
		CEntity::entityList[i]->OnLoop();
	}
	for (unsigned int i = 0; i < CText::textList.size(); i++) {
		if (!CText::textList[i])
			continue;
		CText::textList[i]->OnLoop();
	}
	for (unsigned int i = 0; i < CButton::buttonList.size(); i++) {
		if (!CButton::buttonList[i])
			continue;
		CButton::buttonList[i]->OnLoop();
	}

}

void CStateMenu::OnRender(sf::RenderWindow * window) {

	for (unsigned int i = 0; i < CEntity::entityList.size(); i++) {
		if (!CEntity::entityList[i])
			continue;
		window->draw(*CEntity::entityList[i]);
	}
	for (unsigned int i = 0; i < CText::textList.size(); i++) {
		if (!CText::textList[i])
			continue;
		window->draw(*CText::textList[i]);
	}
	for (unsigned int i = 0; i < CButton::buttonList.size(); i++) {
		if (!CButton::buttonList[i])
			continue;
		window->draw(*CButton::buttonList[i]);
	}

	window->display();
	window->clear(sf::Color::Black);
}

CStateMenu * CStateMenu::GetIntance() {
	return & instance;
}
void CStateMenu::MouseMoved(sf::Event::MouseMoveEvent mouseMoveEvent) {
	for (unsigned int i = 0; i < CButton::buttonList.size(); i++) {
		if (!CButton::buttonList[i])
			continue;
		CButton::buttonList[i]->Highlight(sf::Vector2f(mouseMoveEvent.x,mouseMoveEvent.y));
	}
}
void CStateMenu::MouseButtonPressed(sf::Event::MouseButtonEvent mouseButtonEvent) {
	for (unsigned int i = 0; i < CButton::buttonList.size(); i++) {
		if (!CButton::buttonList[i])
			continue;
		if (CButton::buttonList[i]->OnHover(sf::Vector2f(mouseButtonEvent.x,mouseButtonEvent.y))) {
			CStateManager::SetActiveState(CButton::buttonList[i]->GetActionHover());
		}
	}
}
void CStateMenu::MouseButtonReleased(sf::Event::MouseButtonEvent mouseButtonEvent) {
}
void CStateMenu::KeyPressed(sf::Event::KeyEvent keyEvent) {
	if (keyEvent.code == sf::Keyboard::Escape)
		CStateManager::SetActiveState(STATE_NONE);
}

void CStateMenu::JoystickButtonPressed(sf::Event::JoystickButtonEvent joyButtonEvent) {
	std::cout << "Joystick Numero: " << joyButtonEvent.joystickId;
	std::cout << " Botao: " << joyButtonEvent.button << std::endl;
}
void CStateMenu::JoystickButtonReleased(sf::Event::JoystickButtonEvent joyButtonEvent) {
}
void CStateMenu::JoystickMoved(sf::Event::JoystickMoveEvent joyMoveEvent) {
}
void CStateMenu::JoystickConnected(sf::Event::JoystickConnectEvent joyConnectEvent) {
	std::cout << "Joystick Encontrado" << std::endl;
	unsigned int buttons = sf::Joystick::getButtonCount(0);
	std::cout << "Numero de Botoes: " << buttons << std::endl;
}
void CStateMenu::JoystickDisconnected(sf::Event::JoystickConnectEvent joyConnectEvent) {
}
