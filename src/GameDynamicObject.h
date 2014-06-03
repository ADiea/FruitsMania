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
#ifndef GAMEDYNAMICOBJECT_H
#define GAMEDYNAMICOBJECT_H
#include "GameObject.h"
#include "ResourceManager.h"

const float kAllowedError = 0.3f;
const float kAllowedErrorScaling = 0.05f;
/**
  * class GameDynamicObject
  * This implements a dynamic object who's position and scaling can be animated over
  * time
  */
class GameDynamicObject : public GameObject
{
public:

    /**
	 * Constructs a simple rectangular game object 
	 * @param parent The parent GameObject of this object
     * @param  textureID The texture id of this game object. 
     * @param  position The position and dimensions in parent space of this gameobject
     */
     GameDynamicObject (GameObject *parent, TextureIds textureID, Rect position );

    /**
     * Empty Destructor
     */
    virtual ~GameDynamicObject ( );

	/**
     * Updates the game logic. Called first by Update()
     * @param  frameTime Last frame time that is used as an inverse of the FPS to
     * obtain FPS independent game behaviour
     */
	 virtual void EarlyUpdate (float frameTime );


    /**Renders this gameObject. Called first by Render()
     * @param  frameTime Last frame time that is used as an inverse of the FPS to
     * obtain FPS independent game behavior
     */
    virtual void EarlyRender (float frameTime );

    /**
     * Moves the object to a final position with a linear speed
     * @param  finalPos Final position to move to. In world space
     * @param  moveSpeed Speed of the movement
     */
    void MoveTo (Vector2& finalPos, float moveSpeed );


    /**
     * Scales the object to a final scaling factor with a linear speed
     * @param  finalScale Final scaling the object should have
     * @param  scalingSpeed The speed to scale towards the final scaling with
     */
    void ScaleTo (Vector2& _finalScale, float _scalingSpeed);


    /**
     * Returns true if a translation operation is in progress
     * @return bool
     */
    bool IsMovementInProgress ( );


    /**
     * Returns true if a scaling operation is in progress
     * @return bool
     */
    bool IsScalingInProgress ( );

private:

	// True if a translation operation is in progress
    bool bTranslationInProgress;    
	// The final position this object should have
    Vector2 finalPosition;
    // The spped to translate with
    float translationSpeed;

	// True if a scaling operation is in progress
    bool bScalingInProgress;
    // The final scaling this object should have
    Vector2 finalScale;
    // The spped to scale with
    float scalingSpeed;
};

#endif // GAMEDYNAMICOBJECT_H
