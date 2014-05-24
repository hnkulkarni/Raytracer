/*
 * VectorSpace.h
 *
 *  Created on: Sep 26, 2012
 *      Author: hrushi
 *
 *      This contains all the vector operations in the code. Since the name 'vector'
 *      is already taken by the standard namespace, VectorSpace is used over here.
 */

#ifndef VECTORSPACE_H_
#define VECTORSPACE_H_

#include "Includes.h"
#include "Matrix.h"

class VectorSpace
{

private:
	int Normalize( double *a );
	double Magnitude( const double *a );
	int DivideByScale( double * aNorm, const double *a);


public:
	/*************** Class Housekeeping ***************/
	VectorSpace();
	VectorSpace(const double *ptA);
	VectorSpace(const double *ptA, const double *ptB );
	virtual ~VectorSpace();

	VectorSpace(const VectorSpace& rhsVectorSpace ); // Copy Constructor
	VectorSpace& operator=( const VectorSpace& rhsVectorSpace ); // Assignment Operator

	int CopyVector(const VectorSpace& rhsvs );

	/************** Public Functions ******************/

	int CreateVector(const double *ptA, const double *ptB );
	VectorSpace& ScaleVS( const double Scale, VectorSpace& rhsVs);

	VectorSpace operator-( const VectorSpace& rhsVs ) const;

	int DoNormalization();

	int DivideByScale( double * a);
	int DivideByScale();



	double Magnitude();

	int CrossProduct( VectorSpace v2 );
	double Dot( const VectorSpace v2 ) const;

	int Print( );
	int Print( string Comment );

	double vs[4];

	double RayNVal;
};


// Non Member function for overloading operators for Vector Spaces
std::ostream& operator<<( std::ostream& out, const VectorSpace& outVectorSpace);
std::istream& operator>>( std::istream& in , VectorSpace& inVectorSpace);

VectorSpace operator*( const double Scale, const VectorSpace& rhsVs); // Multiply by constant
VectorSpace operator*( const VectorSpace& rhsVs, const double Scale); // Multiply by constant
VectorSpace MultiplyByScale(const VectorSpace& V1, const double & scale);

VectorSpace operator*( VectorSpace& V1, VectorSpace& V2); // Cross Product

VectorSpace operator+( const VectorSpace& V1, const VectorSpace& V2);

#endif /* VECTORSPACE_H_ */
