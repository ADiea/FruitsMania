/*
 * This source/header file is part of a test interview and is created & copyrighted (c) Andrei Diea <diea_andrei@yahoo.com> 2014
 * and is not to be distributed or used for commercial purposes without author consent.
 */
#ifndef EVENTTYPE_H
#define EVENTTYPE_H

enum EventTypeEnum
{
	EVENT_TIMEOUT,
	EVENT_TOUCH
};

/**
  * class EventType
  * Generic event abstract base class. Cannot be instantiated by its own
  */

class EventType
{
public:

    /**
     * Returns this event's type so that the caller can dynamic_cast to an appropiate
     * event class
     * @return EventType
     */
	virtual EventTypeEnum getType ( ) = 0;
};

#endif // EVENTTYPE_H
