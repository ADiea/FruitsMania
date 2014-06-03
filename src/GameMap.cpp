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
#include "GameMap.h"
#include "GameJewel.h"
#include "RectangularCollider.h"
#include "EventTouch.h"
#include "EventTimeout.h"
#include "GameTimer.h"
#include <time.h>       /* time */


/**
* Constructor
* @param tilesX, tilesY number of tiles
* @param tileSize width and height of one tile
*/
GameMap::GameMap ( GameObject* parent, int tilesX, int tilesY, float tileSize, Rect& position)
	:GameObject(parent), m_jewelMoveState(STARTING), m_tilesX(tilesX), m_tilesY(tilesY),
	 m_tileSize(tileSize)
{
	//set up the transform
	transform.SetPosition(Vector2(position.x, position.y));
	transform.SetScale(Vector2(1,1));

	//create the game HUD
	m_HUD = boost::make_shared<GameHUD>(this, TEX_HUD, Rect(-297, 13, 130, 108));
	AddChild(boost::shared_ptr<GameObject>(m_HUD));

	//create the endgame timer with 60 second timeout
	m_Timer = boost::make_shared<GameTimer>(TIMER_ENDGAME, 60);
	timers.push_back(m_Timer);

	//create a rectangular collider for this object
	pCollider = new RectangularCollider(this, 0,0, position.width, position.height); 

	int i=0, j=0;

	//Construct the jewels map	
	pJewelsMap = new GameJewel**[tilesX];
	for(i=0;i<tilesX;i++)
	{
		pJewelsMap[i] = new GameJewel*[tilesY];
		for(j=0;j<tilesY;j++)
		{
			pJewelsMap[i][j] = NULL;
		}
	}
}

/**
* Destructor
*/
GameMap::~GameMap ( )
{
	//Deallocate the jewels map
	//Objects pointed to in the jewels map will not be destroyed here
	//They will be destroyed in ~GameObject 
	int i=0;
	for(;i<m_tilesX;i++)
	{
		//only use delete without []
		delete pJewelsMap[i];
	}
}


