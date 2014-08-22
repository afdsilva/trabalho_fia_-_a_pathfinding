/*
 * CBoardMap.cpp
 *
 *  Created on: 21/08/2013
 *      Author: andref
 */

#include "CBoardMap.hpp"

CBoardMap CBoardMap::board;

BoardMove::BoardMove() {
	this->move = sf::Vector2i(-1,-1);
	this->value = -1;
	this->depth = 0;
}
BoardMove::BoardMove(sf::Vector2i move, int value, int depth) {
	this->move = move;
	this->value = value;
	this->depth = depth;
}
BoardMove::BoardMove(int value, int depth) {
	this->move = sf::Vector2i(-1,-1);
	this->value = value;
	this->depth = depth;
}


CBoardMap::CBoardMap() {
	this->size = sf::Vector2f(0,0);
	this->tileNumber = sf::Vector2i(0,0);
	this->player = PLAYER_1;
	this->lastPlayer = NO_PLAYER;
	this->playerWinner = NO_PLAYER;
	this->lastPosPlayed = sf::Vector2i(-1,-1);

}
void CBoardMap::NewGame() {
	this->player = PLAYER_1;
	this->lastPlayer = NO_PLAYER;
	this->playerWinner = NO_PLAYER;
	this->lastPosPlayed = sf::Vector2i(-1,-1);
	this->boardMap.clear();
}
void CBoardMap::NewGame(std::vector< std::vector<int> > boardMap) {
	this->player = PLAYER_1;
	this->lastPlayer = NO_PLAYER;
	this->playerWinner = NO_PLAYER;
	this->lastPosPlayed = sf::Vector2i(-1,-1);
	this->boardMap.clear();
	this->boardMap.resize(boardMap.size());

	for (unsigned int i = 0; i < boardMap.size();i++) {
		this->boardMap[i].resize(boardMap[i].size());
		for (unsigned int j = 0; j < boardMap[i].size();j++) {
			this->boardMap[i][j] = boardMap[i][j];
		}
	}
}
bool CBoardMap::Structure(sf::Vector2f size, sf::Vector2i tileNumber) {
	bool retorno = true;
	try {
		this->size = size;
		this->tileNumber = tileNumber;
		sf::Vector2i tileSize(this->size.x / this->tileNumber.x, this->size.y / this->tileNumber.y);
		m_vertices.setPrimitiveType(sf::Quads);
		m_vertices.resize(this->tileNumber.x * this->tileNumber.y * 4);
		m_circles.setPrimitiveType(sf::TrianglesFan);
		m_circles.resize(this->tileNumber.x * this->tileNumber.y * 30);
		boardMap.resize(tileNumber.x);
		for (int i = 0; i < this->tileNumber.x; i++) {
			boardMap[i].resize(tileNumber.y,NO_PLAYER);
			for (int j = 0; j < this->tileNumber.y; j++) {
				sf::Vertex * quad = &m_vertices[(i + j * this->tileNumber.x) * 4];
				//sf::Vertex * circle = &m_circles[(i + j * size.x) * 30];
				quad[0].position = sf::Vector2f(i * tileSize.x + this->getPosition().x+3, j * tileSize.y + this->getPosition().y+3);
				quad[1].position = sf::Vector2f((i + 1) * tileSize.x + this->getPosition().x-3, j * tileSize.y + this->getPosition().y+3);
				quad[2].position = sf::Vector2f((i + 1) * tileSize.x + this->getPosition().x-3, (j + 1) * tileSize.y + this->getPosition().y-3);
				quad[3].position = sf::Vector2f(i * tileSize.x + this->getPosition().x+3, (j + 1) * tileSize.y + this->getPosition().y-3);
				for (int k = 0;k < 4; k++)
					quad[k].color = sf::Color::White;
				//circle[0].position = sf::Vector2f(quad[0].position.x + (tileSize.x / 2), quad[0].position.y + (tileSize.y / 2));
			}

		}
	} catch (int e) {

	}
	return retorno;
}

void CBoardMap::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	// apply the transform
	states.transform *= getTransform();

	// apply the tileset texture
	//states.texture = &m_tileset;
	// draw the vertex array
	target.draw(m_vertices, states);

}

