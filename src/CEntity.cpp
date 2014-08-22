/*
 * CEntity.cpp
 *
 *  Created on: 02/07/2013
 *      Author: andref
 */

#include "CEntity.hpp"

std::vector<CEntity *> CEntity::entityList;
std::vector<CText *> CText::textList;
std::vector<CButton *> CButton::buttonList;

CEntity::CEntity() {

	this->velX = 0;
	this->velY = 0;

	this->acelX = 0;
	this->acelY = 0;

	this->maxVelX = 10;
	this->maxVelY = 10;

	this->lastPath = sf::Vector2i(-1,-1);

}

bool CEntity::Structure(sf::Vector2f size) {
	this->m_vertices.setPrimitiveType(sf::Quads);
	//sf::RectangleShape shape;
	//m_vertices = shape;
	this->m_vertices.resize(4);

	this->m_vertices[0].position = this->getPosition();
	this->m_vertices[1].position = sf::Vector2f(this->getPosition().x + size.x, this->getPosition().y);
	this->m_vertices[3].position = sf::Vector2f(this->getPosition().x, this->getPosition().y + size.y);
	this->m_vertices[2].position = sf::Vector2f(this->getPosition().x + size.x, this->getPosition().y + size.y);
	this->size = size;
	return false;
}
sf::Vector2f CEntity::GetSize() {
	return this->size;
}
bool CEntity::LoadTexture(const std::string & file) {
	bool retorno = true;
	try {
		if (!m_texture.loadFromFile(file))
			throw 1;
		int tileNumber = 0, tu, tv;
		tu = (int)tileNumber % (int)(m_texture.getSize().x / this->size.x);
		tv = tileNumber / (m_texture.getSize().x / this->size.x);
		m_vertices[0].texCoords = sf::Vector2f(tu * this->size.x,tv * this->size.y);
		m_vertices[1].texCoords = sf::Vector2f((tu + 1) * this->size.x,tv * this->size.y);
		m_vertices[2].texCoords = sf::Vector2f((tu + 1) * this->size.x,(tv + 1) * this->size.y);
		m_vertices[3].texCoords = sf::Vector2f(tu * this->size.x,(tv + 1) * this->size.y);

	} catch (int e) {
		retorno = false;
	}

	return retorno;
}

void CEntity::Unload() {
	this->m_vertices.clear();
	sf::Texture nTexture;
	this->m_texture = nTexture;

	this->velX = 0;
	this->velY = 0;

	this->acelX = 0;
	this->acelY = 0;

	this->maxVelX = 10;
	this->maxVelY = 10;

	this->lastPath = sf::Vector2i(-1,-1);
}

void CEntity::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	// apply the entity's transform -- combine it with the one that was passed by the caller
	states.transform *= getTransform(); // getTransform() is defined by sf::Transformable

	// apply the texture
	states.texture = &m_texture;

	// draw the vertex array
	target.draw(m_vertices, states);
}

void CEntity::OnLoop() {
	try {
		this->StopMovement();

		if (this->path.size() > 0 && (this->velX == 0 && this->velY == 0)) {
			sf::Vector2i position = this->path.front();
			//std::cout << "CEntity::OnLoop: ("<< position.x << "," << position.y << ")" << std::endl;
			this->MoveTo(position);
			this->path.pop_front();
		}

		if (floor(this->getPosition().x) != floor(this->moveTo.x)) {
			float dx = this->moveTo.x - this->getPosition().x;
			this->acelX = dx > 0 ? 0.75 : -0.75;
		}
		if (floor(this->getPosition().y) != floor(this->moveTo.y)) {
			float dy = this->moveTo.y - this->getPosition().y;
			this->acelY = dy > 0 ? 0.75 : -0.75;
		}
		this->velX += this->acelX;
		this->velY += this->acelY;

		if (this->velX > this->maxVelX) this->velX = this->maxVelX;
		if (this->velX < -this->maxVelX) this->velX = -this->maxVelX;
		if (this->velY > this->maxVelY) this->velY = this->maxVelY;
		if (this->velY < -this->maxVelY) this->velY = -this->maxVelY;

		this->OnMovement(sf::Vector2f(this->velX,this->velY));

	} catch (int e) {
		if (e == 1)
			return;
		else
			std::cout << "Erro!" << std::endl;
	}

}

