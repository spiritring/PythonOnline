#include "TSGame.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include <iostream>
#include "base/CCRef.h"

USING_NS_CC;

using namespace cocostudio::timeline;
using namespace std;

Scene* TSGame::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = TSGame::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool TSGame::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	auto rootNode = CSLoader::createNode("MainScene.csb");
	addChild(rootNode);

	auto _touchListener = EventListenerTouchOneByOne::create();
	_touchListener->setSwallowTouches(false);
	_touchListener->onTouchBegan = CC_CALLBACK_2(TSGame::TouchBegan, this);
	_touchListener->onTouchMoved = CC_CALLBACK_2(TSGame::TouchMoved, this);
	_touchListener->onTouchEnded = CC_CALLBACK_2(TSGame::TouchEnded, this);
	_touchListener->onTouchCancelled = CC_CALLBACK_2(TSGame::TouchCancelled, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(_touchListener, this);

	this->schedule(CC_SCHEDULE_SELECTOR(TSGame::GameUpdate), 0.5f);
	return true;
}

bool TSGame::TouchBegan(Touch* touch, Event* event)
{
	m_vecBeginTouch = touch->getLocation();
	cout << "ccTouchBegan" << endl;
	return true;
}

void TSGame::TouchMoved(Touch* touch, Event* event)
{
}

void TSGame::TouchEnded(Touch* touch, Event* event)
{
	m_vecEndTouch = touch->getLocation();

	auto vec = m_vecEndTouch - m_vecBeginTouch;
	auto p = (180.0f / 3.14f) * atan2f(vec.y, vec.x);

	if (p >= -45 && p < 45) 
	{
		OnDirection(TSFingerRight);
	}
	else if (p >= 45 && p < 135)
	{
		OnDirection(TSFingerUp);
	}
	else if (p >= 135 && p < 181 || p >= -181 && p < -135)
	{
		OnDirection(TSFingerLeft);
	}
	else if (p >= -135 && p < -45)
	{
		OnDirection(TSFingerDown);
	}
}

void TSGame::TouchCancelled(Touch* touch, Event* event)
{
	CCLOG("ccTouchCancelled");
}

void TSGame::OnDirection(TSDirection od)
{
	m_od = od;
	if (od == TSFingerUp)
	{
		m_dx = 0;
		m_dy = 1;
	}
	else if (od == TSFingerDown)
	{
		m_dx = 0;
		m_dy = -1;
	}
	else if (od == TSFingerLeft)
	{
		m_dx = -1;
		m_dy = 0;
	}
	else if (od == TSFingerRight)
	{
		m_dx = 1;
		m_dy = 0;
	}
}

void TSGame::GameUpdate(float delta)
{
	m_createX += m_dx;
	m_createY += m_dy;

	if (m_createY < 0) 
	{
		m_createY = MAX_MAP_HEIGHT - 1;
	}
	else if (m_createY >= MAX_MAP_HEIGHT)
	{
		m_createY = 0;
	}

	if (m_createX < 0)
	{
		m_createX = MAX_MAP_WIDTH - 1;
	}
	else if (m_createX >= MAX_MAP_WIDTH)
	{
		m_createX = 0;
	}

	auto sprBody = CSLoader::createNode("SnakeBody.csb");
	sprBody->setPosition(Point(BODY_PIX * m_createX, BODY_PIX * m_createY));
	addChild(sprBody);

	m_SnakeList.push_back(sprBody);
	if (m_SnakeList.size() > m_bodySize)
	{
		removeChild(m_SnakeList.front());
		m_SnakeList.pop_front();
	}

	for(auto iter : m_SnakeList)
	{
		auto sprBody = static_cast<Sprite*>(iter->getChildByName("Body"));
		auto sprHead = static_cast<Sprite*>(iter->getChildByName("Head"));
		
		if (iter == m_SnakeList.back())
		{
			sprBody->setVisible(false);
			sprHead->setVisible(true);
			if (m_od == TSFingerUp)
			{
				sprHead->setRotation(270);
			}
			else if (m_od == TSFingerDown)
			{
				sprHead->setRotation(90);
			}
			else if (m_od == TSFingerLeft)
			{
				sprHead->setRotation(180);
			}
			else if (m_od == TSFingerRight)
			{
				sprHead->setRotation(0);
			}
		}
		else
		{
			sprBody->setVisible(true);
			sprHead->setVisible(false);
		}
	}
}
