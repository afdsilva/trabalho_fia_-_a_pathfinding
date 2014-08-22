/*
 * CTileMap.hpp
 *
 *  Created on: 17/07/2013
 *      Author: andref
 */

#ifndef CTILEMAP_HPP_
#define CTILEMAP_HPP_

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <vector>
#include <list>

#include "CPathfinding.hpp"

class CTileMap : public sf::Drawable, public sf::Transformable {
public:

	static CTileMap worldMap;

	static sf::Vector2f IsoTo2D(sf::Vector2f position);
	static sf::Vector2f IsoTo2D(float x, float y);
	static sf::Vector2f TwoToIso(sf::Vector2f position);
	static sf::Vector2f TwoToIso(float x, float y);

	CTileMap();
	bool load(const std::string& tileset, sf::Vector2u tileSize, const float* tiles, const int* collision, unsigned int width, unsigned int height);

	static std::vector<int> ListStates();
	static bool SaveState(std::vector<int> list);
	static std::vector<int> LoadState(int state);

	bool Structure(sf::Vector2u size, sf::Vector2u tileSize);
	bool CollisionMap(std::vector<int> map);
	bool TextureMap(const std::string& tileset, std::vector<int> map);
	void Unload();
	sf::Vector2f GetSize();
	sf::Vector2f GetTileSize();
	void ShowGrid();
	void ShowCollision();
	void HighlightGrid(sf::Vector2f points);
	void ClearHighlight();
	bool Collide(sf::Vector2f points);
	bool CollideMap(sf::Vector2i position);
	bool CollideBox(sf::Rect<float> box);
	bool CollideBox(sf::Rect<float> box, float relax);

	sf::Vector2f PosToMap(sf::Vector2i posCoord); //retorna as coordenadas X Y
	sf::Vector2f PosToMapCenter(sf::Vector2i posCoord); //retorna as coordenadas centrais do tile
	sf::Vector2i MapToPos(sf::Vector2f mapCoord); // retorna as coordenadas do mapa tile
	int HeuristicCostEstimate(sf::Vector2i origin, sf::Vector2i destination);
	void ShowPath(sf::Vector2i origin, sf::Vector2i destination);

	void CreateWall(sf::Vector2i position, float defaultWall);
	void CreateWall(sf::Vector2i position);
	void RemoveWall(sf::Vector2i position, float defaultFloor);
	void RemoveWall(sf::Vector2i position);

private:
	bool ChangeCollide(sf::Vector2i position);
	bool ChangeTexture(sf::Vector2i position, float tileNumber);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void CreateIsoTile(sf::Vertex * tile, sf::Vector2f position);
	void CreateIsoBoundries(sf::Vertex * tile, sf::Vector2f position);
	unsigned int width;
	unsigned int height;
	sf::Vector2u tileSize;
	sf::Color defaultBGColor;

	bool noTexture;
	bool showGrid;
	bool showCollision;

	std::vector< std::vector<int> > collisionMap;

	sf::VertexArray m_vertices;
	sf::VertexArray m_boundries;
	sf::VertexArray m_path;
	sf::Texture m_tileset;

	int defaultFloor;
	int defaultWall;

};

#endif /* CTILEMAP_HPP_ */
