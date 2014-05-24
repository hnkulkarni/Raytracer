/*
 * Clipping.h
 *
 *  Created on: Oct 17, 2012
 *      Author: hrushi
 *
 *      Reference: Algorithm taken from
 *      http://en.wikipedia.org/wiki/Cohen%E2%80%93Sutherland_algorithm
 *
 *      These are the Clipping Codes [TOP : BOTTOM : RIGHT : LEFT]
 *
 *       1001 | 1000 | 1010
 *      ------+------+-------
 *            |      |
 *       0001 | 0000 | 0010
 *            |      |
 *      ------+------+-------
 *       0101 | 0100 | 0110
 *
 */

#ifndef CLIPPING_H_
#define CLIPPING_H_
#include "Matrix.h"
#include "Vertex.h"
#include "DoMath.h"


//Clipping Codes : Deliberately put outside the class.
// Class definitions, do not allow initialization
const int TOP = 0b1000;
const int BOTTOM = 0b0100;
const int RIGHT = 0b0010;
const int LEFT = 0b0001;
const int INSIDE = 0b0000;

class Clipping: public Matrix {

private:
	double ClipLimits[4];
	int GetCode(const Vertex Pt);

	DoMath oMath;

	double xmin, ymin, xmax, ymax;

public:
	Clipping();
	virtual ~Clipping();

	// Set the Clipping Limits
	int SetLimits(const double xMinLim, const double yMinLim, const double xMaxLim, const double yMaxLim );
	int SetLimits(const double* Lim);


	// Clip the Image
	int ClipLine(Vertex& V1, Vertex& V2 );

};

#endif /* CLIPPING_H_ */