sf::Vector2f CBoardMap::PosToMap(sf::Vector2i posCoord) {
	sf::Vector2f retorno;
	try {
		sf::Vector2i tileSize(size.x / this->tileNumber.x, size.y / this->tileNumber.y);
		float x = this->getPosition().x + (posCoord.x * (tileSize.x * this->getScale().x));
		float y = this->getPosition().y + (posCoord.y * (tileSize.y * this->getScale().y));
		retorno = sf::Vector2f(x,y);
	} catch (int e) {
		retorno = sf::Vector2f(-1,-1);
	}
	return retorno;
}
sf::Vector2f CBoardMap::PosToMapCenter(sf::Vector2i posCoord) {
	sf::Vector2f retorno;
	try {
		sf::Vector2i tileSize(size.x / this->tileNumber.x, size.y / this->tileNumber.y);
		float x = this->getPosition().x + (posCoord.x * (tileSize.x * this->getScale().x)) + ((tileSize.x * this->getScale().x) / 2);
		float y = this->getPosition().y + (posCoord.y * (tileSize.y * this->getScale().y)) + ((tileSize.y * this->getScale().y) / 2);
		retorno = sf::Vector2f(x,y);
	} catch (int e) {
		retorno = sf::Vector2f(-1,-1);
	}
	return retorno;
}

sf::Vector2i CBoardMap::MapToPos(sf::Vector2f mapCoord) {
	sf::Vector2i retorno;
	try {
		sf::Vector2i tileSize(size.x / this->tileNumber.x, size.y / this->tileNumber.y);
		int i = floor((mapCoord.x - this->getPosition().x) / (tileSize.x * this->getScale().x));
		int j = floor((mapCoord.y - this->getPosition().y) / (tileSize.y * this->getScale().y));
		if  (i >= this->tileNumber.x || j >= this->tileNumber.y || i < 0 || j < 0)
			throw 1;
		retorno = sf::Vector2i(i,j);

	} catch (int e) {
		retorno = sf::Vector2i(-1,-1);
	}
	return retorno;
}

void CBoardMap::HighlightRow(sf::Vector2i pos) {
	//sf::Vector2i tileSize(this->size.x / this->tileNumber.x, this->size.y / this->tileNumber.y);

	for (int i = 0; i < this->tileNumber.x; i++) {
		for (int j = 0; j < this->tileNumber.y; j++) {
			sf::Vertex * quad = &m_vertices[(i + j * this->tileNumber.x) * 4];
			for (int k = 0;k < 4; k++)
				quad[k].color = sf::Color::White;

			if (i == pos.x) {
					for (int k = 0;k < 4; k++)
						quad[k].color = sf::Color::Green;
			}
		}
	}
}
void CBoardMap::ColorBoard() {
	for (int i = 0; i < this->tileNumber.x; i++) {
		for (int j = 0; j < this->tileNumber.y; j++) {
			sf::Vertex * quad = &m_vertices[(i + j * this->tileNumber.x) * 4];
			if (this->boardMap[i][j] == NO_PLAYER) {
				for (int k = 0;k < 4; k++)
					quad[k].color = sf::Color::White;
			} else if (this->boardMap[i][j] == PLAYER_1) {
				for (int k = 0;k < 4; k++)
					quad[k].color = sf::Color::Red;
			} else if (this->boardMap[i][j] == PLAYER_2) {
				for (int k = 0;k < 4; k++)
					quad[k].color = sf::Color::Blue;
			}
		}
	}
}
std::vector< std::vector<int> > CBoardMap::GetBoardMap() {
	std::vector< std::vector<int> > retorno;

	try {
		retorno.resize(boardMap.size());
		for (unsigned int i = 0; i < boardMap.size();i++) {
			retorno[i].resize(boardMap[i].size());
			for (unsigned int j = 0; j < boardMap[i].size();j++) {
				retorno[i][j] = boardMap[i][j];
			}
		}
		retorno = boardMap;
	} catch (int e) {
		retorno.clear();
	}

	return retorno;
}
sf::Vector2i CBoardMap::PlayerTurn(int column) {
	sf::Vector2i retorno;
	try {
		if (this->playerWinner != NO_PLAYER)
			throw 1;
		sf::Vector2i pos = sf::Vector2i(-1,-1);
		if ((pos = this->PosPlayable(column)) != sf::Vector2i(-1,-1)) {
			boardMap[pos.x][pos.y] = this->player;
			if (Win(pos,this->player)) {
				//std::cout << "Jogador " << this->player << " venceu a partida " << std::endl;
				this->playerWinner = this->player;
			} else {
				//salva ultimo jogador
				this->lastPlayer = this->player;
				//muda jogador
				this->player = this->player == PLAYER_1 ? PLAYER_2 : PLAYER_1;
				retorno = pos;
			}
		} else
			throw 1;
	} catch (int e) {
		retorno = sf::Vector2i(-1,-1);
	}
	//this->ShowBoard();
	return retorno;
}