/**
* Updates the game logic.
* @param  frameTime Last frame time that is used as an inverse of the FPS to
* obtain FPS independent game behaviour
*/
void GameMap::EarlyUpdate (float frameTime )
{
	//update the HUD with the timer reading
	if(m_HUD.get() && m_Timer.get())
	{
		m_HUD.get()->setTime(m_Timer.get()->GetCurrentTime());
	}

	//the game's state machine is implemented here
	switch(m_jewelMoveState)
	{
	case STARTING:
		//check the status of the slowest jewel to determine
		//when the board is inited
		if(pJewelsMap[m_tilesX - 1][0] && !pJewelsMap[m_tilesX - 1][0]->IsMovementInProgress())
		{
			m_jewelMoveState = IDLE;
		}
		break;
	case SWITCHING_JEWELS:
		if(!pJewelsMap[m_sourceJewelTile.x][m_sourceJewelTile.y]->IsMovementInProgress() &&
		   !pJewelsMap[m_destJewelTile.x][m_destJewelTile.y]->IsMovementInProgress() )
		{
			GameJewel* saved = pJewelsMap[m_sourceJewelTile.x][m_sourceJewelTile.y];
			pJewelsMap[m_sourceJewelTile.x][m_sourceJewelTile.y] = pJewelsMap[m_destJewelTile.x][m_destJewelTile.y];
			pJewelsMap[m_destJewelTile.x][m_destJewelTile.y] = saved;

			if(SearchAndDestroyJewels(true))
			{
				m_jewelMoveState = DESTROYING_JEWELS;
				//Pause the game timer
				if(m_Timer.get())
				{
					m_Timer.get()->Pause(true);
				}
			}
			else /* switch jewels back if got no combination */
			{
				pJewelsMap[m_destJewelTile.x][m_destJewelTile.y]->MoveTo(
								Vector2(m_sourceJewelTile.x*m_tileSize, m_sourceJewelTile.y*m_tileSize), kJewelSwitchSpeed);
				pJewelsMap[m_sourceJewelTile.x][m_sourceJewelTile.y]->MoveTo(
								Vector2(m_destJewelTile.x*m_tileSize, m_destJewelTile.y*m_tileSize), kJewelSwitchSpeed);
			
				saved = pJewelsMap[m_sourceJewelTile.x][m_sourceJewelTile.y];
				pJewelsMap[m_sourceJewelTile.x][m_sourceJewelTile.y] = pJewelsMap[m_destJewelTile.x][m_destJewelTile.y];
				pJewelsMap[m_destJewelTile.x][m_destJewelTile.y] = saved;

				m_jewelMoveState = IDLE;
			}
		}

		break;	
	case DESTROYING_JEWELS:
	{
		//TODO: put broken diamonds into a destroy queue and only iterate through those
		bool allDestroyed = true;
		for(int i=0; i< m_tilesX; i++)
			for(int j=0; j < m_tilesY; j++)
			{
				if(pJewelsMap[i][j] && pJewelsMap[i][j]->IsBroken())
				{
					if(pJewelsMap[i][j]->IsBreakingAnimationInProgress())
					{
						allDestroyed = false;
					}
					else /* jewel destroyed, put it at the top, and move the rest down */ 
					{
						GameJewel* destroyed = pJewelsMap[i][j];
						int k=1;
						/*BUG*/float speed = kJewelMoveDownBaseSpeed*k;
						
						if(speed > kJewelMoveDownTopSpeed)
							speed = kJewelMoveDownTopSpeed;

						for(int k=j; k >0 ;k--)
						{
							pJewelsMap[i][k] = pJewelsMap[i][k-1];
							pJewelsMap[i][k]->MoveTo(Vector2(i*m_tileSize, k*m_tileSize), speed);
						}
						
						pJewelsMap[i][0] = destroyed;
						pJewelsMap[i][0]->setJewelType((JewelTypes)(JT_BLUE + rand()%5));
						pJewelsMap[i][0]->getTransform().SetPosition(Vector2(i*m_tileSize, -1*m_tileSize));
						pJewelsMap[i][0]->MoveTo(Vector2(i*m_tileSize, 0), kJewelMoveDownBaseSpeed);	
						pJewelsMap[i][0]->SetBroken(false);
						pJewelsMap[i][0]->getTransform().SetScale(Vector2(1,1));
					}

				}
			}
		
		if(allDestroyed)
		{
			m_jewelMoveState = MOVING_DOWN_JEWELS;
		}
	
		break;
	}
	case MOVING_DOWN_JEWELS:
	{
		bool allMoved = true;
		for(int i=0; i< m_tilesX; i++)
			for(int j=0; j < m_tilesY; j++)
			{
				if(pJewelsMap[i][j] && pJewelsMap[i][j]->IsMovementInProgress())
				{
					allMoved = false;
				}
			}
		
		if(allMoved)
		{
			if(SearchAndDestroyJewels(true))
			{
				m_jewelMoveState = DESTROYING_JEWELS;
			}
			else
			{
				m_jewelMoveState = IDLE;
				//Unpause the game timer
				if(m_Timer.get())
				{
					m_Timer.get()->Pause(false);
				}
			}
		}

		break;
	}

	};
}

/**Renders this gameObject.
* @param  frameTime Last frame time that is used as an inverse of the FPS to
* obtain FPS independent game behavior
*/
void GameMap::EarlyRender (float frameTime )
{
	// not doing any rendering on our own
}

/**
* Called the first frame to set things up in the gameobject. Called first by Start()
*/
void GameMap::EarlyStart ( )
{
	//Construct a random map. Make sure there are no 3 tiles already matched
	int i=0, j=0, k;
	srand(time(NULL));
	for(;i<m_tilesX;i++)
	{
		for(j=0;j<m_tilesY;j++)
		{
			//initialise every map location with a random jewel 
			GameJewelPtr jewel = boost::make_shared<GameJewel>(this, TEX_JEWEL_BLUE, Rect(0, 0, m_tileSize, m_tileSize));
		
			//Also add this as child node
			GameObjectPtr gameObject(jewel);
			AddChild(gameObject);

			pJewelsMap[i][j] = jewel.get();
			
			JewelTypes type = (JewelTypes)(JT_BLUE + rand()%5);
			jewel->getTransform().SetPosition(Vector2(i*m_tileSize, -1*m_tileSize));
			jewel->MoveTo(Vector2(i*m_tileSize, j*m_tileSize), kJewelMoveDownInitialSpeed*(i+j+1));

			do
			{
				jewel->setJewelType(type);	
				type = (JewelTypes)(JT_BLUE + rand()%5);

			}while(SearchAndDestroyJewels(false));			
		}
	}
}

