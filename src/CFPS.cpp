/*
 * CFPS.cpp
 *
 *  Created on: 08/08/2013
 *      Author: andref
 */

#include "CFPS.hpp"

CFPS CFPS::FPSControl;

CFPS::CFPS() {
	this->maxFrame = 60;
	this->oldTime = 0;
	this->lastTime = 0;

	this->speedFactor = 0;

	frames = 0;
	numFrames = 0;
}

void CFPS::OnLoop() {
	sf::Time elapsed = clock.getElapsedTime();
	if (oldTime + 1000 < elapsed.asMilliseconds()) {
		oldTime = elapsed.asMilliseconds();
		numFrames = frames;
		frames = 0;
	}
	speedFactor = ((elapsed.asMilliseconds() - lastTime) / 1000.0f) * 32.0f;
	frames++;
	lastTime = elapsed.asMilliseconds();
}

int CFPS::GetFPS() {
	return numFrames;
}

float CFPS::GetSpeedFactor() {
	return speedFactor;
}
