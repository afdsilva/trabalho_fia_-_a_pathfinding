/*
 * CPathfinding.cpp
 *
 *  Created on: 09/08/2013
 *      Author: andref
 */

#include "CPathfinding.hpp"

std::list<sf::Vector2i> CPathFinding::PathFinding(sf::Vector2i origin, sf::Vector2i destination) {
	//std::cout << "Origin[" << origin.x << "." << origin.y << "]" << std::endl;
	//std::cout << "Origin[" << destination.x << "." << destination.y << "]" << std::endl;
	std::list<PathfindNode *> closedNodes; //nodos jah analisados
	std::list<PathfindNode *> openNodes; //nodos em aberto
	std::list<PathfindNode *> neighborNodes; //nodos em aberto

	std::list<sf::Vector2i> retorno;
	closedNodes.clear();
	openNodes.clear();
	neighborNodes.clear();
	PathfindNode * nodo = new PathfindNode(origin);
	nodo->cost = 0;
	nodo->estimated = nodo->cost + CTileMap::worldMap.HeuristicCostEstimate(origin,destination);

	openNodes.push_back(nodo);

	PathfindNode * atual, * vizinho;
	sf::Vector2i vizinhoPos;
	int estimative_atual;

	while(!openNodes.empty()) {
		/**
		CTileMap::worldMap.ClearHighlight();
		for (std::list<PathfindNode *>::iterator it = openNodes.begin(); it != openNodes.end(); it++) {
			PathfindNode * teste = *it;
			CTileMap::worldMap.HighlightGrid(CTileMap::worldMap.PosToMap(teste->position));
		}
		**/
		std::list<PathfindNode *>::iterator it = PathfindNode::GetLowerEstimativeIterator(openNodes);
		atual = *it;
		openNodes.erase(it);
		if (atual->position == destination) {
			break;
		}
		//std::cout << "Atual: " << atual->position.x << " " << atual->position.y << std::endl;
		closedNodes.push_back(atual);
		for (int i = -1; i <= 1; i++) {
			for (int j = -1; j <= 1; j++) {
				vizinhoPos = sf::Vector2i(i + atual->position.x, j + atual->position.y);
				if (vizinhoPos != atual->position) {
					if(PathfindNode::Distance(atual->position,vizinhoPos) < 3) { // < 2 retira movimento na diagonal
						if (atual->position.x >= 0 && atual->position.y >= 0) {
							if (PathfindNode::FindPosition(vizinhoPos,neighborNodes)) {
								vizinho = PathfindNode::GetNode(vizinhoPos,neighborNodes);
							} else {
								vizinho = new PathfindNode(vizinhoPos);
								vizinho->status = (CTileMap::worldMap.CollideMap(sf::Vector2i(vizinho->position))) ? 1 : 0;
								vizinho->cost = 0;
								vizinho->estimated = 0;
								//std::cout << "Vizinho Criado: "  << vizinho->position.x << " " << vizinho->position.y << std::endl;
							}
							estimative_atual = atual->cost + CTileMap::worldMap.HeuristicCostEstimate(atual->position,vizinho->position);
							if ((PathfindNode::FindNode(vizinho,closedNodes) && estimative_atual >= vizinho->cost) || vizinho->status == 1)
								continue;
							if (PathfindNode::Distance(atual->position,vizinhoPos) == 2) {

								if (PathfindNode::CollisionIntersect(atual->position,vizinhoPos) > 0) {
									continue;
								}
							}
							if (!(PathfindNode::FindNode(vizinho,openNodes)) || estimative_atual < vizinho->cost) {
								vizinho->backtracePath = atual;
								vizinho->cost = estimative_atual;
								vizinho->estimated = vizinho->cost +  CTileMap::worldMap.HeuristicCostEstimate(vizinho->position,destination);
								if (!PathfindNode::FindNode(vizinho,openNodes)) {
									openNodes.push_back(vizinho);
									//std::cout << "Vizinho em aberto" << std::endl;
								}
							}
						}
					}
				}
			}
		}
	}

	if (atual->position == destination) {
		PathfindNode * temp = atual;
		//std::cout << "Caminho Final: " << std::endl;
		while (temp->position != origin) {
			retorno.push_back(temp->position);
			//std::cout << "("<< temp->position.x << "," << temp->position.y << ")" << std::endl;
			temp = temp->backtracePath;
		}
		//std::cout << "("<< temp->position.x << "," << temp->position.y << ")" << std::endl;
		//this->lastPath = sf::Vector2i(temp->position);
		//retorno.push_back(temp->position);

		retorno.reverse();
		return retorno;
	}
	//std::cout << "saindo do metodo " << std::endl;
	retorno.clear();

	return retorno;

}