/**
* Checks if there are 3 in a row on any row or column
* @param bDestroy If true, the matching jewels will be destroyed
* @return Returns true if matching jewels were found
*/
bool GameMap::SearchAndDestroyJewels(bool bDestroy)
{
	bool bResult = false;
	int i, j, marker;
	JewelTypes jewel;
	//check rows
	for(i=0; i<m_tilesX; i++)
	{
		for(j=0; j<m_tilesY; j++)
		{
			if(j==0)
			{
				marker = 0;
				if(!pJewelsMap[i][j])
					break;
				jewel = pJewelsMap[i][j]->getJewelType();
			}
			else
			{
				if(!pJewelsMap[i][j])
					break;
				if(jewel == pJewelsMap[i][j]->getJewelType())
				{
					marker++;
					if(marker == 2)
					{
						bResult = true;
						if(bDestroy)
						{
							pJewelsMap[i][j-2]->SetBroken(true);
							pJewelsMap[i][j-1]->SetBroken(true);
							pJewelsMap[i][j]->SetBroken(true);
							if(m_HUD.get())
							{
								m_HUD.get()->incrementScore(3);
							}
						}
					}
					else if(marker > 2 &&bDestroy)
					{
						pJewelsMap[i][j]->SetBroken(true);
						if(m_HUD.get())
						{
							m_HUD.get()->incrementScore(1);
						}
					}
				}
				else
				{
					marker = 0;
					jewel = pJewelsMap[i][j]->getJewelType();
				}
			}
		}
	}
	//check columns
	for(i=0; i<m_tilesX; i++)
	{
		for(j=0; j<m_tilesY; j++)
		{
			if(!pJewelsMap[j][i])
				break;

			if(j==0)
			{
				marker = 0;
				jewel = pJewelsMap[j][i]->getJewelType();
			}
			else
			{
				if(jewel == pJewelsMap[j][i]->getJewelType())
				{
					marker++;
					if(marker == 2)
					{
						bResult = true;
						if(bDestroy)
						{
							pJewelsMap[j-2][i]->SetBroken(true);
							pJewelsMap[j-1][i]->SetBroken(true);
							pJewelsMap[j][i]->SetBroken(true);
							if(m_HUD.get())
							{
								m_HUD.get()->incrementScore(3);
							}
						}
					}
					else if(marker > 2 &&bDestroy)
					{
						pJewelsMap[j][i]->SetBroken(true);
						if(m_HUD.get())
						{
							m_HUD.get()->incrementScore(1);
						}
					}
				}
				else
				{
					marker = 0;
					jewel = pJewelsMap[j][i]->getJewelType();
				}
			}
		}
	}
	return bResult;
}

