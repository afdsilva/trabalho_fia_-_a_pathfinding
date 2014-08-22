/*
 * CPathfinding.hpp
 *
 *  Created on: 09/08/2013
 *      Author: andref
 */

#ifndef CPATHFINDING_HPP_
#define CPATHFINDING_HPP_

#include <vector>
#include <list>
#include <string>
#include <iostream>
#include <cmath>
#include <climits>
#include <SFML/Graphics.hpp>

#include "CTileMap.hpp"
#include "CFPS.hpp"

class PathfindNode {
public:
	PathfindNode();
	PathfindNode(sf::Vector2i);

	static bool FindPosition(sf::Vector2i position, std::list<PathfindNode *> & nodeList);
	static bool FindNode(PathfindNode * node, std::list<PathfindNode *> & nodeList);
	static PathfindNode * GetNode(sf::Vector2i position, std::list<PathfindNode *> & nodeList);
	static std::list<PathfindNode *>::iterator GetLowerEstimativeIterator(std::list<PathfindNode *> & nodeList);
	static int Distance(sf::Vector2i posA, sf::Vector2i posB);
	static int CollisionIntersect(sf::Vector2i posA, sf::Vector2i posB);

	sf::Vector2i position;
	int status; //estado do objeto: -1 nao existe, 0 passeavel, 1 nao passeavel
	int cost; //custo do inicio ateh o melhor caminho conhecido
	int estimated; //custo total estimado do inicio ateh o final

	PathfindNode * backtracePath;

	bool exists();
};

class CPathFinding {
public:
	static std::list<sf::Vector2i> PathFinding(sf::Vector2i origin, sf::Vector2i destination);
};
#endif /* CPATHFINDING_HPP_ */
