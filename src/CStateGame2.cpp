/*
 * CStateGame2.cpp
 *
 *  Created on: 20/08/2013
 *      Author: andref
 */

#include "CStateGame2.hpp"
#include "CStateManager.hpp"

#include "CBoardMap.hpp"

CStateGame2 CStateGame2::instance;

void CStateGame2::OnActivation() {
	try {
		clock.restart();
		std::string fontName = "fonts/Serious-1.ttf";
		sf::Font * font = new sf::Font();

		if (!font->loadFromFile(fontName))
			throw 1;

		CText * titleText = new CText();
		titleText->id = 0;
		titleText->setPosition(10,10);
		titleText->load("Conecta 4",*font,32);
		CText::textList.push_back(titleText);

		CText * turnText = new CText();
		turnText->id = 1;
		turnText->setPosition(700,10);

		turnText->load("Turno Player 1",*font,32);

		CText::textList.push_back(turnText);

		CButton * p1Button = new CButton();
		p1Button->id = 0;
		p1Button->setPosition(300,5);
		p1Button->load("___P1___",*font,28);
		p1Button->SetColor(sf::Color::Black);
		p1Button->SetBackground(sf::Color::Yellow);
		p1Button->SetActionHover(PLAYER_1);
		CButton::buttonList.push_back(p1Button);

		CButton * p2Button = new CButton();
		p2Button->id = 1;
		p2Button->setPosition(p1Button->getPosition().x+160,p1Button->getPosition().y);
		p2Button->load("___P2___",*font,28);
		p2Button->SetColor(sf::Color::Black);
		p2Button->SetBackground(sf::Color::Yellow);
		p2Button->SetActionHover(PLAYER_2);
		CButton::buttonList.push_back(p2Button);

		CButton * ia1Button = new CButton();
		ia1Button->id = 2;
		ia1Button->setPosition(p1Button->getPosition().x-5,p1Button->getPosition().y+30);
		ia1Button->load("___IA1___",*font,28);
		ia1Button->SetColor(sf::Color::Black);
		ia1Button->SetBackground(sf::Color::White);
		ia1Button->SetActionHover(IA_1);
		CButton::buttonList.push_back(ia1Button);

		CButton * ia2Button = new CButton();
		ia2Button->id = 3;
		ia2Button->setPosition(p1Button->getPosition().x+155,p1Button->getPosition().y+30);
		ia2Button->load("___IA2___",*font,28);
		ia2Button->SetColor(sf::Color::Black);
		ia2Button->SetBackground(sf::Color::White);
		ia2Button->SetActionHover(IA_2);
		CButton::buttonList.push_back(ia2Button);

		CButton * newGameButton = new CButton();
		newGameButton->id = 4;
		newGameButton->setPosition(10,40);
		newGameButton->load("_Novo Jogo_",*font,28);
		newGameButton->SetColor(sf::Color::Black);
		newGameButton->SetBackground(sf::Color::White);
		newGameButton->SetActionHover(NEW_GAME);
		CButton::buttonList.push_back(newGameButton);

		this->selectedP1 = PLAYER_1;
		this->selectedP2 = PLAYER_2;

		this->leftClick = false;
		this->rightClick = false;
		this->middleClick = false;
		CBoardMap::board = CBoardMap();

		CBoardMap::board.NewGame();

		CBoardMap::board.player = PLAYER_1;
		sf::Vector2f boardSize(800,560);
		sf::Vector2i boardTile(10,7);
		CBoardMap::board.Structure(boardSize,boardTile);
		float halfWidth = 1150 / 2;
		float halfHeight = 640 - (boardSize.y / 2);
		CBoardMap::board.setPosition(halfWidth - boardSize.x / 2 ,halfHeight - boardSize.y / 2);


	} catch (int e) {
		return;
	}
}

void CStateGame2::OnDeactivation() {
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
}

