/*
 * CTileMap.cpp
 *
 *  Created on: 17/07/2013
 *      Author: andref
 */

#include "CTileMap.hpp"

CTileMap CTileMap::worldMap;

CTileMap::CTileMap() {
	this->showGrid = false;
	this->showCollision = false;
	this->noTexture = false;
	this->defaultBGColor = sf::Color::White;

	this->defaultWall = -1;
	this->defaultFloor = -1;
}

void CTileMap::Unload() {
	//this->scale(0,0);
	this->setScale(1.0f,1.0f);
	this->setPosition(0,0);

	width = 0;
	height = 0;
	tileSize = sf::Vector2u(0,0);
	defaultBGColor = sf::Color::White;

	noTexture = false;
	showGrid = false;
	showCollision = false;

	for (unsigned int i = 0; i < width; ++i) {
		collisionMap[i].clear();
	}
	collisionMap.clear();
	sf::VertexArray vertices;
	m_vertices = vertices;
	sf::VertexArray boundries;
	m_boundries = boundries;
	sf::Texture tile;
	m_tileset = tile;

}

void CTileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	// apply the transform
	states.transform *= getTransform();

	// apply the tileset texture
	states.texture = &m_tileset;
	// draw the vertex array
	target.draw(m_vertices, states);

	target.draw(m_path);

	if (this->showGrid)
		target.draw(m_boundries,states);

}

bool CTileMap::load(const std::string& tileset, sf::Vector2u tileSize, const float* tiles, const int* collision, unsigned int width, unsigned int height) {
	// load the tileset texture
	bool retorno = true;
	try {

		if (tileset.empty()) {
			noTexture = true;
		}
		else if (!m_tileset.loadFromFile(tileset)) {
			throw 1;
		}

		this->tileSize = tileSize;
		this->width = width;
		this->height = height;

		// resize the vertex array to fit the level size
		m_vertices.setPrimitiveType(sf::Quads);
		m_vertices.resize(width * height * 4);

		m_boundries.setPrimitiveType(sf::Lines);
		m_boundries.resize(width * height * 8);

		collisionMap.resize(this->width);
		for (unsigned int i = 0; i < this->width; ++i) {
			collisionMap[i].resize(this->height);
			for (unsigned int j = 0; j < this->height; ++j) {

				float tileNumber = tiles[i + j * this->width];

				int tu = 0;
				int tv = 0;
				if (!noTexture) {
					tu = (int)tileNumber % (m_tileset.getSize().x / tileSize.x);
					tv = tileNumber / (m_tileset.getSize().x / tileSize.x);
				}

				// collision map
				collisionMap[i][j] = collision[(i) + (j*this->width)] == 1 ? 1 : 0;
				//std::cout << "i: " << i << " j: " << j << " Colision: " << collision[(i) + (j*width)] << std::endl;

				// get a pointer to the current tile's quad
				sf::Vertex * quad = &m_vertices[(i + j * this->width) * 4];
				sf::Vertex * boundries = &m_boundries[(i + j * this->width) * 8];
				// define its 4 corners
				//sf::Vector2f position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
				//CreateIsoTile(quad, position);

				quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
				quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
				quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
				quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);
				//for (int k = 0;k < 4; k++)
				//	quad[k].color = sf::Color::Black;

				if (this->showGrid) {
					boundries[0].position = sf::Vector2f((i * tileSize.x)+0.1f, (j * tileSize.y)+0.1f); //0
					boundries[1].position = sf::Vector2f(((i + 1) * tileSize.x)-0.1f, (j * tileSize.y)+0.1f); //1
					boundries[2].position = sf::Vector2f(((i + 1) * tileSize.x)-0.1f, (j * tileSize.y)+0.1f); //1
					boundries[3].position = sf::Vector2f(((i + 1) * tileSize.x)-0.1f, ((j + 1) * tileSize.y)-0.1f); //2
					boundries[4].position = sf::Vector2f(((i + 1) * tileSize.x)-0.1f, ((j + 1) * tileSize.y)-0.1f); //2
					boundries[5].position = sf::Vector2f((i * tileSize.x)+0.1f, ((j + 1) * tileSize.y)-0.1f); //3
					boundries[6].position = sf::Vector2f((i * tileSize.x)+0.1f, ((j + 1) * tileSize.y)-0.1f); //3
					boundries[7].position = sf::Vector2f((i * tileSize.x)+0.1f, (j * tileSize.y)+0.1f); //0
					for (int k = 0;k < 8; k++)
						boundries[k].color = sf::Color::White;

				}

				// define its 4 texture coordinates
				if (!noTexture) {
					float decimal = tileNumber - std::floor(tileNumber);
					sf::Vector2f halfTile(0,0);
					if (decimal != 0) {
						halfTile.x = tileSize.x / 2;
						halfTile.y = tileSize.y / 2;
					}
					quad[0].texCoords = sf::Vector2f(tu * tileSize.x + halfTile.x, tv * tileSize.y + halfTile.y);
					quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x + halfTile.x, tv * tileSize.y + halfTile.y);
					quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x + halfTile.x, (tv + 1) * tileSize.y + halfTile.y);
					quad[3].texCoords = sf::Vector2f(tu * tileSize.x + halfTile.x, (tv + 1) * tileSize.y + halfTile.y);

					//std::cout << "tileNumber: " << tileNumber << " decimal: " << decimal << std::endl;

				}
			}
		}
	} catch (int e) {
		std::cout << "Excecao!" << std::endl;
		retorno = false;
	}

	return retorno;
}

