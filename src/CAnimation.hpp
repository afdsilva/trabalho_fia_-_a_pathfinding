/*
 * CAnimation.hpp
 *
 *  Created on: 14/08/2013
 *      Author: andref
 */

#ifndef CANIMATION_HPP_
#define CANIMATION_HPP_

#include <SFML/System.hpp>

class CAnimation {
private:
	sf::Clock clock;

	int currentFrame;
	int frameInc;

	int frameRate;
	long oldTime;

public:
	CAnimation();

	int maxFrames;
	bool oscillate;

	void OnAnimate();

	void SetFrameRate(int rate);
	void SetCurrentFrame(int frame);
	int GetCurrentFrame();

};

#endif /* CANIMATION_HPP_ */
