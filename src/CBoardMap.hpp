/*
 * CBoardMap.hpp
 *
 *  Created on: 21/08/2013
 *      Author: andref
 */

#ifndef CBOARDMAP_HPP_
#define CBOARDMAP_HPP_

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <vector>
#include <list>
#include <climits>

enum {
	NO_PLAYER = 0,
	PLAYER_1,
	PLAYER_2,
	IA_1,
	IA_2,
	NEW_GAME
};

enum {
	WINDOW_0 = 0x00000001,
	WINDOW_1 = 0x00000002,
	WINDOW_2 = 0x00000004,
	WINDOW_3 = 0x00000008,
};

enum {
	WIN = 1000,
	LOSE = -1000
};

class BoardMove {
public:
	sf::Vector2i move;
	int value;
	int depth;
	BoardMove();
	BoardMove(sf::Vector2i move, int value, int depth);
	BoardMove(int value, int depth);

};

class CBoardMap : public sf::Drawable, public sf::Transformable {
public:
	static CBoardMap board;
	CBoardMap();

	void NewGame();
	void NewGame(std::vector< std::vector<int> > boardMap);
	bool Structure(sf::Vector2f size, sf::Vector2i tileNumber);

	void HighlightRow(sf::Vector2i pos);
	void ColorBoard();

	sf::Vector2i PlayerTurn(int column);
	void UndoPlay(sf::Vector2i pos);
	bool Win(sf::Vector2i pos, int playerTurn);
	bool NextWin(sf::Vector2i pos, int playerTurn);
	bool Lose(sf::Vector2i pos, int playerTurn);
	bool NextLose(sf::Vector2i pos, int playerTurn);
	int HorizontalWin(sf::Vector2i pos, int playerTurn);
	int VerticalWin(sf::Vector2i pos, int playerTurn);
	int DiagonalPWin(sf::Vector2i pos, int playerTurn);
	int DiagonalSWin(sf::Vector2i pos, int playerTurn);

	bool InsideBoard(int x, int y);
	bool CheckFour(int x, int y, int dx, int dy, int playerTurn);

	void ShowBoard();

	std::vector< std::vector<int> > GetBoardMap();
	void IATurn(int player);

	int player;
	int lastPlayer;
	int playerWinner;

	sf::Vector2f PosToMap(sf::Vector2i posCoord); //retorna as coordenadas X Y
	sf::Vector2f PosToMapCenter(sf::Vector2i posCoord); //retorna as coordenadas centrais do tile
	sf::Vector2i MapToPos(sf::Vector2f mapCoord); // retorna as coordenadas do mapa tile


private:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	sf::Vector2i PosPlayable(int column);

	int MiniMax(sf::Vector2i pos, int depth, bool maximizing);
	BoardMove AlphaBeta(int depth, BoardMove alpha, BoardMove beta, bool maximizing);
	int NegaMax(sf::Vector2i pos, int depth, bool maximizing);

	int HeuristicCost();

	sf::VertexArray m_vertices;
	sf::VertexArray m_circles;

	sf::Vector2f size;
	sf::Vector2i tileNumber;

	std::vector< std::vector<int> > boardMap;
	sf::Vector2i lastPosPlayed;

};

#endif /* CBOARDMAP_HPP_ */
