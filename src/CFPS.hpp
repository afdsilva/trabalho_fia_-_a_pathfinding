/*
 * CFPS.hpp
 *
 *  Created on: 08/08/2013
 *      Author: andref
 */

#ifndef CFPS_HPP_
#define CFPS_HPP_

#include <SFML/System.hpp>

class CFPS {
public:
	static CFPS FPSControl;
	int maxFrame;
private:
	int oldTime;
	int lastTime;

	float speedFactor;

	int numFrames;
	int frames;

	sf::Clock clock;

public:
	CFPS();
	void OnLoop();

public:
	int GetFPS();
	float GetSpeedFactor();
};

#endif /* CFPS_HPP_ */