void CBoardMap::UndoPlay(sf::Vector2i pos) {
	//volta a posicao
	this->boardMap[pos.x][pos.y] = NO_PLAYER;
	//troca jogador com ultimo jogador
	int aux = this->player;
	this->player = this->lastPlayer;
	this->lastPlayer = aux;
}

sf::Vector2i CBoardMap::PosPlayable(int column) {
	sf::Vector2i retorno;
	try {
		if (column < 0 || column >= this->tileNumber.x)
			throw 1;
		sf::Vector2i position = sf::Vector2i(-1,-1);

		for (int i = this->tileNumber.y-1; i >= 0; i--) {
			if (this->boardMap[column][i] == NO_PLAYER) {
				position = sf::Vector2i(column,i);
				break;
			}
		}
		if (position != sf::Vector2i(-1,-1)) {
			//std::cout << "Posicao Livre: " << position.x << " " << position.y << std::endl;
			retorno = position;
		} else {
			throw 1;
		}
	} catch (int e) {
		retorno = sf::Vector2i(-1,-1);
	}
	return retorno;
}
bool CBoardMap::Win(sf::Vector2i pos, int playerTurn) {
	bool retorno = false;
	try {
		/**
		int h,v,dp,ds;

		h = HorizontalWin(pos,this->player);
		v = VerticalWin(pos,this->player);
		dp = DiagonalPWin(pos,this->player);
		ds = DiagonalSWin(pos,this->player);
		//std::cout << "h: " << h << " v: " << v << " dp: " << dp << " ds: " << ds << std::endl;
		if (h == WIN || v == WIN || dp == WIN || ds == WIN)
			throw 1;
		**/
		if (this->boardMap[pos.x][pos.y] != 0) {
			int p = this->boardMap[pos.x][pos.y];
			retorno = (retorno) ? retorno : CheckFour(pos.x, pos.y, 1, 0, p);
			retorno = (retorno) ? retorno : CheckFour(pos.x, pos.y, 1, -1, p);
			retorno = (retorno) ? retorno : CheckFour(pos.x, pos.y, 0, 1, p);
			retorno = (retorno) ? retorno : CheckFour(pos.x, pos.y, 1, 1, p);
		}

	} catch (int e) {
		if (e == 1)
			retorno = true;
	}
	return retorno;

}
bool CBoardMap::NextWin(sf::Vector2i pos, int playerTurn) {
	bool retorno = false;
	try {
		int h,v,dp,ds;

		h = HorizontalWin(pos,this->player);
		v = VerticalWin(pos,this->player);
		dp = DiagonalPWin(pos,this->player);
		ds = DiagonalSWin(pos,this->player);
		//std::cout << "NextWin => h: " << h << " v: " << v << " dp: " << dp << " ds: " << ds << std::endl;
		if (h >= 100 || v >= 100 || dp >= 100 || ds >= 100)
			throw 1;

	} catch (int e) {
		if (e == 1)
			retorno = true;
	}
	return retorno;

}
bool CBoardMap::Lose(sf::Vector2i pos, int playerTurn) {
	bool retorno = false;
	try {
		int h,v,dp,ds;

		h = HorizontalWin(pos,this->player);
		v = VerticalWin(pos,this->player);
		dp = DiagonalPWin(pos,this->player);
		ds = DiagonalSWin(pos,this->player);
		if (h == LOSE || v == LOSE || dp == LOSE || ds == LOSE)
			throw 1;

	} catch (int e) {
		if (e == 1)
			retorno = true;
	}
	return retorno;

}

