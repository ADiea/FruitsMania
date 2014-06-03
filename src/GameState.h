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
#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <vector>

//Fwd declarations
class GameObject;
class EventType;

/**
  * class GameState
  * Abstract Base Class of a game state.
  */

class GameState
{
public:

    /**
     * Empty Constructor
     */
	GameState ( ) : pSceneRoot(NULL){}

    /**
     * Empty Destructor
     */
	virtual ~GameState ( ){}

    /**
     * Function called when GameState instance is pushed, to initialize it. It will
     * perform level loading and create the scene graph
     */
    virtual void Start ( ) = 0;

    /**
	 * Calls the Update function on the current Game State
     * @param  frameTime Last frame time that is used as an inverse of the FPS to
     * obtain FPS independent game behavior
     */
    virtual void Update (float frameTime )=0;

    /**
	 * Calls the Render function on the current Game State
     * @param  frameTime Last frame time that is used as an inverse of the FPS to
     * obtain FPS independent game behavior
     */
    virtual void Render (float frameTime )=0;

	/** 
	 * Handles an event and passes it along to its children if needed
     * @param  pEvent Pointer to an EventType abstract base class describing the event
	 * @return bool Return false to stop propagating this event
     */
    virtual bool OnEvent (EventType* pEvent ) = 0;

protected:

    // The scene root node
    GameObject* pSceneRoot;
};

#endif // GAMESTATE_H
