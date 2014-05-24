/*
 * Matrix.h
 *
 *  Created on: Sep 22, 2012
 *      Author: hrushi
 */

#ifndef MATRIX_H_
#define MATRIX_H_

#include "Includes.h"

class Matrix {
private:


public:
	Matrix();
	virtual ~Matrix();

	double Determinant3x3 ( double* vD,  double  (&Mat)[3][3]  );
	double Determinant3x3 ( double  (&Mat)[3][3]  );

	int Print( double(&Mat)[3][3] );
	int Print( double(&Mat)[3][3], string str );
	int Print( double(&Mat)[4][4], string str );
	int Print( double* Mat, string str);

	int MatrixMult( double (&ans)[4][4], double (&lhs)[4][4], double (&rhs)[4][4] );
	int MatrixMult( double (&ans)[4][4], double (&m1)[4][4], double (&m2)[4][4], double (&m3)[4][4] );
	int MatrixMult( double *ans, const double (&lhs)[3][3], const double* rhs );

	int CopyMatrix( const double(&src)[4][4], double(&dest)[4][4] );

	int MatOnPt( double(&TrMat)[4][4], double *pt );

	int Transpose( double (&Transpose)[4][4] , const double(& rhs)[4][4]);

	int SetMat( double(&Mat)[4][4], const double dVal );
	int SetMat( double *Mat, const double dVal);

	int SetAsEye( double(&Mat)[4][4]);

	int ElementWiseMultiply( double* ans, const double* Mat1, const double* Mat2 );
	int ElementWiseMultiply( double* ans, const unsigned int* Mat1, const double* Mat2 );

	int MultiplyByConst(double* ans,  double * Mat, const double d);
	int MultiplyByConst( double(&ans)[3][3], const double(&Mat)[3][3], const double d);

	int BuildMat( double(&Mat)[3][3], const double* x0, const double* x1, const double * x2);



};

// Non Member functions for Operator Overloading
std::ostream& operator<<( std::ostream& out, const double (&Mat)[4][4]); // prints a matrix 4 x 4
std::ostream& operator<<( std::ostream& out, const double *Mat); // prints a matrix 4 x 1

#endif /* MATRIX_H_ */
