#ifndef __TSGAME_SCENE_H__
#define __TSGAME_SCENE_H__

#include "cocos2d.h"

enum TSDirection
{
	TSFingerLeft,
	TSFingerRight,
	TSFingerDown,
	TSFingerUp
};

enum TSGoods
{
	TSMapNull = 0,
	TSMapRock = 1,
};

#define  MAX_MAP_WIDTH 24
#define  MAX_MAP_HEIGHT 16
#define  BODY_PIX 40

class TSSprite
{
public:
	cocos2d::Node* m_spr = nullptr;
	int m_mapX = 0;
	int m_mapY = 0;
};

class TSGame : public cocos2d::Layer
{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(TSGame);

	bool TouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	void TouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	void TouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
	void TouchCancelled(cocos2d::Touch* touch, cocos2d::Event* event);

	void OnDirection(TSDirection od);

	void GameUpdate(float delta);

private:
	int m_Map[MAX_MAP_WIDTH][MAX_MAP_HEIGHT];

	cocos2d::Node* m_csMainScene = nullptr;
	cocos2d::Node* m_csGameLayer = nullptr;

	cocos2d::Vec2 m_vecBeginTouch;
	cocos2d::Vec2 m_vecEndTouch;

	TSDirection m_od = TSFingerRight;

	int m_dx = 1;
	int m_dy = 0;

	int m_bodySize = 10;

	int m_createX = MAX_MAP_WIDTH / 2;
	int m_createY = MAX_MAP_HEIGHT / 2;

	std::list<TSSprite*> m_SnakeList;
};

#endif // __TSMENU_SCENE_H__
