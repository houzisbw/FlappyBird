#include "Rank.h"
#include "HelloWorldScene.h"
USING_NS_CC;
bool Rank::init()
{
	Size s = Director::getInstance()->getVisibleSize();
	
	Layer::init();
	Size size = Director::getInstance()->getVisibleSize();
	auto bg = Sprite::create("bg.jpg");
	bg->setPosition(size.width / 2, size.height / 2); 
	addChild(bg);
	
	//主菜单按钮
	auto goMenu = MenuItemImage::create("menu.jpg", "menu.jpg", CC_CALLBACK_1(Rank::goMainMenu, this));
	auto goback = Menu::create(goMenu, NULL);
	goback->setPosition(60, 30);
	addChild(goback);

	//分数显示
	HelloWorld::highestScore = UserDefault::getInstance()->getIntegerForKey("highestScore");
	char s1[20];
	sprintf(s1, "EASY:  %d", HelloWorld::highestScore);
	auto label_easy = LabelTTF::create(s1, "Courier", 40);
	addChild(label_easy);
	label_easy->setPosition(s.width / 2, s.height - 50);


	HelloWorld::highestScore_normal = UserDefault::getInstance()->getIntegerForKey("highestScore_normal");
	char s2[20];
	sprintf(s2, "NORMAL:  %d", HelloWorld::highestScore_normal);
	auto label_normal = LabelTTF::create(s2, "Courier", 40);
	addChild(label_normal);
	label_normal->setPosition(s.width / 2, s.height - 150);


	HelloWorld::highestScore_hard = UserDefault::getInstance()->getIntegerForKey("highestScore_hard");
	char s3[20];
	sprintf(s3, "HARD:  %d", HelloWorld::highestScore_hard);
	auto label_hard = LabelTTF::create(s3, "Courier", 40);
	addChild(label_hard);
	label_hard->setPosition(s.width / 2, s.height - 250);
	
	return true;
}
Scene* Rank::createScene()
{
	auto scene = Scene::create();
	auto layer = Rank::create();
	scene->addChild(layer);

	return scene;
}
void Rank::goMainMenu(Ref* r)
{
	Director::getInstance()->replaceScene(HelloWorld::createScene());
}
Rank::Rank()
{
}


Rank::~Rank()
{
}
