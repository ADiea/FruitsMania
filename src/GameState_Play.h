/*
 * This source/header file is part of a test interview and is created & copyrighted (c) Andrei Diea <diea_andrei@yahoo.com> 2014
 * and is not to be distributed or used for commercial purposes without author consent.
 */
#ifndef GAMESTATE_PLAY_H
#define GAMESTATE_PLAY_H
#include "GameState.h"

class GameState_Play : public GameState
{
public:
    /**
     * Empty Constructor
     */
    GameState_Play ( );

    /**
     * Empty Destructor
     */
    virtual ~GameState_Play ( );

	/**
     * Function called when GameState instance is pushed, to initialize it. It will
     * perform level loading and create the scene graph
     */
	virtual void Start ( );

    /**
	 * Calls the Update function on the current Game State
     * @param  frameTime Last frame time that is used as an inverse of the FPS to
     * obtain FPS independent game behavior
     */
    virtual void Update (float frameTime );

    /**
	 * Calls the Render function on the current Game State
     * @param  frameTime Last frame time that is used as an inverse of the FPS to
     * obtain FPS independent game behavior
     */
    virtual void Render (float frameTime );

	/** 
	 * Handles an event and passes it along to its children if needed
     * @param  pEvent Pointer to an EventType abstract base class describing the event
	 * @return bool Return false to stop propagating this event
     */
    virtual bool OnEvent (EventType* pEvent );

};

#endif // GAMESTATE_PLAY_H
