/*
 * CStateIntro.hpp
 *
 *  Created on: 19/06/2013
 *      Author: andref
 */

#ifndef CSTATEINTRO_HPP_
#define CSTATEINTRO_HPP_

#include "CState.hpp"
#include "CEntity.hpp"
#include <SFML/Graphics.hpp>

class CStateIntro : public CState {
private:
	static CStateIntro instance;
	sf::Clock tempoInicio;

	CEntity logo;

private:
	CStateIntro();

public:
	void OnActivation();
	void OnDeactivation();
	void OnLoop();
	void OnRender(sf::RenderWindow * window);

public:
	static CStateIntro * GetIntance();

	void KeyPressed(sf::Event::KeyEvent keyEvent);
};

#endif /* CSTATEINTRO_HPP_ */
