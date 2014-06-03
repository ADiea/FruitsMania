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
#include "GameJewel.h"
#include "SimpleRectRenderer.h"

/**
* Constructs a jewel
* @param parent The parent GameObject of this object
* @param  textureID The texture id of this game object. 
* @param  position The position and dimensions in parent space of this gameobject
*/
GameJewel::GameJewel (GameObject *parent, TextureIds textureID, Rect position)
	:GameDynamicObject(parent, textureID, position)
{
	//determine the jewel type
	jewelType = (JewelTypes)( (textureID - TEX_JEWEL_BLUE) + JT_BLUE);
	bIsBroken = false;
}

GameJewel::~GameJewel ( ) 
{ 

}

/**
* Called the first frame to set things up in the gameobject. Called first by Start()
*/
void GameJewel::EarlyStart ( )
{

}

/**Handles an event Called first by OnEvent
* @param  pEvent Pointer to an EventType abstract base class describing the event
* @return bool Return false to stop propagating this event 
*/
bool GameJewel::EarlyOnEvent (EventType* pEvent )
{
	return true;
}

/**
* Changes this jewel's type
* @param type The new type of the jewel
*/
void GameJewel::setJewelType(JewelTypes type)
{
	jewelType = type;
	TextureIds newTexId = (TextureIds)( (jewelType - JT_BLUE) + TEX_JEWEL_BLUE);
	SimpleRectRenderer *r = dynamic_cast<SimpleRectRenderer*>(getRenderer());
	if(r)
	{
		r->SetTexture(newTexId);
	}
}

/**
 * Get the value of jewelType
 * @return the value of jewelType
 */
JewelTypes GameJewel::getJewelType ( ) 
{
    return jewelType;
}

/**
 * Get the value of bIsBroken
 * @return the value of bIsBroken
 */
bool GameJewel::IsBroken ( ) {
    return bIsBroken;
}

/**
 * Marks this jewel as broken then proceeds to scaling it down.
 */
void GameJewel::SetBroken (bool broken )
{
	Vector2 pos(0,0), size(0,0);
	SimpleRectRenderer* rectRenderer=NULL;

	if(bIsBroken != broken)
	{
		bIsBroken = broken;
		if(bIsBroken)
		{
			getTransform().GetLocalPosition(pos);
			if(pRenderer)
			{
				rectRenderer = dynamic_cast<SimpleRectRenderer*>(pRenderer);
				if(rectRenderer)
				{
					rectRenderer->GetSize(size);
					size = size * 0.5;
				}
			}
			ScaleTo(Vector2(.1f, .1f), kJewelScaleSpeed);
			MoveTo(pos+size, kJewelMoveCenterSpeed);
		}
	}
}

/**
* Returns true if the breaking animation is in progress
*/
bool GameJewel::IsBreakingAnimationInProgress()
{
	return bIsBroken && (IsScalingInProgress() || IsMovementInProgress());
}
