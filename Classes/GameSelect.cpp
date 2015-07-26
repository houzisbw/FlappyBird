#include "GameSelect.h"
#include "GameScene.h"
#include "HelloWorldScene.h"
USING_NS_CC;
bool GameSelect::init()
{
	Size size = Director::getInstance()->getVisibleSize();
	Layer::init();
	auto bg = Sprite::create("bg.jpg");
	bg->setPosition(size.width/2,size.height/2);
	addChild(bg);
	//难度选择
	auto lv1_menu = MenuItemImage::create("bird_blue_0.png", "bird_blue_0.png", CC_CALLBACK_1(GameSelect::lv1, this)); //只能调用自己类的函数
	auto me1 = Menu::create(lv1_menu, NULL);
	addChild(me1);
	me1->setPosition(size.width / 2-60, size.height / 2+100);
	auto label_1 = LabelTTF::create("EASY", "Courier", 40);
	label_1->setPosition(size.width / 2+50, size.height / 2 + 100);
	addChild(label_1);

	auto lv2_menu = MenuItemImage::create("bird_blue_0.png", "bird_blue_0.png", CC_CALLBACK_1(GameSelect::lv2, this)); //只能调用自己类的函数
	auto me2 = Menu::create(lv2_menu, NULL);
	addChild(me2);
	me2->setPosition(size.width / 2 - 60, size.height / 2 );
	auto label_2 = LabelTTF::create("NORMAL", "Courier", 30);
	label_2->setPosition(size.width / 2 + 50, size.height / 2 );
	addChild(label_2);

	auto lv3_menu = MenuItemImage::create("bird_blue_0.png", "bird_blue_0.png", CC_CALLBACK_1(GameSelect::lv3, this)); //只能调用自己类的函数
	auto me3 = Menu::create(lv3_menu, NULL);
	addChild(me3);
	me3->setPosition(size.width / 2 - 60, size.height / 2-100);
	auto label_3 = LabelTTF::create("HARD", "Courier", 40);
	label_3->setPosition(size.width / 2 + 50, size.height / 2-100);
	addChild(label_3);

	//主菜单按钮
	auto goMenu = MenuItemImage::create("menu.jpg", "menu.jpg", CC_CALLBACK_1(GameSelect::goMainMenu,this));
	auto goback = Menu::create(goMenu, NULL);
	goback->setPosition(60, 30);
	addChild(goback);



	return true;
}
void GameSelect::goMainMenu(Ref* r)
{
	Director::getInstance()->replaceScene(HelloWorld::createScene());
}
void GameSelect::lv1(Ref* r)
{
	lv_state = 1;
	Director::getInstance()->replaceScene(GameScene::createScene());
}
void GameSelect::lv2(Ref* r)
{
	lv_state = 2;
	Director::getInstance()->replaceScene(GameScene::createScene());
}
void GameSelect::lv3(Ref* r)
{
	lv_state = 3;
	Director::getInstance()->replaceScene(GameScene::createScene());
}
Scene* GameSelect::createScene()
{
	auto scene = Scene::create();
	auto layer = GameSelect::create();
	scene->addChild(layer);


	return scene;
}
int GameSelect::lv_state=1;//游戏选关变量
GameSelect::GameSelect()
{
}


GameSelect::~GameSelect()
{
}
  