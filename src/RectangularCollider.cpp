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
#include "RectangularCollider.h"
#include "GameObject.h"
#include "Vector2.h"

/**
* Instance constructor
* @param _pGameObject 
* @param _x offset X from the object's position
* @param _y offset Y from the object's position
* @param _width Width of the rect collider
* @param _height Height of the rect collider
*/
RectangularCollider::RectangularCollider (GameObject* _pGameObject, int _x, int _y, int _width, int _height) 
	: Collider(_pGameObject)
{
	x = _x;
	y = _y;
	width = _width;
	height = _height;
}

RectangularCollider::~RectangularCollider ( ) { /*nothing to do here*/ }

/**
 * Tests if a point defined by x,y screen coordinates collides with this object
 * @return bool
 * @param  x X screen coordinate of test point
 * @param  y Y screen coordinate of test point
 */
bool RectangularCollider::isColliding (int _x, int _y )
{
	Vector2 position(0,0);
	if(pGameObject)
	{
		pGameObject->getTransform().GetPosition(position);
	}
	//add the (x,y) offset
	position = position + Vector2(x,y);

	if(_x >= position.getX() && _x <= (position.getX() + width) &&
	   _y >= position.getY() && _y <= (position.getY() + height))
	{
		return true;
	}

	return false;
}


