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
#include "GameDynamicObject.h"
#include "SimpleRectRenderer.h"
#include "RectangularCollider.h"
/**
* Constructs a dynamic rectangular game object 
* @param parent The parent GameObject of this object
* @param  textureID The texture id of this game object. 
* @param  position The position and dimensions in parent space of this gameobject
*/
GameDynamicObject::GameDynamicObject (GameObject* parent, TextureIds textureID, Rect position )
	:GameObject(parent), finalPosition(0,0), finalScale(1,1)
{
	//Create a simple rectangular renderer
	pRenderer = new SimpleRectRenderer(this, textureID, position.width, position.height);
	//set up the transform
	transform.SetPosition(Vector2(position.x, position.y));
	transform.SetScale(Vector2(1,1));
	//create a rectangular collider for this object
	pCollider = new RectangularCollider(this, 0,0, position.width, position.height); 
}

GameDynamicObject::~GameDynamicObject ( ) { }

/**
* Updates the game logic. Called first by Update()
* @param  frameTime Last frame time that is used as an inverse of the FPS to
* obtain FPS independent game behaviour
*/
void GameDynamicObject::EarlyUpdate (float frameTime )
{
	Vector2 currentPos(0,0);

	if(bTranslationInProgress)
	{
		getTransform().GetLocalPosition(currentPos);

		if((currentPos - finalPosition).sqLength() > kAllowedError)
		{
			getTransform().Translate((finalPosition - currentPos).Normal()*(frameTime*translationSpeed));
		}
		else
		{
			bTranslationInProgress = false;
			getTransform().SetPosition(finalPosition);
		}
	}

	if(bScalingInProgress)
	{
		getTransform().GetLocalScale(currentPos);

		if((currentPos - finalScale).sqLength() > kAllowedErrorScaling)
		{
			getTransform().Scale((finalScale - currentPos).Normal()*(frameTime*scalingSpeed));
		}
		else
		{
			bScalingInProgress = false;
			getTransform().SetScale(finalScale);
		}
	}
}


/**Renders this gameObject. Called first by Render()
* @param  frameTime Last frame time that is used as an inverse of the FPS to
* obtain FPS independent game behavior
*/
void GameDynamicObject::EarlyRender (float frameTime )
{
	if(pRenderer)
	{
		pRenderer->Render(frameTime);
	}
}

/**
 * Moves the object to a final position with a linear speed
 * @param  finalPos Final position to move to. In world space
 * @param  moveSpeed Speed of the movement
 */
void GameDynamicObject::MoveTo (Vector2& finalPos, float moveSpeed )
{
	bTranslationInProgress = true;
	finalPosition = finalPos;
	translationSpeed = moveSpeed;
}

/**
 * Scales the object to a final scaling factor with a linear speed
 * @param  finalScale Final scaling the object should have
 * @param  scalingSpeed The speed to scale towards the final scaling with
 */
void GameDynamicObject::ScaleTo (Vector2& _finalScale, float _scalingSpeed)
{
	bScalingInProgress = true;
	finalScale = _finalScale;
	scalingSpeed = _scalingSpeed;
}

/**
 * Returns true if a translation operation is in progress
 * @return bool
 */
bool GameDynamicObject::IsMovementInProgress ( )
{
	return bTranslationInProgress;
}

/**
 * Returns true if a scaling operation is in progress
 * @return bool
 */
bool GameDynamicObject::IsScalingInProgress ( )
{
	return bScalingInProgress;
}



