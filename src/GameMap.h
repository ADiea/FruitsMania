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
#ifndef GAMEMAP_H
#define GAMEMAP_H
#include "GameObject.h"
#include "GameHUD.h"
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

//Fwd declarations
class GameJewel;
typedef boost::shared_ptr<GameJewel> GameJewelPtr;


const float kJewelMoveDownInitialSpeed = 30.0f;
const float kJewelSwitchSpeed = 90.0f;
const float kJewelMoveDownBaseSpeed = 100.0f;
const float kJewelMoveDownTopSpeed = 1000.0f;

enum JewelMovePhase
{
	STARTING, //the jewels are falliung in from above at level start
	IDLE, //game is in idle state waiting for the player to pick a jewel
	SOURCE_JEWEL_SET, //player picked a source jewel
	SWITCHING_JEWELS, //player chose a valid destination jewel and the jewels are being switched
	DESTROYING_JEWELS, //some jewels are being destroyed
	MOVING_DOWN_JEWELS //jewels fall from above to fill in the empty spaces

};

// Contains a tile position
struct Tile
{
    int x, y;
};

class GameMap : public GameObject
{
public:
	/**
     * Constructor
     * @param tilesX, tilesY number of tiles
	 * @param tileSize width and height of one tile
     */
	GameMap ( GameObject* parent, int tilesX, int tilesY, float tileSize, Rect& position);
    virtual ~GameMap ( );

	/**
	* Checks if there are 3 in a row on any row or column
	* @param bDestroy If true, the matching jewels will be destroyed
	* @return Returns true if matching jewels were found
	*/
	bool SearchAndDestroyJewels(bool bDestroy);

	/**
     * Updates the game logic. Called first by Update()
     * @param  frameTime Last frame time that is used as an inverse of the FPS to
     * obtain FPS independent game behaviour
     */
    void EarlyUpdate (float frameTime );

    /**Renders this gameObject. Called first by Render()
     * @param  frameTime Last frame time that is used as an inverse of the FPS to
     * obtain FPS independent game behavior
     */
    void EarlyRender (float frameTime );

    /**
	 * Called the first frame to set things up in the gameobject. Called first by Start()
     */
    void EarlyStart ( );

    /**Handles an event Called first by OnEvent
     * @param  pEvent Pointer to an EventType abstract base class describing the event
	 * @return bool Return false to stop propagating this event 
     */
    bool EarlyOnEvent (EventType* pEvent );

private:

    // GameJewel objects matrix.
    GameJewel*** pJewelsMap;
    // Size of a rectangular tile
    float m_tileSize;
    // Number of horizontal tiles
    int m_tilesX;
    // Number of vertical tiles
    int m_tilesY;
    // Stores the state of the jewel moving process
    JewelMovePhase m_jewelMoveState;
    // Stores the tile of the jewel that will be moved
    Tile m_sourceJewelTile, m_destJewelTile;
	//game's HUD
	boost::shared_ptr<GameHUD> m_HUD;
	//game's one minute timer
	boost::shared_ptr<GameTimer> m_Timer;

public:

    /**
     * Get the value of tileSize
     * Size of a rectangular tile
     * @return the value of tileSize
     */
    float getTileSize ( );

    /**
     * Get the value of tilesX
     * Number of horizontal tiles
     * @return the value of tilesX
     */
    int getTilesX ( );

    /**
     * Get the value of tilesY
     * Number of vertical tiles
     * @return the value of tilesY
     */
    int getTilesY ( );

    /**
     * Get the value of jewelMoveState
     * Stores the state of the jewel moving process
     * @return the value of jewelMoveState
     */
    JewelMovePhase getJewelMoveState ( );
};

#endif // GAMEMAP_H