/**Handles an event Called first by OnEvent
* @param  pEvent Pointer to an EventType abstract base class describing the event
* @return bool Return false to stop propagating this event 
*/
bool GameMap::EarlyOnEvent (EventType* pEvent )
{
	Vector2 pos(0,0);

	if(pEvent && pEvent->getType() == EVENT_TOUCH)
	{
		EventTouch* evTouch = dynamic_cast<EventTouch*>(pEvent);
		if(evTouch)
		{
			if(pCollider->isColliding(evTouch->getX(), evTouch->getY()) || (evTouch->getTouchType() == TOUCH_END))
			{
				//adjust touch event coords to local space
				getTransform().GetPosition(pos);
				pos.setX(evTouch->getX() - pos.getX());
				pos.setY(evTouch->getY() - pos.getY());

				int tX = pos.getX() / m_tileSize;
				int tY = pos.getY() / m_tileSize;

				if((tX >= 0 && tY >=0 &&
					tX < m_tilesX && tY < m_tilesY ) || (evTouch->getTouchType() == TOUCH_END))
				{
					//decide what to do with the touch for various states
					switch(m_jewelMoveState)
					{
					case IDLE:
						if(evTouch->getTouchType() == TOUCH_START)
						{
							m_sourceJewelTile.x = tX;
							m_sourceJewelTile.y = tY;
							m_jewelMoveState = SOURCE_JEWEL_SET;
						}
						break;
					case SOURCE_JEWEL_SET:
						if(evTouch->getTouchType() == TOUCH_START)
						{	
							int dx,dy;
							dx = tX - m_sourceJewelTile.x;
							dy = tY - m_sourceJewelTile.y;
							/* only up/down left/right neighbours allowed */
							if((dx == 0 && (dy == 1 || dy == -1 )) || 
							   (dy == 0 && (dx == 1 || dx == -1 ))) 
							{
								m_destJewelTile.x = tX;
								m_destJewelTile.y = tY;
								m_jewelMoveState = SWITCHING_JEWELS;
							}
							else /* a new source tile is set */
							{
								m_sourceJewelTile.x = tX;
								m_sourceJewelTile.y = tY;
							}
						}
						else if(evTouch->getTouchType() == TOUCH_END)
						{
							if(m_sourceJewelTile.x != tX ||
							   m_sourceJewelTile.y != tY)
							{
								//start from the source tile
								m_destJewelTile = m_sourceJewelTile;

								Vector2 centerSource(m_sourceJewelTile.x*m_tileSize + m_tileSize/2, 
													 m_sourceJewelTile.y*m_tileSize + m_tileSize/2);
								int dx, dy;
								//compute the absolute movement from the source point
								dx = centerSource.getX() > pos.getX() ? centerSource.getX() - pos.getX() : 
																		pos.getX() - centerSource.getX();

								dy = centerSource.getY() > pos.getY() ? centerSource.getY() - pos.getY() : 
																		pos.getY() - centerSource.getY();
								//determine if the movement was predominantly horizontal or vertical
								if(dx > dy)
								{
									if(centerSource.getX() > pos.getX())
									{
										m_destJewelTile.x--;
									}
									else
									{
										m_destJewelTile.x++;
									}
								}
								else
								{
									if(centerSource.getY() > pos.getY())
									{
										m_destJewelTile.y--;
									}
									else
									{
										m_destJewelTile.y++;
									}								
								}

								//in the end, if we have a valid tile we start switching the jewels
								if( m_destJewelTile.x >= 0 && m_destJewelTile.x < m_tilesX &&
									m_destJewelTile.y >= 0 && m_destJewelTile.y < m_tilesY )
								{
									m_jewelMoveState = SWITCHING_JEWELS;
								}
							}
						}

						//if the state changed to that of switching the jewels, start the switch
						if (m_jewelMoveState == SWITCHING_JEWELS)
						{
							pJewelsMap[m_sourceJewelTile.x][m_sourceJewelTile.y]->MoveTo(
								Vector2(m_destJewelTile.x*m_tileSize, m_destJewelTile.y*m_tileSize), kJewelSwitchSpeed);
							pJewelsMap[m_destJewelTile.x][m_destJewelTile.y]->MoveTo(
								Vector2(m_sourceJewelTile.x*m_tileSize, m_sourceJewelTile.y*m_tileSize), kJewelSwitchSpeed);
						}

						break;
					
					default:
						break;
					};
					//pJewelsMap[tX][tY]->ScaleTo(Vector2(0.5, 0.5), 2);	
					//pJewelsMap[tX][tY]->MoveTo(Vector2(tX*m_tileSize+m_tileSize/8, tY*m_tileSize+m_tileSize/8), 3);	
				}

				return false;
			}
		}
			
	}

	//not interested in this event let it bubble
	return true;
}

/**
* Get the value of tileSize
* Size of a rectangular tile
* @return the value of tileSize
*/
float GameMap::getTileSize ( )
{
	return m_tileSize;
}

/**
* Get the value of tilesX
* Number of horizontal tiles
* @return the value of tilesX
*/
int GameMap::getTilesX ( )
{
	return m_tilesX;
}

/**
* Get the value of tilesY
* Number of vertical tiles
* @return the value of tilesY
*/
int GameMap::getTilesY ( )
{	
	return m_tilesY;
}

/**
* Get the value of jewelMoveState
* Stores the state of the jewel moving process
* @return the value of jewelMoveState
*/
JewelMovePhase GameMap::getJewelMoveState ( )
{
	return m_jewelMoveState;
}
