#ifndef _RANK_H_
#define _RANK_H_
#include "cocos2d.h"
class Rank:public cocos2d::Layer
{
public:
	Rank();
	~Rank();
	virtual bool init();
	CREATE_FUNC(Rank);
	void goMainMenu(Ref* r);
	static cocos2d::Scene* createScene();
};
#endif

