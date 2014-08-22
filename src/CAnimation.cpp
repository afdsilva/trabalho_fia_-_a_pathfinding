/*
 * CAnimation.cpp
 *
 *  Created on: 14/08/2013
 *      Author: andref
 */

#include "CAnimation.hpp"

CAnimation::CAnimation() {
	this->currentFrame = 0;
	this->maxFrames = 0;
	this->frameInc = 1;

	this->frameRate = 100; //millisecconds
	this->oldTime = 0;

	this->oscillate = false;

}

void CAnimation::OnAnimate() {
	if (this->frameRate > clock.getElapsedTime().asMilliseconds()) {
		return;
	}

	clock.restart();

	this->currentFrame += this->frameInc;

	if (this->oscillate) {
		if (this->frameInc > 0) {
			if (this->currentFrame >= this->maxFrames) {
				this->frameInc = -this->frameInc;
			}
		} else {
			if (this->currentFrame <= 0) {
				this->frameInc = -this->frameInc;
			}
		}
	} else {
		if (this->currentFrame >= this->maxFrames) {
			this->currentFrame = 0;
		}
	}
}


void CAnimation::SetFrameRate(int rate) {
	this->frameRate = rate;
}

void CAnimation::SetCurrentFrame(int frame) {
	if (frame < 0 || frame >= this->maxFrames)
		return;

	this->currentFrame = frame;
}

int CAnimation::GetCurrentFrame() {
	return this->currentFrame;
}