bool CBoardMap::NextLose(sf::Vector2i pos, int playerTurn) {
	bool retorno = false;
	try {
		int h,v,dp,ds;

		h = HorizontalWin(pos,this->player);
		v = VerticalWin(pos,this->player);
		dp = DiagonalPWin(pos,this->player);
		ds = DiagonalSWin(pos,this->player);
		//std::cout << "NextLose => h: " << h << " v: " << v << " dp: " << dp << " ds: " << ds << std::endl;
		if (h <= -100 || v <= -100 || dp <= -100 || ds <= -100)
			throw 1;

	} catch (int e) {
		if (e == 1)
			retorno = true;
	}
	return retorno;

}

void CBoardMap::IATurn(int player) {
	BoardMove resultado;
	try {
		std::cout  << std::endl << std::endl << std::endl << std::endl << "IA Jogando: " << player << std::endl;
		//this->ShowBoard();
		sf::Vector2i pos = sf::Vector2i(-1,-1);
		BoardMove alpha, beta;

		alpha = BoardMove(pos,-1000,0);
		beta = BoardMove(pos,1000,0);
		resultado = AlphaBeta(6,alpha,beta,true);

	} catch (sf::Vector2i & pos) {

	}
	PlayerTurn(resultado.move.x);
}

/**
 * Retorna a posicao de melhor avaliacao
 *
 */
BoardMove CBoardMap::AlphaBeta(int depth, BoardMove alpha, BoardMove beta, bool maximizing) {
	BoardMove retorno;
	retorno.move = sf::Vector2i(-1,-1);
	retorno.value = 0;
	try {
		//std::cout << "AlphaBeta Iniciado para Jogador " << this->player << std::endl;
		for (int i = 0; i < this->tileNumber.x; i++) {
			sf::Vector2i pos = this->PosPlayable(i);
			if (this->NextWin(pos,this->player)) {
				retorno = BoardMove(pos,WIN,depth);
				throw 1;
			}
		}
		if (depth == 0) {
			retorno.value = maximizing ? HeuristicCost() : -HeuristicCost();
			throw 4;
		}
		BoardMove resultado;
		/**/
		CBoardMap nBoard;
		std::vector<int> numbers;
		for (int i = 0; i < this->tileNumber.x; ++i) numbers.push_back(i);

		std::random_shuffle ( numbers.begin(), numbers.end() );
		//for (int i = 0; i < this->tileNumber.x; ++i)
		//	std::cout << "[" << i << "]: "<<  numbers[i] << " ";
		//std::cout << std::endl;
		sf::Vector2i pos;

		for (int i = 0; i < this->tileNumber.x; i++) {
			pos = this->PosPlayable(numbers[i]);
			//std::cout << "Criando Novo tabuleiro " << std::endl;
			nBoard = CBoardMap();
			nBoard.NewGame(this->GetBoardMap());
			nBoard.player = this->player;
			nBoard.Structure(this->size,this->tileNumber);
			//simula a jogada
			//std::cout << "Simulando jogada: " << numbers[i] << std::endl;
			nBoard.PlayerTurn(numbers[i]);
			BoardMove newAlpha = BoardMove(beta.move,-beta.value,depth-1);
			BoardMove newBeta = BoardMove(alpha.move,-alpha.value,depth-1);

			resultado = nBoard.AlphaBeta(depth-1,newAlpha,newBeta,!maximizing);
			//std::cout << "Mostrando Resultado.value" << resultado.value << std::endl;

			resultado.value = -resultado.value;
			resultado.move = pos;
			//std::cout << "move: (" << resultado.move.x << "," << resultado.move.y << ") value: " << resultado.value << " alpha.v: " << alpha.value << " melhor valor atual: (" << alpha.move.x << "," << alpha.move.y << ")" << std::endl;
			if (resultado.value > alpha.value) {
				//std::cout << "valor do alpha atualizado" << std::endl;
				alpha = BoardMove(pos,resultado.value,resultado.depth);
			}
			if (alpha.value >= beta.value) {
				retorno = beta;
				throw 2;
			}
		}
		if (alpha.move == sf::Vector2i(-1,-1))
			alpha.move = pos;
		retorno = alpha;
		throw 3;

	} catch (int e) {
		switch(e) {
		case 1:
			//std::cout << "Encontrou vencedor" << std::endl;
			break;
		case 2:
			//std::cout << "Poda Beta" << std::endl;
			break;
		case 3:
			//std::cout << "Poda Alpha" << std::endl;
			break;
		case 4:
			//std::cout << "Heuristica Aplicada" << std::endl;
			break;
		}
		//std::cout << "X: " << retorno.move.x << " Y: " << retorno.move.y  << " value: " << retorno.value << " depth: " << retorno.depth << std::endl;
	}

	//std::cout << retorno << " = AlphaBeta(" << depth << ", " << alpha.value << ", " << beta.value << "," << (maximizing ? "TRUE" : "FALSE") << ")" << std::endl;
	return retorno;
}

