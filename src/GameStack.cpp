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
#include "GameStack.h"
#include "GameState.h"

//Destructor
GameStack::~GameStack ( ) 
{ 
	while(PopState())
		;
}

/**
 * Pushes a new GameState instance
 * @param  _gameState New GameState to be pushed onto the stack and inited
 */
void GameStack::PushState (GameStatePtr& _gameState )
{
	if(_gameState)
	{
		mStack.push(_gameState);
		//run the initialisation method
		_gameState->Start();
	}
}


/**
 * Deinitializes and pops the current GameState.
 * @return bool
 */
bool GameStack::PopState ( )
{
	if(!mStack.empty())
	{
		//deinit top GameState
		mStack.top().reset();
		//pop it
		mStack.pop();
	}
	return false;
}


/**
* Calls the Update function on the current Game State
* @param  frameTime Last frame time that is used as an inverse of the FPS to
* obtain FPS independent game behavior
* @return bool Returns false if there is no or an invalid state pushed onto the stack
*			Returning false will end the game.
*/
bool GameStack::Update (float frameTime )
{
	GameState *topState = NULL;
	bool bResult = false;

	if(bShouldPopState)
	{
		bShouldPopState = false;
		PopState();
		/* Stay in the game if more states left on the stack */
		if(!mStack.empty())
		{
			bResult = true;
		}
	}
	else
	{
		if(!mStack.empty())
		{
			topState = mStack.top().get();
			if(topState)
			{
				topState->Update(frameTime);
				bResult = true;
			}
		}
	}
	return bResult;
}

/**
* Calls the Render function on the current Game State
* @param  frameTime Last frame time that is used as an inverse of the FPS to
* obtain FPS independent game behavior
* @return bool Returns false if there is no or an invalid state pushed onto the stack
*			Returning false will end the game.
*/
bool GameStack::Render (float frameTime )
{
	GameState *topState = NULL;
	if(!mStack.empty())
	{
		topState = mStack.top().get();
		if(topState)
		{
			topState->Render(frameTime);
			return true;
		}
	}
	return false;
}

/**
 * @param  pEvent Pointer to the event that has occured
 */
void GameStack::OnEvent (EventType* pEvent )
{
	GameState *topState = NULL;
	if(!mStack.empty())
	{
		topState = mStack.top().get();
		if(topState)
		{
			topState->OnEvent(pEvent);
		}
	}
}


