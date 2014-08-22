/*
 * CStateManager.hpp
 *
 *  Created on: 19/06/2013
 *      Author: andref
 */

#ifndef CSTATEMANAGER_HPP_
#define CSTATEMANAGER_HPP_

enum {
	STATE_NONE,
	STATE_SPLASH,
	STATE_MENU,
	STATE_GAME,
	STATE_GAME2,
	STATE_PAUSE
};

#include "CState.hpp"

class CStateManager {
private:
	static CState * activeState;

public:
	static void OnEvent(sf::Event * eventHandler);
	static void OnLoop();
	static void OnRender(sf::RenderWindow * window);

public:
	static void SetActiveState(int stateId);
	static CState * GetActiveState();
	static int GetActiveStateId();
};

#endif /* CSTATEMANAGER_HPP_ */
