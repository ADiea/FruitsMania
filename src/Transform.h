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
#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <string>
#include "Mat3.h"
#include "Vector2.h"

/**
  * class Transform
  * Keeps track of a GameObject's position and scaling. Rotation is not implemented
  * due to irrelevancce for this project but can be easily added because internally
  * transforms are stored as 3x3 matrixes.
  * [ Math reference: http://users.dsic.upv.es/~jlinares/grafics/Chapter%203.pdf ]
  */
class GameObject;
class Transform
{
public:
    /**
	 * Constructor
     * @param  pGameObject GameObject instance that this Transform is attached to. This
     * will be used to get the hierachy parent
     */
     Transform (GameObject* pGameObject);

    /**
     * Translates the object in local space relative to its previous position.
     * @param  translateVector The relative translation vector that is to be applied to
     * this object's localTransform
     */
    void Translate (Vector2& translateVector );


    /**
     * Scales the object in local space relative to it's previous scale
     * @param  scaleVector Scale vector used to scale the object
     */
    void Scale (Vector2& scaleVector );


    /**
     * Sets the absolute position of the object in local space
     * @param  position Final position of the object in local space
     */
    void SetPosition (Vector2& position );


    /**
     * Sets the absolute scale of the object in local space
     * @param  scale Final scale of the object in local space
     */
    void SetScale (Vector2& scale );


    /**
	 * Gets the absolute position of the object in local space
	 * @param result Storage for the position
	 */
    void GetLocalPosition (Vector2& result);


    /**
     * Gets the absolute scale of the object in local space
     * @param result Storage for the position
     */
    void GetLocalScale (Vector2& result);


    /**
     * Gets the absolute position of the object in world space
     * @param result Storage for the position
     */
    void GetPosition (Vector2& result);


    /**
     * Gets the absolute scale of the object in world space
     * @param result Storage for the position
     */
    void GetScale (Vector2& result);

	/**
	 * Returns the local transform matrix
	 * @return Mat3&
	 */
	Mat3& GetLocalTransform ( );

	/**
	 * Returns the final transform matrix
	 * @return Mat3&
	 */
	Mat3& GetFinalTransform ( );

private:
    // Transformation matrix (Ttranslates Scales Rotation) relative to object's own space. 
    Mat3 localTransform;
    // The resulting transform by multiplying object's localTransform with parent's transform. 
	//Useful for determining position/scaling in world-space coords. 
	//This is updated every time a transform is applied to the localTransform.
    Mat3 finalTransform;
    // GameObject instance that owns this Transform instance
    GameObject* mpGameObject;
};

#endif // TRANSFORM_H