int CBoardMap::HeuristicCost() {
	int retorno = 0;

	std::vector<int> maxY;
	std::size_t tam = this->tileNumber.x;
	maxY.resize(tam);
	//pega proxima posicao valida para todas pecas em cada coluna tocando outra peca
	for (unsigned int i = 0; i < tam; i++) {
		maxY[i] = this->PosPlayable(i).y;
	}

	//acha a mais alta peca em cada coluna tocando outra peca
	std::vector<int> maxYH;
	maxYH.resize(tam);

	for (unsigned int i = 0; i < tam; i++) {
		maxYH[i] = (i > 0 && maxY[i-1] < maxY[i]) ? maxY[i-1] : maxY[i];
		maxYH[i] = (i < tam-1 && maxY[i+1] < maxY[i]) ? maxY[i+1] : maxY[i];
		maxYH[i] = std::min(0,maxYH[i]);
	}
	/**/
	std::cout << "Calculando Heuristica" << std::endl;
	sf::Clock relogio;
	for (unsigned int i = 0; i < tam; i++) {
		for (int j = maxYH[i]; j <= maxY[i]; j++) {
			if (this->boardMap[i][j] == NO_PLAYER) {
				this->boardMap[i][j] = PLAYER_1;
				//std::cout << "Verificando Heuristica para: (" << i << "," << j << ")" << std::endl;
				if (Win(sf::Vector2i(i,j),PLAYER_1)) {
					//std::cout << "retorno++" << std::endl;
					retorno++;
				}
				//this->ShowBoard();
				this->boardMap[i][j] = PLAYER_2;
				if (Win(sf::Vector2i(i,j),PLAYER_2)) {
					//std::cout << "retorno--" << std::endl;
					retorno--;
				}
				//this->ShowBoard();
				this->boardMap[i][j] = NO_PLAYER;
			}
		}
	}
	std::cout << "Heuristica calculada em " << relogio.getElapsedTime().asMicroseconds() << " ms valor: " << retorno << std::endl;
	/**/
	//std::cout << "Heuristica: " << retorno << std::endl;
	return retorno;
}

/**
 * Percorre o tabuleiro em busca de uma jogada horizontal promissora, retorna um peso conforme os vizinhos encontrados
 */

