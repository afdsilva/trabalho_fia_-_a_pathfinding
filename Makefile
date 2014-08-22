#Compilador
CC=g++

OBJETOS=./src/CAnimation.o CEntity.o CEvent.o CFPS.o CPathfinding.o CState.o CStateGame.o CStateGame2.o CStateIntro.o CStateManager.o CStateMenu.o CTileMap.o CBoardMap.o Game.o

CPPFLAGS=-O0 -g3 -Wall

LDFLAGS=-lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system

EXECUTAVEL=mAle_ai_games

MATRICULA=11107587

REVISION=1.21

DATE=20130830

BASE_FILENAME=trabalho_fia[$(MATRICULA)]-$(DATE)-$(REVISION)

all: $(OBJETOS)
	rm -rf $(EXECUTAVEL)
	$(CC) $(OBJETOS) $(LDFLAGS) -o $(EXECUTAVEL)
CAnimation.o: src/CAnimation.hpp src/CAnimation.cpp 
	rm -rf CAnimation.o
	$(CC) $(CPPFLAGS) -c src/CAnimation.cpp
CEntity.o: src/CEntity.hpp src/CEntity.cpp
	rm -rf CEntity.o
	$(CC) $(CPPFLAGS) -c src/CEntity.cpp
CEvent.o: src/CEvent.hpp src/CEvent.cpp
	rm -rf CEvent.o
	$(CC) $(CPPFLAGS) -c src/CEvent.cpp
CFPS.o: src/CFPS.hpp src/CFPS.cpp
	rm -rf CFPS.o
	$(CC) $(CPPFLAGS) -c src/CFPS.cpp
CPathfinding.o: src/CPathfinding.hpp src/CPathfinding.cpp
	rm -rf CPathfinding.o
	$(CC) $(CPPFLAGS) -c src/CPathfinding.cpp
CState.o: src/CState.hpp src/CState.cpp
	rm -rf CState.o
	$(CC) $(CPPFLAGS) -c src/CState.cpp
CStateGame.o: src/CStateGame.hpp src/CStateGame.cpp
	rm -rf CStateGame.o
	$(CC) $(CPPFLAGS) -c src/CStateGame.cpp
CStateGame2.o: src/CStateGame2.hpp src/CStateGame2.cpp
	rm -rf CStateGame2.o
	$(CC) $(CPPFLAGS) -c src/CStateGame2.cpp
CStateIntro.o: src/CStateIntro.hpp src/CStateIntro.cpp
	rm -rf CStateIntro.o
	$(CC) $(CPPFLAGS) -c src/CStateIntro.cpp
CStateManager.o: src/CStateManager.hpp src/CStateManager.cpp
	rm -rf CStateManager.o
	$(CC) $(CPPFLAGS) -c src/CStateManager.cpp
CStateMenu.o: src/CStateMenu.hpp src/CStateMenu.cpp
	rm -rf CStateMenu.o
	$(CC) $(CPPFLAGS) -c src/CStateMenu.cpp
CTileMap.o: src/CTileMap.hpp src/CTileMap.cpp
	rm -rf CTileMap.o
	$(CC) $(CPPFLAGS) -c src/CTileMap.cpp
CBoardMap.o: src/CBoardMap.hpp src/CBoardMap.cpp
	rm -rf CBoardMap.o
	$(CC) $(CPPFLAGS) -c src/CBoardMap.cpp
Game.o: src/Game.hpp src/Game.cpp
	rm -rf Game.o
	$(CC) $(CPPFLAGS) -c src/Game.cpp

runtime:
	sudo apt-add-repository ppa:sonkun/sfml-development
	sudo apt-get update
	sudo apt-get install libsfml

dev:
	sudo apt-add-repository ppa:sonkun/sfml-development
	sudo apt-get update
	sudo apt-get install libsfml
	sudo apt-get install libsfml-dbg
	sudo apt-get install libsfml-dev
	sudo apt-get install libsfml-doc
	sudo apt-get install sfml-examples

clean:
	rm -rf $(OBJETOS)	
	rm -rf $(EXECUTAVEL)

package:
ifeq ($(wildcard $(BASE_FILENAME).tar.gz),)
	mkdir $(BASE_FILENAME)
	cp -R README Makefile src/ img/ snd/ fonts/ $(BASE_FILENAME)/
	#tar -zcvf $(BASE_FILENAME).tar.gz $(BASE_FILENAME)/
	zip -r $(BASE_FILENAME).zip $(BASE_FILENAME)/
	rm -R $(BASE_FILENAME)/
endif
