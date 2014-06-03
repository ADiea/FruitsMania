/*
 * This source/header file is part of a test interview and is created & copyrighted (c) Andrei Diea <diea_andrei@yahoo.com> 2014
 * and is not to be distributed or used for commercial purposes without author consent.
 */
#ifndef RECTANGULARCOLLIDER_H
#define RECTANGULARCOLLIDER_H
#include "Collider.h"

/**
  * class RectangularCollider
  * A simple rectangular collider class. Uses a gameObject to get the object's position
  */
class RectangularCollider : public Collider
{
public:
    /**
     * Instance constructor
     * @param _pGameObject 
	 * @param _x offset X from the object's position
     * @param _y offset Y from the object's position
	 * @param _width Width of the rect collider
     * @param _height Height of the rect collider
     */
    RectangularCollider (GameObject* _pGameObject, int _x, int _y, int _width, int _height);
    virtual ~RectangularCollider ( );

    /**
     * Tests if a point defined by x,y screen coordinates collides with this object
     * @return bool
     * @param  x X screen coordinate of test point
     * @param  y Y screen coordinate of test point
     */
    bool isColliding (int x, int y );

private:
    // Anchor point x of the imaginary colliding rectangle. 
	// Offset from the object's position
    float x;
    // Anchor point y of the imaginary colliding rectangle
	// Offset from the object's position
    float y;
    // Width of the imaginary colliding rectangle
    float width;
    // Height of the imaginary colliding rectangle
    float height;
};

#endif // RECTANGULARCOLLIDER_H