bool CTileMap::Structure(sf::Vector2u size, sf::Vector2u tileSize) {
	bool retorno = true;
	try {
		this->tileSize = tileSize;
		this->width = width;
		this->height = height;

		// resize the vertex array to fit the level size
		m_vertices.setPrimitiveType(sf::Quads);
		m_vertices.resize(width * height * 4);

		m_boundries.setPrimitiveType(sf::Lines);
		m_boundries.resize(width * height * 8);

		m_path.clear();

		for (unsigned int i = 0; i < this->width; ++i) {
			for (unsigned int j = 0; j < this->height; ++j) {

				sf::Vertex * quad = &m_vertices[(i + j * this->width) * 4];
				sf::Vertex * boundries = &m_boundries[(i + j * this->width) * 8];
				// define its 4 corners
				//sf::Vector2f position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
				//CreateIsoTile(quad, position);

				quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
				quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
				quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
				quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);
				//for (int k = 0;k < 4; k++)
				//	quad[k].color = sf::Color::Black;

				if (this->showGrid) {
					boundries[0].position = sf::Vector2f((i * tileSize.x)+0.1f, (j * tileSize.y)+0.1f); //0
					boundries[1].position = sf::Vector2f(((i + 1) * tileSize.x)-0.1f, (j * tileSize.y)+0.1f); //1
					boundries[2].position = sf::Vector2f(((i + 1) * tileSize.x)-0.1f, (j * tileSize.y)+0.1f); //1
					boundries[3].position = sf::Vector2f(((i + 1) * tileSize.x)-0.1f, ((j + 1) * tileSize.y)-0.1f); //2
					boundries[4].position = sf::Vector2f(((i + 1) * tileSize.x)-0.1f, ((j + 1) * tileSize.y)-0.1f); //2
					boundries[5].position = sf::Vector2f((i * tileSize.x)+0.1f, ((j + 1) * tileSize.y)-0.1f); //3
					boundries[6].position = sf::Vector2f((i * tileSize.x)+0.1f, ((j + 1) * tileSize.y)-0.1f); //3
					boundries[7].position = sf::Vector2f((i * tileSize.x)+0.1f, (j * tileSize.y)+0.1f); //0
					for (int k = 0;k < 8; k++)
						boundries[k].color = sf::Color::White;

				}
			}
		}

	} catch (int e) {
		std::cout << "Excecao!" << std::endl;
		retorno = false;
	}

	return retorno;
}
bool CTileMap::CollisionMap(std::vector<int> map) {
	bool retorno = true;
	try {
		collisionMap.resize(this->width);
		for (unsigned int i = 0; i < this->width; ++i) {
			collisionMap[i].resize(this->height);
			for (unsigned int j = 0; j < this->height; ++j) {
				if (map.size() > (i + j * this->width))
					collisionMap[i][j] = map[i + j * this->width] == 0 ? 0 : 1;
			}
		}

	} catch (int e) {
		std::cout << "Excecao!" << std::endl;
		retorno = false;
	}

	return retorno;
}
bool CTileMap::TextureMap(const std::string& tileset, std::vector<int> map) {
	bool retorno = true;
	try {
		if (!noTexture) {
			for (unsigned int i = 0; i < this->width; ++i) {
				for (unsigned int j = 0; j < this->height; ++j) {
					if (map.size() > (i + j * this->width)) {

						sf::Vertex * quad = &m_vertices[(i + j * this->width) * 4];

						float tileNumber = map[i + j * this->width];

						int tu = 0;
						int tv = 0;
						tu = (int)tileNumber % (m_tileset.getSize().x / tileSize.x);
						tv = tileNumber / (m_tileset.getSize().x / tileSize.x);

						// define its 4 texture coordinates
						float decimal = tileNumber - std::floor(tileNumber);
						sf::Vector2f halfTile(0,0);
						if (decimal != 0) {
							halfTile.x = tileSize.x / 2;
							halfTile.y = tileSize.y / 2;
						}
						quad[0].texCoords = sf::Vector2f(tu * tileSize.x + halfTile.x, tv * tileSize.y + halfTile.y);
						quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x + halfTile.x, tv * tileSize.y + halfTile.y);
						quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x + halfTile.x, (tv + 1) * tileSize.y + halfTile.y);
						quad[3].texCoords = sf::Vector2f(tu * tileSize.x + halfTile.x, (tv + 1) * tileSize.y + halfTile.y);

						//std::cout << "tileNumber: " << tileNumber << " decimal: " << decimal << std::endl;
					}
				}
			}
		}

	} catch (int e) {
		std::cout << "Excecao!" << std::endl;
		retorno = false;
	}

	return retorno;
}

