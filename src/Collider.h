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
#ifndef COLLIDER_H
#define COLLIDER_H

class GameObject;
/**
  * class Collider
  * Abstract collider class. Uses a gameObject to get the object's position
  */
class Collider
{
public:
    Collider ( GameObject* _pGameObject );
    virtual ~Collider ( );

	/**
     * Tests if a point defined by x,y screen coordinates collides with this object
     * @return bool
     * @param  x X coordinate value to test in ScreenCoords
     * @param  y Y coordinate value to test in ScreenCoords
     */
    virtual bool isColliding (int x, int y ) = 0;

protected:

    // The GameObject instance that contains this collider
    GameObject* pGameObject;
};

#endif // COLLIDER_H
