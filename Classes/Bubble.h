#ifndef _BUBBLE_H_
#define _BUBBLE_H_
#include "cocos2d.h"
#include "Player.h"

class Bubble:public cocos2d::Sprite
{
public:
	Bubble();
	~Bubble();
	virtual bool init();
	CREATE_FUNC(Bubble);
public:
	void moveBubble();
	void setSpeed(float vx);
	bool getIsTouch();
	void setIsTouch(bool it);
	
private:
	float vx;
	bool isTouch;
};
#endif