void CTileMap::ShowGrid() {
	this->showGrid = this->showGrid ? false : true;
}
void CTileMap::ShowCollision() {
	this->showCollision = this->showCollision ? false : true;
}

bool CTileMap::Collide(sf::Vector2f points) {
	bool retorno = false;
	try {

		sf::Vector2i pos = MapToPos(points);
		return CollideMap(pos);

	} catch (int e) {
		retorno = false;
	}
	return retorno;
}
bool CTileMap::CollideMap(sf::Vector2i position) {
	bool retorno = false;
	try {

		if (position.x < 0 || position.x > (int) this->width)
			throw 1;
		if (position.y < 0 || position.y > (int) this->height)
			throw 1;
		if (position.x >= (int) collisionMap.size())
			throw 2;
		if (position.y >= (int) collisionMap[position.x].size())
			throw 3;
		if (collisionMap[position.x][position.y] == 1)
			return true;

	} catch (int e) {
		switch (e) {
		case 1:
			//std::cout << "x ou y negativo" << std::endl;
			break;
		case 2:
			//std::cout << "x fora dos limites " << std::endl;
			break;
		case 3:
			//std::cout << "y fora dos limites" << std::endl;
			break;
		}
		retorno = false;
	}
	return retorno;
}
bool CTileMap::CollideBox(sf::Rect<float> box) {
	bool retorno = false;
	try {
		sf::Vector2f topLeft = sf::Vector2f(box.left, box.top);
		sf::Vector2f topRight = sf::Vector2f(box.left + box.width, box.top);
		sf::Vector2f bottomLeft = sf::Vector2f(box.left, box.top + box.height);
		sf::Vector2f bottomRight = sf::Vector2f(box.left + box.width, box.top + box.height);

		if (this->Collide(topLeft)) throw 0;
		if (this->Collide(topRight)) throw 0;
		if (this->Collide(bottomLeft)) throw 0;
		if (this->Collide(bottomRight)) throw 0;

		retorno = true;

	} catch (int e) {
		retorno = false;
	}
	return retorno;
}
bool CTileMap::CollideBox(sf::Rect<float> box, float relax) {

	box.left += relax;
	box.top += relax;
	box.width -= relax;
	box.height -= relax;

	return this->CollideBox(box);
}
void CTileMap::HighlightGrid(sf::Vector2f points) {
	if (points.x >= 0 && points.y >= 0) {
		//ClearHighlight();

		sf::Vector2i position = this->MapToPos(points);
		sf::Vertex * quad;


		sf::Color cor;
		quad = &m_vertices[(position.x + position.y * this->width) * 4];
		if (this->CollideMap(position)) {
			cor = sf::Color::Red;
		} else {
			cor = sf::Color::Green;
		}

		for (int k = 0;k < 4; k++)
			quad[k].color = cor;
	}
}
void CTileMap::ClearHighlight() {

	sf::Vertex * quad;
	for (unsigned int i = 0; i < this->width; ++i) {
		for (unsigned int j = 0; j < this->height; ++j) {
			quad = &m_vertices[(i + j * this->width) * 4];
			for (int k = 0;k < 4; k++)
				quad[k].color = this->defaultBGColor;
		}
	}
}
sf::Vector2f CTileMap::PosToMap(sf::Vector2i posCoord) {
	sf::Vector2f retorno;
	try {
		float x = this->getPosition().x + (posCoord.x * (this->tileSize.x * this->getScale().x));
		float y = this->getPosition().y + (posCoord.y * (this->tileSize.y * this->getScale().y));
		retorno = sf::Vector2f(x,y);
	} catch (int e) {
		retorno = sf::Vector2f(-1,-1);
	}
	return retorno;
}
sf::Vector2f CTileMap::PosToMapCenter(sf::Vector2i posCoord) {
	sf::Vector2f retorno;
	try {
		float x = this->getPosition().x + (posCoord.x * (this->tileSize.x * this->getScale().x)) + ((this->tileSize.x * this->getScale().x) / 2);
		float y = this->getPosition().y + (posCoord.y * (this->tileSize.y * this->getScale().y)) + ((this->tileSize.y * this->getScale().y) / 2);
		retorno = sf::Vector2f(x,y);
	} catch (int e) {
		retorno = sf::Vector2f(-1,-1);
	}
	return retorno;
}

