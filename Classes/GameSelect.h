#ifndef _GAMESELECT_H_
#define _GAMESELECT_H_
#include "cocos2d.h"
class GameSelect :public cocos2d::Layer
{
public:
	GameSelect();
	~GameSelect();
	virtual bool init();
	CREATE_FUNC(GameSelect);
	static cocos2d::Scene* createScene();
	void lv1(Ref* r);
	void lv2(Ref* r);
	void lv3(Ref* r);
	void goMainMenu(Ref* r);
	static int lv_state;//游戏选关变量
	

};

#endif