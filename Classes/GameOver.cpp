#include "GameOver.h"
#include "GameScene.h"
#include "HelloWorldScene.h"
#include "GameSelect.h"
USING_NS_CC;

bool GameOver::init()
{
	Layer::init();
	
	Size vs = Director::getInstance()->getVisibleSize();
	auto panel = Sprite::create("gameover.png");
	panel->setPosition(vs.width/2,vs.height/2+180);
	addChild(panel);

	auto board = Sprite::create("score.png");
	board->setPosition(vs.width / 2, vs.height / 2 +30);
	addChild(board);

	auto restart = MenuItemImage::create("start.png", "start.png", CC_CALLBACK_1(GameOver::restartGame, this));
	auto menu_start = Menu::create(restart, NULL);
	addChild(menu_start);
	menu_start->setPosition(vs.width / 2-80, vs.height / 2 - 110);

	auto go = MenuItemImage::create("rank.png", "rank.png", CC_CALLBACK_1(GameOver::goMenu, this));
	auto menu_go = Menu::create(go, NULL);
	addChild(menu_go);
	menu_go->setPosition(vs.width / 2 +80, vs.height / 2 - 110);
		
	char s[20];
	sprintf(s, "%d",GameScene::score/2);
	sl = LabelTTF::create(s, "Courier", 30);
	addChild(sl);
	sl->setPosition(250, 290);
	
	HelloWorld::highestScore = UserDefault::getInstance()->getIntegerForKey("highestScore");//必须在这里取得最高分
	HelloWorld::highestScore_normal = UserDefault::getInstance()->getIntegerForKey("highestScore_normal");
	HelloWorld::highestScore_hard = UserDefault::getInstance()->getIntegerForKey("highestScore_hard");
	
	if (GameSelect::lv_state == 1)
	{

		if (GameScene::score / 2 > HelloWorld::highestScore)
		{
			UserDefault::getInstance()->setIntegerForKey("highestScore", GameScene::score / 2);
			HelloWorld::highestScore = GameScene::score / 2;
			UserDefault::getInstance()->flush();//不能漏掉
		}
	}

	if (GameSelect::lv_state == 2)
	{

		if (GameScene::score / 2 > HelloWorld::highestScore_normal)
		{
			UserDefault::getInstance()->setIntegerForKey("highestScore_normal", GameScene::score / 2);
			HelloWorld::highestScore_normal = GameScene::score / 2;
			UserDefault::getInstance()->flush();//不能漏掉
		}
	}

	if (GameSelect::lv_state == 3)
	{

		if (GameScene::score / 2 > HelloWorld::highestScore_hard)
		{
			UserDefault::getInstance()->setIntegerForKey("highestScore_hard", GameScene::score / 2);
			HelloWorld::highestScore_hard = GameScene::score / 2;
			UserDefault::getInstance()->flush();//不能漏掉
		}
	}
	
	
	char s1[20];
	if (GameSelect::lv_state == 1)
	{
		sprintf(s1, "%d", HelloWorld::highestScore);
	}
	else if (GameSelect::lv_state == 2)
	{
		sprintf(s1, "%d", HelloWorld::highestScore_normal);
	}
	else if (GameSelect::lv_state == 3)
	{
		sprintf(s1, "%d", HelloWorld::highestScore_hard);
	}
	hsl = LabelTTF::create(s1, "Courier", 30);
	addChild(hsl);
	hsl->setPosition(250,230);


	//auto menu = Menui
	
	return true;

}
void GameOver::restartGame(cocos2d::Ref* r)
{
	Director::getInstance()->replaceScene( GameScene::createScene());
}
void GameOver::goMenu(cocos2d::Ref* r)
{
	Director::getInstance()->replaceScene(HelloWorld::createScene());
}
GameOver::GameOver()
{
}


GameOver::~GameOver()
{
}