void CStateGame2::OnLoop() {
	for (unsigned int i = 0; i < CEntity::entityList.size(); i++) {
		if (!CEntity::entityList[i])
			continue;
		CEntity::entityList[i]->OnLoop();
	}
	for (unsigned int i = 0; i < CText::textList.size(); i++) {
		if (!CText::textList[i])
			continue;
		CText::textList[i]->OnLoop();
		if (CText::textList[i]->id == 1) {
			if (CBoardMap::board.playerWinner == 0) {
				if (CBoardMap::board.player == PLAYER_1)
					CText::textList[i]->SetText("Turno Player 1");
				if (CBoardMap::board.player == PLAYER_2)
					CText::textList[i]->SetText("Turno Player 2");
			} else {
				if (CBoardMap::board.playerWinner == PLAYER_1)
					CText::textList[i]->SetText("Jogador 1 Vencedor");
				if (CBoardMap::board.playerWinner == PLAYER_2)
					CText::textList[i]->SetText("Jogador 2 Vencedor");
			}
		}
	}
	for (unsigned int i = 0; i < CButton::buttonList.size(); i++) {
		if (!CButton::buttonList[i])
			continue;
		if (CButton::buttonList[i]->id == 0) {
			if (this->selectedP1 == PLAYER_1)
				CButton::buttonList[i]->SetBackground(sf::Color::Yellow);
			else
				CButton::buttonList[i]->SetBackground(sf::Color::White);
		}
		if (CButton::buttonList[i]->id == 1) {
			if (this->selectedP2 == PLAYER_2)
				CButton::buttonList[i]->SetBackground(sf::Color::Yellow);
			else
				CButton::buttonList[i]->SetBackground(sf::Color::White);
		}
		if (CButton::buttonList[i]->id == 2) {
			if (this->selectedP1 == IA_1)
				CButton::buttonList[i]->SetBackground(sf::Color::Yellow);
			else
				CButton::buttonList[i]->SetBackground(sf::Color::White);
		}
		if (CButton::buttonList[i]->id == 3) {
			if (this->selectedP2 == IA_2)
				CButton::buttonList[i]->SetBackground(sf::Color::Yellow);
			else
				CButton::buttonList[i]->SetBackground(sf::Color::White);
		}
		CButton::buttonList[i]->OnLoop();
	}

	if (this->mousePos != sf::Vector2i(-1,-1)) {
		CBoardMap::board.ColorBoard();
		//CBoardMap::board.HighlightRow(this->mousePos);
		if (CBoardMap::board.playerWinner == NO_PLAYER) {

			if (CBoardMap::board.player == PLAYER_1) {
				if (this->selectedP1 == PLAYER_1) {
					if (this->leftClick) {
						this->leftClick = false;
						clock.restart();
						CBoardMap::board.PlayerTurn(this->mousePos.x);
					}
				} else if (this->selectedP1 == IA_1) {
					if (clock.getElapsedTime().asSeconds() > 1) {
						clock.restart();
						CBoardMap::board.IATurn(CBoardMap::board.player);
					}
				}
			} else if (CBoardMap::board.player == PLAYER_2) {
				if (this->selectedP2 == PLAYER_2) {
					if (this->leftClick) {
						this->leftClick = false;
						clock.restart();
						CBoardMap::board.PlayerTurn(this->mousePos.x);
					}
				} else if (this->selectedP2 == IA_2) {
					if (clock.getElapsedTime().asSeconds() > 1) {
						clock.restart();
						CBoardMap::board.IATurn(CBoardMap::board.player);
					}
				}
			}

		}
		//std::cout << "this->mousePos: " << this->mousePos.x << " " << this->mousePos.y << std::endl;
	}
	for (unsigned int i = 0; i < CEntity::entityList.size(); i++) {
		if (!CEntity::entityList[i])
			continue;
		CEntity::entityList[i]->OnLoop();
	}
}

void CStateGame2::OnRender(sf::RenderWindow * window) {

	window->draw(CBoardMap::board);
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

CStateGame2 * CStateGame2::GetIntance() {
	return & instance;
}
void CStateGame2::MouseMoved(sf::Event::MouseMoveEvent mouseMoveEvent) {
	sf::Vector2f mouseCords(mouseMoveEvent.x,mouseMoveEvent.y);
	this->mousePos = sf::Vector2i(CBoardMap::board.MapToPos(mouseCords));
	for (unsigned int i = 0; i < CButton::buttonList.size(); i++) {
		if (!CButton::buttonList[i])
			continue;
		CButton::buttonList[i]->Highlight(sf::Vector2f(mouseMoveEvent.x,mouseMoveEvent.y));
	}
}
void CStateGame2::MouseButtonPressed(sf::Event::MouseButtonEvent mouseButtonEvent) {
	if ( mouseButtonEvent.button == sf::Mouse::Left ) {
		this->leftClick = true;
	}
	if ( mouseButtonEvent.button == sf::Mouse::Right ) {
		this->rightClick = true;
	}
	if ( mouseButtonEvent.button == sf::Mouse::Middle ) {
		this->middleClick = true;
	}
	for (unsigned int i = 0; i < CButton::buttonList.size(); i++) {
		if (!CButton::buttonList[i])
			continue;
		if (CButton::buttonList[i]->OnHover(sf::Vector2f(mouseButtonEvent.x,mouseButtonEvent.y))) {
			if (CButton::buttonList[i]->GetActionHover() == PLAYER_1)
				this->selectedP1 = PLAYER_1;
			if (CButton::buttonList[i]->GetActionHover() == PLAYER_2)
				this->selectedP2 = PLAYER_2;
			if (CButton::buttonList[i]->GetActionHover() == IA_1)
				this->selectedP1 = IA_1;
			if (CButton::buttonList[i]->GetActionHover() == IA_2)
				this->selectedP2 = IA_2;
			if (CButton::buttonList[i]->GetActionHover() == NEW_GAME) {
				CBoardMap::board = CBoardMap();

				CBoardMap::board.NewGame();

				CBoardMap::board.player = PLAYER_1;
				sf::Vector2f boardSize(800,560);
				sf::Vector2i boardTile(10,7);
				CBoardMap::board.Structure(boardSize,boardTile);
				float halfWidth = 1150 / 2;
				float halfHeight = 640 - (boardSize.y / 2);
				CBoardMap::board.setPosition(halfWidth - boardSize.x / 2 ,halfHeight - boardSize.y / 2);
			}
		}
	}
}
void CStateGame2::MouseButtonReleased(sf::Event::MouseButtonEvent mouseButtonEvent) {
	if ( mouseButtonEvent.button == sf::Mouse::Left ) {
		this->leftClick = false;
	}
	if ( mouseButtonEvent.button == sf::Mouse::Right ) {
		this->rightClick = false;
	}
	if ( mouseButtonEvent.button == sf::Mouse::Middle ) {
		this->middleClick = false;
	}
}
void CStateGame2::KeyPressed(sf::Event::KeyEvent keyEvent) {
	if (keyEvent.code == sf::Keyboard::Escape)
		CStateManager::SetActiveState(STATE_MENU);
	//CStateManager::SetActiveState(STATE_NONE);

}
