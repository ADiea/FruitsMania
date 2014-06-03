/*
 * This source/header file is part of a test interview and is created & copyrighted (c) Andrei Diea <diea_andrei@yahoo.com> 2014
 * and is not to be distributed or used for commercial purposes without author consent.
 */
#include "EventTimeout.h"

/**
* Constructs a timeout event instance
*/
EventTimeout::EventTimeout (TimerIds _expiredTimer ):expiredTimer(_expiredTimer){}

/**
 * Get the value of expiredTimer
 * Timer ID that expired
 * @return the value of expiredTimer
 */
TimerIds EventTimeout::getExpiredTimer ( ) {
    return expiredTimer;
}

/**
* Returns this event's type
* @return EventType
*/
EventTypeEnum EventTimeout::getType ( )
{
	return EVENT_TIMEOUT;
}
