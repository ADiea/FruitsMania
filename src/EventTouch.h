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
#ifndef EVENTTOUCHEND_H
#define EVENTTOUCHEND_H
#include "EventType.h"

enum TouchType
{
	TOUCH_START,
	TOUCH_END,
	TOUCH_MOVE,
};

/**
  * class EventTouch
  * Event fired by a touch
  */
class EventTouch : public EventType
{
public:
    /**
     * Constructs a touch event instance
     */
    EventTouch (int _x, int _y, TouchType _type);

    /**
     * Get the value of x
     * @return the value of x
     */
    int getX ( );

    /**
     * Get the value of y
     * @return the value of y
     */
    int getY ( );

	/**
     * Get the type of the touch 
     * @return the value of touchType
     */
    TouchType getTouchType ( );

    /**
     * Returns this event's type
     * @return EventType
     */
	virtual EventTypeEnum getType ( );
private:

    int x;
    int y;
	TouchType touchType;
};

#endif // EVENTTOUCHEND_H
