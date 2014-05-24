/*
 * Transformation.h
 *
 *  Created on: Sep 22, 2012
 *      Author: hrushi
 */

#ifndef TRANSFORMATION_H_
#define TRANSFORMATION_H_

#include "Matrix.h"
#include "VectorSpace.h"

class Transformation: public Matrix {

private:

	int FillUpRw(double(&Rw)[4][4], const double* u, const double* v, const double* w );


public:
	Transformation();
	virtual ~Transformation();


	int RotAxis( double(&R)[4][4],  VectorSpace w );
	int CheckRotationMat( double (&R)[4][4] );
	int RotMatZ(double (&Ro)[4][4], double theta );
};

#endif /* TRANSFORMATION_H_ */
