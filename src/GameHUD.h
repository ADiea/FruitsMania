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
#ifndef GAMEHUD_H
#define GAMEHUD_H
#include "SimpleRectGameObject.h"
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

/**
  * class GameHUD
  * This implements game functionality for a HUD displaying time and score
  */
class GameHUD : public SimpleRectGameObject
{

public:
    /**
	 * Constructs the HUD
	 * @param parent The parent GameObject of this object
     * @param  textureID The texture id of this game object(hud background). 
     * @param  position The position and dimensions in parent space of this gameobject
     */
    GameHUD (GameObject *parent, TextureIds textureID, Rect position);

    /**
     * Empty Destructor
     */
    virtual ~GameHUD ( );

    /**
	 * Called to set the seconds remaining
     */
	void setTime(int seconds);

    /**
	 * Called to set up the score
     */
	void setScore(int score);

    /**
	 * Called to increment the score
     */
	void incrementScore(int increment);

    /**
	 * Called the first frame to set things up in the gameobject. Called first by Start()
     */
    virtual void EarlyStart ( );

    /**Handles an event Called first by OnEvent
     * @param  pEvent Pointer to an EventType abstract base class describing the event
	 * @return bool Return false to stop propagating this event 
     */
    virtual bool EarlyOnEvent (EventType* pEvent );

private:
	
	//the current score
	int m_score;
	//two dogits of the score
    boost::shared_ptr<SimpleRectGameObject> m_ScoreUnitsDigit;
	boost::shared_ptr<SimpleRectGameObject> m_ScoreTensDigit;
	//two dogits of the time
	boost::shared_ptr<SimpleRectGameObject> m_TimeUnitsDigit;
	boost::shared_ptr<SimpleRectGameObject> m_TimeTensDigit;

};

#endif // GameHUD_H