sf::Vector2i CTileMap::MapToPos(sf::Vector2f mapCoord) {
	sf::Vector2i retorno;
	try {

		float i = floor((mapCoord.x) / (this->tileSize.x * this->getScale().x));
		float j = floor((mapCoord.y) / (this->tileSize.y * this->getScale().y));

		retorno = sf::Vector2i(i,j);

	} catch (int e) {
		retorno = sf::Vector2i(-1,-1);
	}
	return retorno;
}

sf::Vector2f CTileMap::IsoTo2D(sf::Vector2f position) {
	sf::Vector2f retorno;

	retorno.x = ( 2 * position.y + position.x) / 2;
	retorno.y = ( 2 * position.y - position.x) / 2;
	return retorno;
}
sf::Vector2f CTileMap::IsoTo2D(float x, float y) {
	return CTileMap::IsoTo2D(sf::Vector2f(x,y));
}
sf::Vector2f CTileMap::TwoToIso(sf::Vector2f position) {
	sf::Vector2f retorno;
	retorno.x = position.x - position.y;
	retorno.y = (position.x + position.y) / 2;
	return retorno;
}
sf::Vector2f CTileMap::TwoToIso(float x, float y) {
	return CTileMap::TwoToIso(sf::Vector2f(x,y));
}

void CTileMap::CreateIsoTile(sf::Vertex * tile, sf::Vector2f position) {
	//top
	/**/
	tile[0].position = CTileMap::TwoToIso(position);
	tile[1].position = CTileMap::TwoToIso(sf::Vector2f(position.x, position.y - this->tileSize.y));
	tile[2].position = CTileMap::TwoToIso(sf::Vector2f(position.x - this->tileSize.x, position.y - this->tileSize.y));
	tile[3].position = CTileMap::TwoToIso(sf::Vector2f(position.x - this->tileSize.x, position.y));
	//left
	tile[4].position = tile[0].position;
	tile[5].position = sf::Vector2f(tile[4].position.x, tile[4].position.y + this->tileSize.y);
	tile[6].position = sf::Vector2f(tile[3].position.x, tile[3].position.y + this->tileSize.y);
	tile[7].position = tile[3].position;
	//right
	tile[8].position = tile[5].position;
	tile[9].position = sf::Vector2f(tile[1].position.x, tile[1].position.y + this->tileSize.y);
	tile[10].position = tile[1].position;
	tile[11].position = tile[0].position;
	/**/

}

void CTileMap::CreateIsoBoundries(sf::Vertex * tile, sf::Vector2f position) {
	tile[0].position = CTileMap::TwoToIso(position);
	tile[1].position = CTileMap::TwoToIso(sf::Vector2f(position.x, position.y - this->tileSize.y));
	tile[2].position = CTileMap::TwoToIso(sf::Vector2f(position.x - this->tileSize.x, position.y - this->tileSize.y));
	tile[3].position = CTileMap::TwoToIso(sf::Vector2f(position.x - this->tileSize.x, position.y));

}