void CEntity::OnMovement(sf::Vector2f velocity) {
	try {
		if (velocity.x == 0 && velocity.y == 0)
			throw 1;
		float newX = 0, newY = 0;

		velocity.x *= CFPS::FPSControl.GetSpeedFactor();
		velocity.y *= CFPS::FPSControl.GetSpeedFactor();

		if (velocity.x > 0) newX = CFPS::FPSControl.GetSpeedFactor();
		else newX = -CFPS::FPSControl.GetSpeedFactor();

		if (velocity.y > 0) newY = CFPS::FPSControl.GetSpeedFactor();
		else newY = -CFPS::FPSControl.GetSpeedFactor();

		while(true) {

			sf::Rect<float> box, box2, box3;
			box.height = this->size.y;
			box.width = this->size.x;
			box.left = this->getPosition().x + newX;
			box.top = this->getPosition().y + newY;

			this->move(newX,newY);

			velocity.x += -newX;
			velocity.y += -newY;

			if (newX > 0 && velocity.x <= 0) newX = 0;
			if (newX < 0 && velocity.x >= 0) newX = 0;

			if (newY > 0 && velocity.y <= 0) newY = 0;
			if (newY < 0 && velocity.y >= 0) newY = 0;

			if (velocity.x == 0) newX = 0;
			if (velocity.y == 0) newY = 0;

			if (velocity.x == 0 && velocity.y == 0) break;
			if (newX == 0 && newY == 0) break;
		}

	} catch (int e) {
		if (e == 1)
			return;
		else
			std::cout << "Erro!" << std::endl;
	}
}

void CEntity::StopMovement() {
	float dx = this->moveTo.x - this->getPosition().x;
	if (dx < 2.0f && dx > -2.0f) {
		this->velX = 0;
		this->acelX = 0;
	}
	float dy = this->moveTo.y - this->getPosition().y;
	if (dy < 2.0f && dy > -2.0f) {
		this->velY = 0;
		this->acelY = 0;
	}

}

void CEntity::Animation(int framesNum) {

}

void CEntity::MoveTo(sf::Vector2f points) {
	sf::Vector2i mapPos = CTileMap::worldMap.MapToPos(points);
	this->moveTo = CTileMap::worldMap.PosToMap(mapPos);
	//if (this->PathFinding(CTileMap::worldMap.MapToPos(pos), CTileMap::worldMap.MapToPos(position)))
}
void CEntity::MoveTo(sf::Vector2i position) {
	this->moveTo = CTileMap::worldMap.PosToMap(position);
}
void CEntity::InitialPos(int x, int y) {
	this->InitialPos(sf::Vector2i(x,y));
}
void CEntity::InitialPos(sf::Vector2i position) {
	sf::Vector2f initialPos = CTileMap::worldMap.PosToMap(position);
	//sf::Vector2f tileSize = CTileMap::worldMap.GetTileSize();
	//sf::Vector2f points = sf::Vector2f(initialPos.x - tileSize.x, initialPos.y - tileSize.y);
	sf::Vector2f points = sf::Vector2f(initialPos.x, initialPos.y);
	this->setPosition(points);
	this->moveTo = points;

}

void CEntity::PathTo(sf::Vector2i position) {
	this->lastPath = CTileMap::worldMap.MapToPos(this->getPosition());
	this->path = CPathFinding::PathFinding(this->lastPath,position);
	/**
	for (std::list<sf::Vector2i>::iterator it = this->path.begin(); it != this->path.end(); it++) {
		sf::Vector2i temp = *it;
		std::cout << "(" << temp.x << "," << temp.y << ")" << std::endl;
	}
	**/

}

CPlayer::CPlayer() {

}

