/*
 * This source/header file is part of a test interview and is created & copyrighted (c) Andrei Diea <diea_andrei@yahoo.com> 2014
 * and is not to be distributed or used for commercial purposes without author consent.
 */

#ifndef MAT3_H
#define MAT3_H

#include <string>

/**
  * class Mat3
  * Implementation of a 3x3 matrix together with addition and multiplying operations
  */

class Mat3
{
public:
    /**
     * Empty Constructor
     */
    Mat3 ( );

    // A 3x3 float array holding the matrix data
    float mat[3][3];

    /**
	 * Binary addition operator. Returns a fully constructed object
     */
    Mat3 operator+(const Mat3& rhs);

    /**
	 * Binary addition operator. Returns a fully constructed object
     */
    Mat3 operator*(const Mat3& rhs);

};

#endif // MAT3_H
