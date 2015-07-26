#include "HelloWorldScene.h"
#include "GameScene.h"
#include "Ground.h"
#include "SimpleAudioEngine.h"
#include "GameSelect.h"
#include "Rank.h"
using namespace CocosDenshion;
USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}
bool HelloWorld::isSaveFile()
{
	if (!UserDefault::getInstance()->getBoolForKey("score"))
	{
		UserDefault::getInstance()->setBoolForKey("score", true);
		//设置3个不同难度的分数
		UserDefault::getInstance()->setIntegerForKey("highestScore", 0);
		UserDefault::getInstance()->setIntegerForKey("highestScore_normal", 0);
		UserDefault::getInstance()->setIntegerForKey("highestScore_hard", 0);
		//写入
		UserDefault::getInstance()->flush();
		return false;
	}
	else
		return true;
}
int HelloWorld::getHighestScore()
{
	if (isSaveFile())
	{
		highestScore = UserDefault::getInstance()->getIntegerForKey("highestScore");
		return highestScore;
	}
	else
		return 0;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	
	//////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	isSaveFile();
	
	
	//背景
	auto bg = Sprite::create("bg.jpg");
	addChild(bg);
	bg->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	auto title = Sprite::create("main.png");
	addChild(title);
	title->setPosition(visibleSize.width / 2, visibleSize.height - 100);
	
	//开始按钮
	auto menuImage = MenuItemImage::create("start.png", "start.png", CC_CALLBACK_1(HelloWorld::gameStart, this));
	auto menuStart = Menu::create(menuImage, NULL);
	menuStart->setPosition(visibleSize.width / 2, visibleSize.height-220);
	addChild(menuStart);

	//分数查看
	auto lookup = MenuItemImage::create("rank.png", "rank.png", CC_CALLBACK_1(HelloWorld::gameLookup, this));
	auto menuLookup = Menu::create(lookup, NULL);
	menuLookup->setPosition(visibleSize.width / 2, visibleSize.height - 320);
	addChild(menuLookup);

	g = Ground::create();//创建地板
	g->setPosition(0, -50);
	addChild(g);

	//创建小鸟 
	mPlayer = Player::create();
	mPlayer->setPosition(visibleSize.width / 2, visibleSize.height -50);
	addChild(mPlayer);
	
	this->schedule(SEL_SCHEDULE(&HelloWorld::gameStep), 0.02f);
    
    return true;
}
void HelloWorld::gameStep(float dt)
{
	g->moveGround();
}

int HelloWorld::highestScore = 0;
int HelloWorld::highestScore_normal = 0;
int HelloWorld::highestScore_hard = 0;

void HelloWorld::gameStart(Ref* r)
{
	Director::getInstance()->replaceScene(TransitionSlideInB::create(0.5, GameSelect::createScene()));
}
void HelloWorld::gameLookup(Ref* r)
{
	Director::getInstance()->replaceScene(TransitionSlideInB::create(0.5, Rank::createScene()));
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
