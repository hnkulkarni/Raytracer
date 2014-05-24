/*
 * DoMath.h
 *
 *  Created on: Oct 20, 2012
 *      Author: hrushi
 *
 *
 *      Does all the math
 */

#ifndef DOMATH_H_
#define DOMATH_H_

#include "Includes.h"
#include "Vertex.h"

class DoMath {
public:
	DoMath();
	virtual ~DoMath();


	double CalcSlope(const Vertex& V1, const Vertex& V2 );
};

#endif /* DOMATH_H_ */
