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
#ifndef GAMEJEWEL_H
#define GAMEJEWEL_H
#include "GameDynamicObject.h"

enum JewelTypes
{
	JT_BLUE,
	JT_GREEN,
	JT_PURPLE,
	JT_RED,
	JT_YELLOW
};

const float kJewelScaleSpeed = 4.0f;
const float kJewelMoveCenterSpeed = 80.0f;

/**
  * class GameJewel
  * This implements game functionality for a jewel
  */
class GameJewel : public GameDynamicObject
{

public:
    /**
	 * Constructs a jewel
	 * @param parent The parent GameObject of this object
     * @param  textureID The texture id of this game object. 
     * @param  position The position and dimensions in parent space of this gameobject
     */
    GameJewel (GameObject *parent, TextureIds textureID, Rect position);

    /**
     * Empty Destructor
     */
    virtual ~GameJewel ( );

	/**
	 * Get the value of jewelType
	 * @return the value of jewelType
	 */
	JewelTypes getJewelType ( );

	/**
	 * Changes this jewel's type
	 * @param type The new type of the jewel
	 */
	void setJewelType(JewelTypes type);

    /**
     * Marks this jewel as broken then proceeds to scaling it down.
     */
    void SetBroken (bool broken );

	/**
	 * Returns true if the breaking animation is in progress
	 */
	bool IsBreakingAnimationInProgress();

	/**
	 * Get the value of bIsBroken
	 * @return the value of bIsBroken
	 */
	bool GameJewel::IsBroken ( );

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

    JewelTypes jewelType;
    bool bIsBroken;
};

#endif // GAMEJEWEL_H