sf::Vector2f CTileMap::GetSize() {
	sf::Vector2f retorno = sf::Vector2f(this->width,this->height);
	return retorno;
}
sf::Vector2f CTileMap::GetTileSize() {
	sf::Vector2f retorno = sf::Vector2f(this->tileSize);
	return retorno;
}

int CTileMap::HeuristicCostEstimate(sf::Vector2i origin, sf::Vector2i destination) {
	int retorno = 0;

	retorno = abs(origin.x - destination.x);
	retorno += abs(origin.y - destination.y);
	int weight = 0;
	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			if (this->Collide(sf::Vector2f(origin.x + i, origin.y + j))) {
				weight+=1;
			}
		}
	}
	/** /
	if (retorno >= 2) {
		retorno += weight;
		std::cout << "origin: " << origin.x << " " << origin.y << std::endl;
		std::cout << "destination: " << destination.x << " " << destination.y << std::endl;
	}
	/ **/

	return retorno;
}

void CTileMap::ShowPath(sf::Vector2i origin, sf::Vector2i destination) {
	std::list<sf::Vector2i> nodos = CPathFinding::PathFinding(origin,destination);

	m_path.setPrimitiveType(sf::LinesStrip);
	m_path.resize(nodos.size());
	int i = 0;

	//std::cout << "ShowPath: " << std::endl;
	for (std::list<sf::Vector2i>::iterator it = nodos.begin(); it != nodos.end(); it++) {
		sf::Vector2i posA = *it;
		sf::Vector2f pointA = CTileMap::worldMap.PosToMapCenter(posA);
		//std::cout << "		(" << posA.x << "," << posA.y << ")" << std::endl;
		m_path[i].position = pointA;

		i++;
	}
}

bool CTileMap::ChangeCollide(sf::Vector2i position) {
	bool retorno = true;
	if ((int)collisionMap.size() > position.x) {
		if ((int)collisionMap[position.x].size() > position.y)
			collisionMap[position.x][position.y] = (this->CollideMap(position) ? 0 : 1);

	}
	return retorno;
}
bool CTileMap::ChangeTexture(sf::Vector2i position, float tileNumber) {
	bool retorno = true;

	sf::Vertex * quad;
	quad = &m_vertices[(position.x + position.y * this->width) * 4];

	int tu = 0;
	int tv = 0;
	tu = (int)tileNumber % (this->m_tileset.getSize().x / this->tileSize.x);
	tv = tileNumber / (this->m_tileset.getSize().x / this->tileSize.x);

	float decimal = tileNumber - std::floor(tileNumber);
	sf::Vector2f halfTile(0,0);
	if (decimal != 0) {
		halfTile.x = tileSize.x / 2;
		halfTile.y = tileSize.y / 2;
	}
	quad[0].texCoords = sf::Vector2f(tu * tileSize.x + halfTile.x, tv * tileSize.y + halfTile.y);
	quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x + halfTile.x, tv * tileSize.y + halfTile.y);
	quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x + halfTile.x, (tv + 1) * tileSize.y + halfTile.y);
	quad[3].texCoords = sf::Vector2f(tu * tileSize.x + halfTile.x, (tv + 1) * tileSize.y + halfTile.y);

	return retorno;

}

void CTileMap::CreateWall(sf::Vector2i position, float defaultWall) {
	this->defaultWall = defaultWall;
	this->ChangeTexture(position, defaultWall);
	this->ChangeCollide(position);
}

void CTileMap::CreateWall(sf::Vector2i position) {
	if (this->defaultWall >= 0) {
		this->ChangeTexture(position, this->defaultWall);
		this->ChangeCollide(position);
	}
}

void CTileMap::RemoveWall(sf::Vector2i position, float defaultFloor) {
	this->defaultFloor = defaultFloor;
	this->ChangeTexture(position, defaultFloor);
	this->ChangeCollide(position);
}

void CTileMap::RemoveWall(sf::Vector2i position) {
	if (this->defaultFloor >= 0) {
		this->ChangeTexture(position, this->defaultFloor);
		this->ChangeCollide(position);
	}
}
