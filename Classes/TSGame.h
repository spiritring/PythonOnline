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

#define  MAX_MAP_WIDTH 24
#define  MAX_MAP_HEIGHT 16
#define  BODY_PIX 40

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

	cocos2d::Vec2 m_vecBeginTouch;
	cocos2d::Vec2 m_vecEndTouch;

	TSDirection m_od = TSFingerRight;

	int m_dx = 1;
	int m_dy = 0;

	int m_bodySize = 5;

	int m_createX = MAX_MAP_WIDTH / 2;
	int m_createY = MAX_MAP_HEIGHT / 2;

	std::list<cocos2d::Node*> m_SnakeList;
};

#endif // __TSMENU_SCENE_H__
