#ifndef _GAMEOVER_H_
#define _GAMEOVER_H_
#include "cocos2d.h"
class GameOver:public cocos2d::Layer
{
public:
	GameOver();
	~GameOver();
	virtual bool init();
	CREATE_FUNC(GameOver);
	void restartGame(cocos2d::Ref* r);
	void goMenu(cocos2d::Ref* r);
private:
	cocos2d::LabelTTF *sl;
	cocos2d::LabelTTF* hsl;
};
#endif

