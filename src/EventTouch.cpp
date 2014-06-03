/*
 * This source/header file is part of a test interview and is created & copyrighted (c) Andrei Diea <diea_andrei@yahoo.com> 2014
 * and is not to be distributed or used for commercial purposes without author consent.
 */
#include "EventTouch.h"

/**
* Constructs a touch event instance
*/
EventTouch::EventTouch (int _x, int _y, TouchType _type)
	: x(_x), y(_y), touchType(_type){}

/**
 * Get the value of x
 * @return the value of x
 */
int EventTouch::getX ( ) {
    return x;
}

/**
 * Get the value of y
 * @return the value of y
 */
int EventTouch::getY ( ) {
    return y;
}

/**
* Get the type of the touch 
* @return the value of touchType
*/
TouchType EventTouch::getTouchType ( )
{
	return touchType;
}

/**
* Returns this event's type
* @return EventType
*/
EventTypeEnum EventTouch::getType ( )
{
	return EVENT_TOUCH;
}