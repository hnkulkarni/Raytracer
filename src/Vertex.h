/*
 * Vertex.h
 *
 *  Created on: Sep 22, 2012
 *      Author: hrushi
 */

#ifndef VERTEX_H_
#define VERTEX_H_

#include "VectorSpace.h"

#include "Includes.h"

class Vertex
{

private:


public:

	//Public Functions
	Vertex(); // Default Constructor
	Vertex(const Vertex& rhsVertex); // Copy Constructor
	Vertex( const VectorSpace& V1 );

	Vertex& operator=(const Vertex& rhsVertex);

	int Set(double x, double y, double z, double scale);
	int Print(string str);

	virtual ~Vertex();

	int AllocateVertex( const Vertex& rhsVertex );
	int CopyVertex(const Vertex& rhsVertex);
	int DivideByScale();

	double Distance( const Vertex& pt) const;

	Vertex operator-( const Vertex& pt ) const;


	Vertex Multiply( const double d ) const;

	// Public Variables
	double arr[4];

	vector<int> FaceIdx;
};
std::istream& operator>>(std::istream& in, Vertex& Pt);
std::ostream& operator<<(std::ostream& out, const Vertex& Vrtx);
Vertex operator+( const Vertex& pt, const VectorSpace& v ); // Overloading for L+tU form
Vertex operator+( const VectorSpace& v, const Vertex& pt ); // Swapped argument, i.e. tU+L
Vertex L_plus_tU(const Vertex& pt, const VectorSpace &v);
Vertex operator*( const double d, const Vertex& pt );
Vertex operator*( const Vertex& pt, const double d );



#endif /* VERTEX_H_ */