int CBoardMap::HorizontalWin(sf::Vector2i pos, int playerTurn) {

	int retorno = 0;
	int jogador, oponente, neutro;
	try {
		if (pos == sf::Vector2i(-1,-1))
			throw 10;
		/**
		 * Verifica na linha horizontal, todas possiveis jogadas em uma janela de 3 posicoes adjacentes a posicao dada
		 */
		for (int window = 0; window < 4; window++) {
			//zera as variaveis
			neutro = jogador = oponente = 0;
			for (int j = pos.x-window; j < pos.x+(4-window); j++) {
				//std::cout << "Checking POS: [" << j << ","<< pos.y << "]" << std::endl;
				if (j < 0 || j > this->tileNumber.x-1)
					continue;
				if (this->boardMap[j][pos.y] == 0) {
					//posicao vazia, verifica validade
					if (PosPlayable(j) == sf::Vector2i(j,pos.y)) {
						neutro++;
					}

				} else if (this->boardMap[j][pos.y] == playerTurn) {
					//posicao ocupada por uma peça do proprio jogador
					jogador++;
				} else {
					oponente++;
				}
			}
			//percorreu a janela, calculo da minha heuristica maneira
			//jogador tem peso 2, neutro tem peso 1, oponente tem peso -4
			retorno+= jogador * 2 + neutro - oponente * 4;
			//neutro == 3, todas posicoes sao boas para jogar (nao existe uma escolha boa)
			//jogador == 3, jogada que irá vencer o jogo
			if (jogador == 3)
				retorno+=100;
			if (oponente == 3)
				retorno-=100;
			if (jogador >= 4)
				throw 2;
			if (oponente >= 4)
				throw 4;
			//jogador == 4, jogador venceu (teste de win)
			//oponente == 3, qualquer outra jogada levará a vitoria do opontente
			//oponente == 4, oponente venceu (nao tem muito uso pratico...)
		}

	} catch (int e) {
		switch(e) {
		case 1:
			//jogada leva a vitoria
			retorno = 100;
			break;
		case 2:
			//jogada leva a impedimento de vitoria inimiga (nao sei se eh certo)
			retorno = WIN;
			break;
		case 3:
			retorno = -100;
			break;
		case 4:
			retorno = LOSE;
			break;
		default:
			retorno = 0;
			break;
		}
	}
	//std::cout << "retorno H: " << retorno << std::endl;
	return retorno;
}
int CBoardMap::VerticalWin(sf::Vector2i pos, int playerTurn) {
	int retorno = 0;
	try {
		if (pos == sf::Vector2i(-1,-1))
			throw 10;
		int jogador, oponente, neutro;
		for (int window = 0; window < 4; window++) {
			neutro = jogador = oponente = 0;
			for (int j = pos.y-window; j < pos.y+(4-window); j++) {
				if (j < 0 || j > this->tileNumber.y-1)
					continue;
				if (this->boardMap[pos.x][j] == 0) {
					neutro++;
				} else if (this->boardMap[pos.x][j] == playerTurn) {
					jogador++;
				} else {
					oponente++;
				}
			}
			retorno+= jogador * 2 + neutro - oponente * 4;
			if (jogador == 3)
				retorno+=100;
			if (oponente == 3)
				retorno-=100;
			if (jogador >= 4)
				throw 2;
			if (oponente >= 4)
				throw 4;
		}
	} catch (int e) {
		switch(e) {
		case 1:
			retorno = 100;
			break;
		case 2:
			retorno = WIN;
			break;
		case 3:
			retorno = -100;
			break;
		case 4:
			retorno = LOSE;
			break;
		default:
			retorno = 0;
			break;
		}
	}
	//std::cout << "retorno V: " << retorno << std::endl;
	return retorno;
}
int CBoardMap::DiagonalPWin(sf::Vector2i pos, int playerTurn) {
	int retorno = 0;
	try {
		if (pos == sf::Vector2i(-1,-1))
			throw 10;
		//diagonal principal
		//window = 0 => [pos.x,pos.y][pos.x+1,pos.y+1][pos.x+2,pos.y+2][pos.x+3,pos.y+3]
		//window = 1 => [pos.x-1,pos.y-1][pos.x,pos.y][pos.x+1,pos.y+1][pos.x+2,pos.y+2]
		//window = 2 => [pos.x-2,pos.y-2][pos.x-1,pos.y-1][pos.x,pos.y][pos.x+1,pos.y+1]
		//window = 3 => [pos.x-3,pos.y-3][pos.x-2,pos.y-2][pos.x-1,pos.y-1][pos.x,pos.y]
		int jogador, oponente, neutro;
		for (int window = 0; window < 4; window++) {
			neutro = jogador = oponente = 0;
			for (int j = pos.y-window, i=pos.x-window; j < pos.y+(4-window); j++, i++) {
				if ((j < 0 || j >= this->tileNumber.y) || (i < 0 || i >= this->tileNumber.x)) {
					continue;
				}
				if (this->boardMap[i][j] == 0) {
					neutro++;
				} else if (this->boardMap[i][j] == playerTurn) {
					jogador++;
				} else {
					oponente++;
				}
			}
			retorno+= jogador * 2 + neutro - oponente * 4;
			if (jogador == 3)
				retorno+=100;
			if (oponente == 3)
				retorno-=100;
			if (jogador >= 4)
				throw 2;
			if (oponente >= 4)
				throw 4;
		}
	} catch (int e) {
		switch(e) {
		case 1:
			retorno = 100;
			break;
		case 2:
			retorno = WIN;
			break;
		case 3:
			retorno = -100;
			break;
		case 4:
			retorno = LOSE;
			break;
		default:
			retorno = 0;
			break;
		}
	}
	//std::cout << "retorno DP: " << retorno << std::endl;
	return retorno;
}
int CBoardMap::DiagonalSWin(sf::Vector2i pos, int playerTurn) {
	int retorno = 0;
	try {
		if (pos == sf::Vector2i(-1,-1))
			throw 10;
		int jogador, oponente, neutro;
		for (int window = 0; window < 4; window++) {
			//diagonal secundaria
			//window = 0 => [pos.x,pos.y][pos.x+1,pos.y-1][pos.x+2,pos.y-2][pos.x+3,pos.y-3]
			//window = 1 => [pos.x-1,pos.y+1][pos.x,pos.y][pos.x+1,pos.y-1][pos.x+2,pos.y-2]
			//window = 2 => [pos.x-2,pos.y+2][pos.x-1,pos.y+1][pos.x,pos.y][pos.x+1,pos.y-1]
			//window = 3 => [pos.x-3,pos.y+3][pos.x-2,pos.y+2][pos.x-1,pos.y+1][pos.x,pos.y]
			neutro = jogador = oponente = 0;
			for (int j = pos.y-window, i=pos.x+window; j < pos.y+(4-window); j++, i--) {
				if ((j < 0 || j >= this->tileNumber.y) || (i < 0 || i >= this->tileNumber.x)) {
					continue;
				}
				if (this->boardMap[i][j] == 0) {
					neutro++;
				} else if (this->boardMap[i][j] == playerTurn) {
					jogador++;
				} else {
					oponente++;
				}
			}
			retorno+= jogador * 2 + neutro - oponente * 4;
			if (jogador == 3)
				retorno+=100;
			if (oponente == 3)
				retorno-=100;
			if (jogador >= 4)
				throw 2;
			if (oponente >= 4)
				throw 4;
		}
	} catch (int e) {
		switch(e) {
		case 1:
			retorno = -100;
			break;
		case 2:
			retorno = WIN;
			break;
		case 3:
			retorno = 100;
			break;
		case 4:
			retorno = LOSE;
			break;
		default:
			retorno = -1;
			break;
		}
	}
	if (retorno < 0)
		retorno = 0;
	//std::cout << "retorno DS: " << retorno << std::endl;
	return retorno;
}

bool CBoardMap::InsideBoard(int x, int y) {
	return (x >= 0 && x < this->tileNumber.x && y >= 0 && y <= this->tileNumber.y);
}
bool CBoardMap::CheckFour(int x, int y, int dx, int dy, int playerTurn) {
	bool retorno = false;

	try {
		int tam = 1;
		int i = 1;
		while(InsideBoard(x+dx*i,y+dy*i)) {
			if (this->boardMap[x+dx*i][y+dy*i] == playerTurn) {
				tam++;
				i++;
			} else
				break;
		}
		i = -1;
		while(InsideBoard(x+dx*i,y+dy*i)) {
			if (this->boardMap[x+dx*i][y+dy*i] == playerTurn) {
				tam++;
				i--;
			} else
				break;
		}
		if (tam>=4)
			throw 1;
	} catch (int e) {
		if (e == 1)
			retorno = true;
	}
	return retorno;
}

void CBoardMap::ShowBoard() {
	for (int j = 0; j < this->tileNumber.y; j++) {
		for (int i = 0; i < this->tileNumber.x; i++) {
			std::cout << "[P" << this->boardMap[i][j] << "]";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
	std::cout << std::endl;
}
