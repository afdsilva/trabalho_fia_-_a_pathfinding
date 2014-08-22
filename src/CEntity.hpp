/*
 * CEntity.hpp
 *
 *  Created on: 02/07/2013
 *      Author: andref
 */

#ifndef CENTITY_HPP_
#define CENTITY_HPP_

#include <vector>
#include <list>
#include <string>
#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>

#include "CPathfinding.hpp"
#include "CTileMap.hpp"
#include "CFPS.hpp"


using namespace std;

class CEntity : public sf::Drawable, public sf::Transformable {
public:
	static std::vector<CEntity *> entityList;

	CEntity();
	bool Structure(sf::Vector2f size);
	bool Structure(int radius);
	sf::Vector2f GetSize();

	virtual bool LoadTexture(const std::string & file);

	virtual void Unload();

	static std::list<sf::Vector2i> PathFinding(sf::Vector2i origin, sf::Vector2i destination);

	void InitialPos(sf::Vector2i position);
	void InitialPos(int x, int y);
	void Animation(int framesNum);

	void PathTo(sf::Vector2i position);

	virtual void OnLoop();

protected:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void OnMovement(sf::Vector2f position);
	void StopMovement();

	void MoveTo(sf::Vector2f points);
	void MoveTo(sf::Vector2i position);
	void MoveTo(float x, float y);
	void MoveTo(int x, int y);

	bool PosValMap(sf::Vector2f position);

	std::list<sf::Vector2i> path;
	sf::Vector2i lastPath;
	sf::VertexArray m_vertices;
	sf::Texture m_texture;
	sf::Vector2f size;

	sf::Vector2f moveTo;

	float velX;
	float velY;

	float acelX;
	float acelY;

	float maxVelX;
	float maxVelY;

};

class CPlayer : public CEntity {
public:
	CPlayer();

	void MoveLeft();
	void MoveRight();
	void MoveUp();
	void MoveDown();

};

class CText : public sf::Drawable, public sf::Transformable {
public:
	static std::vector<CText *> textList;
	CText();
	int id;

private:
protected:
	sf::Text m_text;
	sf::Font * m_font;
	int size;
	std::string sentence;

public:
	bool load(const std::string & text, const std::string & fontFile, unsigned int size);
	bool load(const std::string & text, const sf::Font & font, unsigned int size);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	virtual void OnLoop();

	virtual void Unload();

	void SetText(const std::string & text);
	void SetFont(sf::Font & font);
	void SetColor(sf::Color color);

	string GetText();

};

class CButton : public CText {
public:
	static std::vector<CButton *> buttonList;
	CButton();

private:
	sf::RectangleShape m_shape;
	int actionHover;
public:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	virtual void Unload();
	virtual void OnLoop();

	void SetBackground(sf::Color cor);
	void Highlight(sf::Vector2f points);
	bool OnHover(sf::Vector2f points);
	int GetActionHover();
	void SetActionHover(int state);


};
#endif /* CENTITY_HPP_ */
