/*
 * CStateGame.cpp
 *
 *  Created on: 21/07/2013
 *      Author: andref
 */

#include "CStateGame.hpp"
#include "CStateManager.hpp"

CStateGame CStateGame::instance;

CStateGame::CStateGame() {
	this->lastMousePosition = sf::Vector2i(-1,-1);
	this->leftButton = false;
	this->rightButton = false;

	this->currentMousePoints = sf::Vector2f(-1,-1);
	this->samePosition = false;

}

void CStateGame::OnActivation() {
	try {
		CPlayer newPlayer;
		p1 = newPlayer;

		std::vector<int> levelMap, collisionMap;
		levelMap.resize(100*100,0);
		collisionMap.resize(100*100,0);
		/**/
		const float level[] = {
				114,98.5,98.5,98.5,98.5,98.5,98.5,98.5,98.5,98.5,98.5,98.5,98.5,98.5,98.5,98.5,98.5,98.5,98.5,98.5,98.5,98.5,98.5,98.5,98.5,98.5,98.5,98.5,98.5,98.5,98.5,98.5,98.5,98.5,98.5,115,
				114, 131, 130, 131, 130, 131, 130, 131, 130, 131, 130, 131, 130, 131, 130, 131, 130, 131, 130, 131, 130, 131, 130, 131, 130, 131, 130, 131, 130, 131, 130, 131, 130, 131, 130,115,
				114,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,115,
				114,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,115,
				114,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,115,
				114,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,115,
				114,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,115,
				114,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,115,
				114,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,115,
				114,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,115,
				114,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,115,
				114,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,115,
				114,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,115,
				114,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,115,
				114,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,115,
				114,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,115,
				114,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,115,
				114,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,115,
				114,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,84.5,115,
				114,98.5,98.5,98.5,98.5,98.5,98.5,98.5,98.5,98.5,98.5,98.5,98.5,98.5,98.5,98.5,98.5,98.5,98.5,98.5,98.5,98.5,98.5,98.5,98.5,98.5,98.5,98.5,98.5,98.5,98.5,98.5,98.5,98.5,98.5,115,
		};
		const int collision[] = {
				1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
				1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
				1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
				1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
				1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
				1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
				1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
				1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
				1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
				1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
				1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
				1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
				1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
				1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
				1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
				1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
				1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
				1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
				1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
				1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		};
		/**/
		//CTileMap::worldMap.setPosition(500,0);
		//CTileMap::worldMap.scale(2.0f,2.0f);

		if (!CTileMap::worldMap.load("img/tileset.png",sf::Vector2u(32,32), level, collision, 36, 20))
			throw 0;
		/**
		if (!CTileMap::worldMap.Structure(sf::Vector2u(100,100),sf::Vector2u(32,32)))
			throw 1;
		if (!CTileMap::worldMap.TextureMap("img/tileset.png",levelMap))
			throw 2;
		if (!CTileMap::worldMap.CollisionMap(collisionMap))
			throw 3;
		**/
		//CTileMap::worldMap.setPosition(100,100);

		this->p1.Structure(sf::Vector2f(32,32));
		this->p1.LoadTexture("img/gallery_5198_2_1320.png");
		this->p1.Animation(3);
		this->p1.InitialPos(1,2);
		//this->p1.scale(2.0f,2.0f);

	} catch(int e) {
		switch (e) {
		case 1:
			std::cout << "Structure Load Error:" << std::endl;
			break;
		case 2:
			std::cout << "Texture Load Error:" << std::endl;
			break;
		case 3:
			std::cout << "Collision Load Error:" << std::endl;
			break;
		}
	}
}

void CStateGame::OnDeactivation() {
	CTileMap::worldMap.Unload();
	this->p1.Unload();
	//CEntity::entityList.clear();
}

void CStateGame::OnLoop() {
	CTileMap::worldMap.ClearHighlight();
	CTileMap::worldMap.HighlightGrid(this->currentMousePoints);

	this->p1.OnLoop();
	sf::Vector2i p1Pos = CTileMap::worldMap.MapToPos(sf::Vector2f(this->p1.getPosition().x + ((this->p1.GetSize().x * this->p1.getScale().x) / 2), this->p1.getPosition().y + ((this->p1.GetSize().y * this->p1.getScale().y) / 2)));
	sf::Vector2i mousePos = CTileMap::worldMap.MapToPos(this->currentMousePoints);
	if (this->lastMousePosition != mousePos) {
		CTileMap::worldMap.ShowPath(p1Pos, mousePos);
		this->samePosition = false;
	}

	if (this->leftButton && !CTileMap::worldMap.Collide(this->currentMousePoints)) {
		this->p1.PathTo(mousePos);
		this->leftButton = false;
	}
	if (this->rightButton) {
		if (this->lastMousePosition != mousePos || !this->samePosition) {
			if (!CTileMap::worldMap.CollideMap(mousePos))
				CTileMap::worldMap.CreateWall(mousePos, 98.5);
			else
				CTileMap::worldMap.RemoveWall(mousePos, 84.5);
			this->samePosition = true;
		}

	}

	this->lastMousePosition = CTileMap::worldMap.MapToPos(this->currentMousePoints);
}

void CStateGame::OnRender(sf::RenderWindow * window) {

	//for (int i = 0; i < entityList.size(); i++) {
		//window->draw(entiyList[i]->OnDraw();
	//}


	window->draw(CTileMap::worldMap);
	window->draw(this->p1);

	window->display();
	window->clear(sf::Color::Black);
}

CStateGame * CStateGame::GetIntance() {
	return & instance;
}
void CStateGame::MouseMoved(sf::Event::MouseMoveEvent mouseMoveEvent) {
	this->currentMousePoints = sf::Vector2f(mouseMoveEvent.x,mouseMoveEvent.y);
}
void CStateGame::MouseButtonPressed(sf::Event::MouseButtonEvent mouseButtonEvent) {
	if ( mouseButtonEvent.button == sf::Mouse::Left ) {
		this->leftButton = true;

	}
	if ( mouseButtonEvent.button == sf::Mouse::Right ) {
		this->rightButton = true;
	}
}
void CStateGame::MouseButtonReleased(sf::Event::MouseButtonEvent mouseButtonEvent) {
	if ( mouseButtonEvent.button == sf::Mouse::Left ) {
		this->leftButton = false;
		this->samePosition = false;
	}
	if ( mouseButtonEvent.button == sf::Mouse::Right) {
		this->rightButton = false;
		this->samePosition = false;
	}

}
void CStateGame::KeyPressed(sf::Event::KeyEvent keyEvent) {
	if (keyEvent.code == sf::Keyboard::Escape)
		CStateManager::SetActiveState(STATE_MENU);
	//CStateManager::SetActiveState(STATE_NONE);
	/**
	if (keyEvent.code == sf::Keyboard::Up)
		p1.MoveUp();
	if (keyEvent.code == sf::Keyboard::Down)
		p1.MoveDown();
	if (keyEvent.code == sf::Keyboard::Left)
		p1.MoveLeft();
	if (keyEvent.code == sf::Keyboard::Right)
		p1.MoveRight();
	**/
}