void CPlayer::MoveLeft() {
	//this->move(sf::Vector2f(-(this->m_vertices.getBounds().width * this->getScale()).x,0));
	this->MoveTo(this->getPosition());
}
void CPlayer::MoveRight() {
	//this->move(sf::Vector2f(this->m_vertices.getBounds().width * this->getScale().x,0));
	this->MoveTo(this->getPosition());
}
void CPlayer::MoveUp() {
	//this->move(sf::Vector2f(0,-(this->m_vertices.getBounds().height * this->getScale().y)));
	this->MoveTo(this->getPosition());
}
void CPlayer::MoveDown() {
	//this->move(sf::Vector2f(0,this->m_vertices.getBounds().height * this->getScale().y));
	this->MoveTo(this->getPosition());
}

/**
 *
 * CText
 *
 */

CText::CText() {

	const sf::Text text;
	this->m_text = text;
	this->m_font = new sf::Font();
	this->size = 0;
	this->id = CText::textList.size();
	sentence.clear();
}
bool CText::load(const std::string & text,const sf::Font & font, unsigned int size) {
	bool retorno = true;
	try {
		this->SetText(text);
		this->m_text.setCharacterSize(size);
		this->m_font = (sf::Font *) &font;

		this->m_text.setFont(*this->m_font);
	} catch (int e) {
		retorno = false;
	}
	return retorno;

}
bool CText::load(const std::string & text, const std::string & fontFile, unsigned int size) {
	bool retorno = true;
	try {
		this->SetText(text);
		this->m_text.setCharacterSize(size);
		if (!this->m_font->loadFromFile(fontFile))
			throw;
		this->m_text.setFont(*this->m_font);
	} catch (int e) {
		retorno = false;
	}
	return retorno;

}

void CText::Unload() {
	const sf::Text text;
	this->m_text = text;
	this->m_font = NULL;
	this->size = 0;
	this->sentence.clear();
}
void CText::OnLoop() {

}

void CText::SetText(const std::string & text) {
	this->m_text.setString(text);
}

void CText::SetColor(sf::Color color) {
	this->m_text.setColor(color);
}

void CText::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	// apply the entity's transform -- combine it with the one that was passed by the caller
	states.transform *= getTransform(); // getTransform() is defined by sf::Transformable

	target.draw(this->m_text, states);
}
string CText::GetText() {
	return sentence;
}

CButton::CButton() {
	actionHover = -1;
	this->id = CButton::buttonList.size();
}

void CButton::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	// apply the entity's transform -- combine it with the one that was passed by the caller
	states.transform *= getTransform(); // getTransform() is defined by sf::Transformable

	target.draw(this->m_shape, states);
	target.draw(this->m_text, states);

}

void CButton::Unload() {
	CText::Unload();
	sf::RectangleShape rect;
	this->m_shape = rect;
}
void CButton::OnLoop() {

}

void CButton::SetBackground(sf::Color cor) {
	this->m_shape.setPosition(sf::Vector2f(this->m_text.getPosition().x-5,this->m_text.getPosition().y+10));
	this->m_shape.setSize(sf::Vector2f(this->m_text.getGlobalBounds().width+5,this->m_text.getGlobalBounds().height+10));
	this->m_shape.setFillColor(cor);
	this->m_shape.setOutlineColor(sf::Color::Blue);
	this->m_shape.setOutlineThickness(1.0f);

}

void CButton::Highlight(sf::Vector2f points) {
	//sf::FloatRect boundingBox = this->m_shape.getGlobalBounds();
		if (this->OnHover(points)) {
		this->m_shape.setOutlineColor(sf::Color::Yellow);
	}
	else {
		this->m_shape.setOutlineColor(sf::Color::Blue);
	}

}

bool CButton::OnHover(sf::Vector2f points) {
	bool retorno = false;
	sf::FloatRect boundingBox;
	boundingBox.top = this->getPosition().y;
	boundingBox.left = this->getPosition().x;
	boundingBox.width = this->m_shape.getSize().x;
	boundingBox.height = this->m_shape.getSize().y;

	if (boundingBox.contains(points))
		retorno = true;

	return retorno;
}
int CButton::GetActionHover() {
	return this->actionHover;
}
void CButton::SetActionHover(int state) {
	this->actionHover = state;
}
