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
#include "GameHUD.h"
#include "SimpleRectRenderer.h"

/**
* Constructs the HUD
* @param parent The parent GameObject of this object
* @param  textureID The texture id of this game object. 
* @param  position The position and dimensions in parent space of this gameobject
*/
GameHUD::GameHUD (GameObject *parent, TextureIds textureID, Rect position)
	:SimpleRectGameObject(parent, textureID, position), m_score(0)
{

}

GameHUD::~GameHUD ( ) 
{ 

}

/**
* Called the first frame to set things up in the gameobject. Called first by Start()
*/
void GameHUD::EarlyStart ( )
{
	//construct score digits and add them as children
	m_ScoreUnitsDigit = boost::make_shared<SimpleRectGameObject>(this, TEX_DIGIT_0, Rect(180, -6, 25, 55));
	m_ScoreTensDigit = boost::make_shared<SimpleRectGameObject>(this, TEX_DIGIT_0, Rect(147, -6, 25, 55));
	AddChild(boost::shared_ptr<GameObject>(m_ScoreUnitsDigit));
	AddChild(boost::shared_ptr<GameObject>(m_ScoreTensDigit));

	//construct score digits and add them as children
	m_TimeUnitsDigit = boost::make_shared<SimpleRectGameObject>(this, TEX_DIGIT_0, Rect(180, 60, 25, 55));
	m_TimeTensDigit = boost::make_shared<SimpleRectGameObject>(this, TEX_DIGIT_0, Rect(147, 60, 25, 55));
	AddChild(boost::shared_ptr<GameObject>(m_TimeUnitsDigit));
	AddChild(boost::shared_ptr<GameObject>(m_TimeTensDigit));
}

/**Handles an event Called first by OnEvent
* @param  pEvent Pointer to an EventType abstract base class describing the event
* @return bool Return false to stop propagating this event 
*/
bool GameHUD::EarlyOnEvent (EventType* pEvent )
{
	return true;
}

/**
* Called to set the seconds remaining
*/
void GameHUD::setTime(int seconds)
{
	TextureIds newTexIdUnit = (TextureIds)( TEX_DIGIT_0 + seconds%10);
	TextureIds newTexIdTens = (TextureIds)( TEX_DIGIT_0 + (seconds/10)%10);
	SimpleRectRenderer* r = dynamic_cast<SimpleRectRenderer*>(m_TimeUnitsDigit.get()->getRenderer());
	if(r)
	{
		r->SetTexture(newTexIdUnit);
	}
	r = dynamic_cast<SimpleRectRenderer*>(m_TimeTensDigit.get()->getRenderer());
	if(r)
	{
		r->SetTexture(newTexIdTens);
	}	
}

/**
* Called to set up the score
*/
void GameHUD::setScore(int score)
{
	TextureIds newTexIdUnit = (TextureIds)( TEX_DIGIT_0 + score%10);
	TextureIds newTexIdTens = (TextureIds)( TEX_DIGIT_0 + (score/10)%10);
	SimpleRectRenderer* r = dynamic_cast<SimpleRectRenderer*>(m_ScoreUnitsDigit.get()->getRenderer());
	if(r)
	{
		r->SetTexture(newTexIdUnit);
	}
	r = dynamic_cast<SimpleRectRenderer*>(m_ScoreTensDigit.get()->getRenderer());
	if(r)
	{
		r->SetTexture(newTexIdTens);
	}
}

/**
* Called to increment the score
*/
void GameHUD::incrementScore(int increment)
{
	m_score += increment;
	setScore(m_score);
}