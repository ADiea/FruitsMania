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
#ifndef SIMPLERECTGAMEOBJECT_H
#define SIMPLERECTGAMEOBJECT_H
#include "GameObject.h"
#include "ResourceManager.h"

/**
  * class SimpleRectGameObject
  * A simple GameObject implementation where the Renderer is a SimpleRectRenderer
  * and has no collision.
  */
class SimpleRectGameObject : public GameObject
{
public:
    /**
	 * Constructs a simple rectangular game object 
	 * @param parent The parent GameObject of this object
     * @param  textureID The texture id of this game object. 
     * @param  position The position and dimensions in parent space of this gameobject
     */
     SimpleRectGameObject (GameObject *parent, TextureIds textureID, Rect position );

	/**
     * Updates the game logic. Called first by Update()
     * @param  frameTime Last frame time that is used as an inverse of the FPS to
     * obtain FPS independent game behaviour
     */
	 virtual void EarlyUpdate (float frameTime ){}

    /**Renders this gameObject. Called first by Render()
     * @param  frameTime Last frame time that is used as an inverse of the FPS to
     * obtain FPS independent game behavior
     */
    virtual void EarlyRender (float frameTime );

    /**Handles an event Called first by OnEvent
     * @param  pEvent Pointer to an EventType abstract base class describing the event
	 * @return bool Return false to stop propagating this event 
     */
	virtual bool EarlyOnEvent (EventType* pEvent ){return true;} /*let the event bubble up*/

    /**
	 * Called the first frame to set things up in the gameobject. Called first by Start()
     */
	void EarlyStart ( ){}

};

#endif // SIMPLERECTGAMEOBJECT_H
