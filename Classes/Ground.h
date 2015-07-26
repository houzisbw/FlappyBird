#ifndef _GROUND_H_
#define _GROUND_H_
#include "cocos2d.h"
class Ground:public cocos2d::Layer
{
public:
	Ground();
	~Ground();
	virtual bool init();
	CREATE_FUNC(Ground);
	void moveGround();
private:
	float vx;//x÷·ÀŸ∂»
	cocos2d::Sprite* ground_1;
	cocos2d::Sprite* ground_2;

};

#endif

