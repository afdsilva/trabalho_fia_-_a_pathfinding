/*
 * CStateManager.cpp
 *
 *  Created on: 19/06/2013
 *      Author: andref
 */

#include "CStateManager.hpp"

/**
 * States Includes
 */
#include "CStateIntro.hpp"
#include "CStateMenu.hpp"
#include "CStateGame.hpp"
#include "CStateGame2.hpp"


CState * CStateManager::activeState = 0;

void CStateManager::OnEvent(sf::Event * eventHandler) {
	if (activeState) activeState->GameEvent(eventHandler);

}
void CStateManager::OnLoop() {
	if (activeState) activeState->OnLoop();
}
void CStateManager::OnRender(sf::RenderWindow * window) {
	if (activeState) activeState->OnRender(window);
}

void CStateManager::SetActiveState(int stateId) {
	if (activeState) activeState->OnDeactivation();

	/**
	 * States
	 */
	switch(stateId) {
	case STATE_NONE:
		activeState = 0;
		break;
	case STATE_SPLASH:
		activeState = CStateIntro::GetIntance();
		break;
	case STATE_MENU:
		activeState = CStateMenu::GetIntance();
		break;
	case STATE_GAME:
		activeState = CStateGame::GetIntance();
		break;
	case STATE_GAME2:
		activeState = CStateGame2::GetIntance();
		break;
	case STATE_PAUSE:
		break;
	}
	if (activeState) activeState->OnActivation();
}
CState * CStateManager::GetActiveState() {
	return activeState;
}
int CStateManager::GetActiveStateId() {
	int retorno = STATE_NONE;
	//if (activeState == CStateSpash::GetInstance())
		//return STATE_SPLASH;
	/**
	 *
	 *
	 */
	return retorno;
}