PathfindNode::PathfindNode() {
	this->position = sf::Vector2i(-1,-1);
	this->status = -1;
	this->cost = 0;
	this->estimated = 0;
	this->backtracePath = NULL;

}

PathfindNode::PathfindNode(sf::Vector2i position) {
	this->position = position;
	status = 0;
	this->cost = 0;
	this->estimated = 0;
	this->backtracePath = NULL;

}
bool PathfindNode::exists() {
	bool retorno = false;
	sf::Vector2i test = sf::Vector2i(-1,-1);
	if (this->position != test || this->status != -1)
		retorno = true;

	return retorno;
}

bool PathfindNode::FindPosition(sf::Vector2i position, std::list<PathfindNode *> & nodeList) {
	bool retorno = false;
	try {
		if (position.x < 0 && position.x > CTileMap::worldMap.GetSize().x)
			throw 1;
		if (position.y < 0 && position.y > CTileMap::worldMap.GetSize().y)
			throw 2;
		PathfindNode * atual;
		for (std::list<PathfindNode *>::iterator it = nodeList.begin(); it != nodeList.end(); it++) {
			atual = *it;

			if (atual->position == position)
				throw 0;
		}

	} catch (int e) {
		switch(e) {
		case 0:
			retorno = true;
			break;
		case 1:
			retorno = false;
			break;
		case 2:
			retorno = false;
			break;
		}
	}

	return retorno;

}
bool PathfindNode::FindNode(PathfindNode * node, std::list<PathfindNode *> & nodeList) {
	PathfindNode * atual;
	for (std::list<PathfindNode *>::iterator it = nodeList.begin(); it != nodeList.end(); it++) {
		atual = *it;
		if (node->position == atual->position)
			return true;
	}
	return false;
}
PathfindNode * PathfindNode::GetNode(sf::Vector2i position, std::list<PathfindNode *> & nodeList) {
	PathfindNode * retorno = new PathfindNode();
	PathfindNode * atual;
	for (std::list<PathfindNode *>::iterator it = nodeList.begin(); it != nodeList.end(); it++) {
		atual = *it;
		if (position == atual->position)
			return atual;
	}
	return retorno;
}
std::list<PathfindNode *>::iterator PathfindNode::GetLowerEstimativeIterator(std::list<PathfindNode *> & nodeList) {
	std::list<PathfindNode *>::iterator retorno = nodeList.begin();
	int lower_cost = INT_MAX;
	if (nodeList.size() > 0) {
		PathfindNode * atual;
		for (std::list<PathfindNode *>::iterator it = nodeList.begin(); it != nodeList.end(); it++) {
			atual = *it;
			if (atual->cost < lower_cost) {
				retorno = it;
				lower_cost = atual->cost;
			}
		}
	}
	return retorno;
}

int PathfindNode::Distance(sf::Vector2i posA, sf::Vector2i posB) {
	int retorno = 0;
	retorno += abs(posA.x - posB.x);
	retorno += abs(posA.y - posB.y);
	return retorno;
}
int PathfindNode::CollisionIntersect(sf::Vector2i posA, sf::Vector2i posB) {
	int retorno = 0;
	sf::Vector2i vizinhoA;
	sf::Vector2i vizinhoB;
	for(int i = -1; i <= 1; i++) {
		for(int j = -1; j <= 1; j++) {
			vizinhoA = sf::Vector2i(posA.x + i, posA.y + j);
			if (CTileMap::worldMap.CollideMap(vizinhoA)) {
				for(int k = -1; k <= 1; k++) {
					for(int l = -1; l <= 1; l++) {
						vizinhoB = sf::Vector2i(posB.x + k, posB.y + l);
						if (vizinhoA == vizinhoB) {
							if (CTileMap::worldMap.CollideMap(vizinhoB)) {
								retorno++;
							}
						}
					}
				}
			}
		}
	}
	return retorno;
}
