/*
 * This source/header file is part of a test interview and is created & copyrighted (c) Andrei Diea <diea_andrei@yahoo.com> 2014
 * and is not to be distributed or used for commercial purposes without author consent.
 */
#ifndef GAMETIMER_H
#define GAMETIMER_H
#include "EventTimeout.h"

/**
  * class GameTimer
  * Implements a simple timer that fires an event on TimeOut
  * Start/Stop functions could be added but are not needed at this point
  */
class GameTimer
{
public:
    /**
	 * Constructs a GameTimer instance
     * @param  _timerId The ID of this timer instance
     * @param  timeoutValue Timeout value of this timer instance
     */
     GameTimer (TimerIds _timerId, float timeoutValue );

    /**
     * @param  frameTime Time interval of the last frame that will be subtracted from
     * currentTime
     */
    void Update (float frameTime );

    /**
     * @return the current time
     */
	float GetCurrentTime ();

	/**
	* Pauses and unpauses the timer
	*/
	void Pause(bool bPause);

private:
	//Time left until timeout
	float currentTime;
	//This timer's ID used when firing the timeout event
    TimerIds timerId;
	//Flag that stores the paused state of the timer
	bool m_Pause;
};

#endif // GAMETIMER_H
