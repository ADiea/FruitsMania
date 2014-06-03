/*
 * This source/header file is part of a test interview and is created & copyrighted (c) Andrei Diea <diea_andrei@yahoo.com> 2014
 * and is not to be distributed or used for commercial purposes without author consent.
 */
#include "Vector2.h"

/**
* Constructor
*/
Vector2::Vector2 ( float _x, float _y):x(_x), y(_y){}

/**
* Binary addition operator
*/
Vector2 Vector2::operator+(const Vector2& rhs)
{
	Vector2 result(x,y);
	result.x += rhs.x;
	result.y += rhs.y;
	return result;
}

/**
* Binary subtraction operator
*/
Vector2 Vector2::operator-(const Vector2& rhs)
{
	Vector2 result(x,y);
	result.x -= rhs.x;
	result.y -= rhs.y;
	return result;
}

/**
* Constant multiplication operator
*/
Vector2 Vector2::operator*(const float k)
{
	Vector2 result(x,y);
	result.x *= k;
	result.y *= k;
	return result;
}

/**
* Return squared length of the vector
*/
float Vector2::sqLength()
{
	return (x*x + y*y);
}

/**
* Return length of the vector
*/
float Vector2::Length()
{
	return sqrt(sqLength());
}

/**
* Return the normalized vector
*/
Vector2 Vector2::Normal()
{
	return (*this)*(1/Length());
}

/**
 * Set the value of x
 * @param _x the new value of x
 */
void Vector2::setX( float _x) {
    x = _x;
}

/**
 * Get the value of x
 * @return the value of x
 */
float Vector2::getX ( ) {
    return x;
}

/**
 * Set the value of y
 * @param _y the new value of y
 */
void Vector2::setY ( float _y ) {
    y = _y;
}

/**
 * Get the value of y
 * @return the value of y
 */
float Vector2::getY ( ) {
    return y;
}