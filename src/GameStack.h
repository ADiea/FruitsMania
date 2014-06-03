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
#ifndef GAMESTACK_H
#define GAMESTACK_H
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <stack>

//Fwd declarations
class EventType;
class GameState;

typedef boost::shared_ptr<GameState> GameStatePtr;

/**
  * class GameStack
  * GameStack singletone. This holds the game's state stack. It's functionality is
  *	invoked from the main game's loop
  */

class GameStack
{
public:
    /**
     * @return the GameStack instance
     */
    static GameStack& getGameStackInstance ( )
	{	// Instantiated on first use.
		static GameStack instance;
		return instance;
    }

    /**
     * Public Destructor
     */
    ~GameStack ( );

    /**
     * Pushes a new GameState instance
     * @param  _gameState New GameState to be pushed onto the stack and inited
     */
    void PushState (GameStatePtr& _gameState );

    /**
     * Deinitializes and pops the current GameState.
     * @return bool True if the stack is not empty
     */
    bool PopState ( );

    /**
     * Sets a flag to pop the current state on the next update
     */
	void PopStateNextFrame(){bShouldPopState = true;}

    /**
	 * Calls the Update function on the current Game State
     * @param  frameTime Last frame time that is used as an inverse of the FPS to
     * obtain FPS independent game behavior
	 * @return bool Returns false if there is no or an invalid state pushed onto the stack
	 *			Returning false will end the game.
     */
    bool Update (float frameTime );

    /**
	 * Calls the Render function on the current Game State
     * @param  frameTime Last frame time that is used as an inverse of the FPS to
     * obtain FPS independent game behavior
	 * @return bool Returns false if there is no or an invalid state pushed onto the stack
	 *			Returning false will end the game.
     */
    bool Render (float frameTime );

    /**
     * @param  pEvent Pointer to the event that has occured
     */
    void OnEvent (EventType* pEvent );

private:
	/* Declare constructor copy-ctor and asignment op private*/
	GameStack (){bShouldPopState = false;}
	GameStack(GameStack const&){}
	void operator=(GameStack const&){}

	/* The stack that holds the game's states*/
    std::stack<GameStatePtr> mStack;

	bool bShouldPopState;
};

#endif // GAMESTACK_H
