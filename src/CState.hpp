/*
 * CState.hpp
 *
 *  Created on: 19/06/2013
 *      Author: andref
 */

#ifndef CSTATE_HPP_
#define CSTATE_HPP_
#include "CEvent.hpp"
#include <SFML/Graphics.hpp>

class CState : public CEvent {
public:
	CState();
public:
	virtual void OnActivation() = 0;
	virtual void OnDeactivation() = 0;
	virtual void OnLoop() = 0;
	virtual void OnRender(sf::RenderWindow * window) = 0;
};

#endif /* CSTATE_HPP_ */
