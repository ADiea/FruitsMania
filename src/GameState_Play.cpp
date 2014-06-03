/*
This file is part of the FruitsMania game project, distributed under the MIT license.

Repository: https://github.com/AndreiDiea/fruitsMania
Description: FruitsMania is a SDL match-three concept/prototype game.
Copyright: (c) 2014 Andrei Diea

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
 */
#include "GameState_Play.h"
#include "GameState_Menu.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "SimpleRectGameObject.h"
#include "EventType.h"
#include "EventTouch.h"
#include "EventTimeout.h"
#include "GameState.h"
#include "GameState_Play.h"
#include "GameStack.h"
#include "GameMap.h"

GameState_Play::GameState_Play ( ) 
{}

GameState_Play::~GameState_Play ( ) 
{ 
	if(pSceneRoot)
	{
		delete pSceneRoot;
		pSceneRoot = NULL;
	}
}

/**
* Function called when GameState instance is pushed, to initialize it. It will
* perform level loading and create the scene graph
*/
void GameState_Play::Start ( )
{
	int i=0,j=0;
	/*Consruct the main menu scene*/
	
	//Step 1: Load scene's textures
	ResourceManager::getResourceManager().LoadTexture(TEX_MAINMENU, "res/BackGround.jpg");
	ResourceManager::getResourceManager().LoadTexture(TEX_JEWEL_BLUE, "res/Blue.png");
	ResourceManager::getResourceManager().LoadTexture(TEX_JEWEL_GREEN, "res/Green.png");
	ResourceManager::getResourceManager().LoadTexture(TEX_JEWEL_PURPLE, "res/Purple.png");
	ResourceManager::getResourceManager().LoadTexture(TEX_JEWEL_RED, "res/Red.png");
	ResourceManager::getResourceManager().LoadTexture(TEX_JEWEL_YELLOW, "res/Yellow.png");
	ResourceManager::getResourceManager().LoadTexture(TEX_FOREGROUND, "res/foreground.png");
	ResourceManager::getResourceManager().LoadTexture(TEX_DIGIT_0, "res/0.png");
	ResourceManager::getResourceManager().LoadTexture(TEX_DIGIT_1, "res/1.png");
	ResourceManager::getResourceManager().LoadTexture(TEX_DIGIT_2, "res/2.png");
	ResourceManager::getResourceManager().LoadTexture(TEX_DIGIT_3, "res/3.png");
	ResourceManager::getResourceManager().LoadTexture(TEX_DIGIT_4, "res/4.png");
	ResourceManager::getResourceManager().LoadTexture(TEX_DIGIT_5, "res/5.png");
	ResourceManager::getResourceManager().LoadTexture(TEX_DIGIT_6, "res/6.png");
	ResourceManager::getResourceManager().LoadTexture(TEX_DIGIT_7, "res/7.png");
	ResourceManager::getResourceManager().LoadTexture(TEX_DIGIT_8, "res/8.png");
	ResourceManager::getResourceManager().LoadTexture(TEX_DIGIT_9, "res/9.png");	
	ResourceManager::getResourceManager().LoadTexture(TEX_HUD, "res/hud.png");
	

	//Stept 2: Create scene's objects and construct the hierarchy
	pSceneRoot = new SimpleRectGameObject(NULL, TEX_MAINMENU, Rect(0,0,755, 600));
	if(pSceneRoot)
	{
		
		GameObjectPtr pMap = boost::make_shared<GameMap>
									   (pSceneRoot, 8,8,45,  Rect(314, 93, 360, 360));
		pSceneRoot->AddChild(pMap);
		
		GameObjectPtr pForeground = boost::make_shared<SimpleRectGameObject>
									   (pSceneRoot, TEX_FOREGROUND, Rect(234,31, 513, 432));
		pSceneRoot->AddChild(pForeground);
	
		//in the end, call the start method on the hierarchy
		pSceneRoot->Start();
	}
}

/**
* Calls the Update function on the current Game State
* @param  frameTime Last frame time that is used as an inverse of the FPS to
* obtain FPS independent game behavior
*/
void GameState_Play::Update (float frameTime )
{
	if(pSceneRoot)
	{
		pSceneRoot->Update(frameTime);
	}
}

/**
* Calls the Render function on the current Game State
* @param  frameTime Last frame time that is used as an inverse of the FPS to
* obtain FPS independent game behavior
*/
void GameState_Play::Render (float frameTime )
{
	if(pSceneRoot)
	{
		pSceneRoot->Render(frameTime);
	}
}

/** 
* Handles an event and passes it along to its children if needed
* @param  pEvent Pointer to an EventType abstract base class describing the event
* @return bool Return false to stop propagating this event
*/
bool GameState_Play::OnEvent (EventType* pEvent )
{
	if(pEvent && pEvent->getType() == EVENT_TIMEOUT)
	{
		EventTimeout *timer = dynamic_cast<EventTimeout*>(pEvent);
		if(timer && timer->getExpiredTimer() == TIMER_ENDGAME)
		{
			GameStack::getGameStackInstance().PopStateNextFrame();
		}
	}
	if(pSceneRoot)
	{
		return pSceneRoot->OnEvent(pEvent);
	}
	return false;
}


