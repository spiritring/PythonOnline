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
	cocos2d::Vec2 m_vecBeginTouch;
	cocos2d::Vec2 m_vecEndTouch;

	TSDirection m_od;

	int m_dx = 1;
	int m_dy = 0;

	int m_createX = 24/2;
	int m_createY = 16/2;

	std::list<cocos2d::Node*> m_SnakeList;
};

#endif // __TSMENU_SCENE_H__
