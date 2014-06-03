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
#include "GameTimer.h"
#include "GameStack.h"
/**
 * Constructs a GameTimer instance
 * @param  _timerId The ID of this timer instance
 * @param  timeoutValue Timeout value of this timer instance
 */
GameTimer::GameTimer (TimerIds _timerId, float timeoutValue )
	:currentTime(timeoutValue), timerId(_timerId), m_Pause(false)
{
}

/**
 * @param  frameTime Time interval of the last frame that will be subtracted from
 * currentTime
 */
void GameTimer::Update (float frameTime )
{
	if(m_Pause)
		return;
	//prevent firing twice
	if(currentTime >= 0)
	{
		currentTime -= frameTime;
		if(currentTime < 0)
		{
			//fire timeout event
			EventTimeout evt(timerId);
			GameStack::getGameStackInstance().OnEvent((EventType*)&evt);
		}
	}
}


/**
* @return the current time
*/
float GameTimer::GetCurrentTime ()
{
	return currentTime;
}

/**
* Pauses and unpauses the timer
*/
void GameTimer::Pause(bool bPause)
{
	m_Pause = bPause;
}





