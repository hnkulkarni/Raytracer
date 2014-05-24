/*
 * Vertex.cpp
 *
 *  Created on: Sep 22, 2012
 *      Author: hrushi
 */

#include "Vertex.h"

/**********************************************************************
 * Function_Name: Default Constructor
 * Return 		:
 * Comments 	:
 **********************************************************************/
Vertex::Vertex()
{
	// DONE Auto-generated constructor stub

	//Load Default Values
	arr[0] = 0;
	arr[1] = 0;
	arr[2] = 0;
	arr[3] = 1; // Default Scale Value is 1

}

/**********************************************************************
 * Function_Name: Default Destructor
 * Return 		:
 * Comments 	:
 **********************************************************************/
Vertex::~Vertex() {
	// DONE Auto-generated destructor stub
}



/**********************************************************************
 * Function_Name: Copy Constructor
 * Return 		:
 * Comments 	:
 **********************************************************************/
Vertex::Vertex(const Vertex& rhsVertex)
{
	AllocateVertex(rhsVertex);
	CopyVertex(rhsVertex);
}


/**********************************************************************
 * Function_Name: Assignment Operator =
 * Return 		:
 * Comments 	:
 **********************************************************************/
Vertex& Vertex::operator =(const Vertex &rhsVertex)
{
	AllocateVertex(rhsVertex);
	CopyVertex(rhsVertex);
	return *this;
}



/**********************************************************************
 * Function_Name: Allocate vertex
 * Return 		:
 * Comments 	:
 **********************************************************************/
int Vertex::AllocateVertex(const Vertex& rhsVertex)
{
	FaceIdx.resize(  rhsVertex.FaceIdx.size() );

	return EXIT_SUCCESS;
}


/**********************************************************************
 * Function_Name: Copy Vector
 * Return 		:
 * Comments 	:
 **********************************************************************/
int Vertex::CopyVertex(const Vertex& rhsVertex)
{

	for(int i = 0; i < 4; i++)
	{
		arr[i] = rhsVertex.arr[i];
	}

	for( unsigned int i = 0; i < rhsVertex.FaceIdx.size(); i++ )
	{
		FaceIdx.at(i) = rhsVertex.FaceIdx.at(i);
	}

	return EXIT_SUCCESS;
}
/**********************************************************************
 * Function_Name: Set the Vertex Values
 * Return 		: Success or failure
 * Comments 	: Sets the vertex value from the given arguments
 **********************************************************************/
int Vertex::Set(double x, double y, double z, double scale )
{

	// Set the values
	arr[0] = x;
	arr[1] = y;
	arr[2] = z;
	arr[3] = scale;

	return EXIT_SUCCESS;

}


/**********************************************************************
 * Function_Name: Print
 * Return 		:
 * Comments 	:
 **********************************************************************/
int Vertex::Print(string str)
{

	cout << str << endl;

	for( int i = 0; i < 4; i++ )
	{
		cout << arr[i] << " ";
	}

	cout << endl;

	return EXIT_SUCCESS;
}



/**********************************************************************
 * Function_Name: DivideByScale
 * Return 		:
 * Comments 	:
 **********************************************************************/
int Vertex::DivideByScale()
{
	VectorSpace Vs(arr); // Temp Vector Space used only for division with scale
						// Bad design style

	Vs.DivideByScale(arr);

	return EXIT_SUCCESS;
}


/**********************************************************************
 * Function_Name: Overloading <<
 * Return 		:
 * Comments 	:
 **********************************************************************/
std::ostream& operator<<(std::ostream& out, const Vertex& Vrtx)
{
	for( int i = 0; i < 4; i++ )
	{
		out << Vrtx.arr[i] << " ";
	}

	out << endl;

	return out;
}


/**********************************************************************
 * Function_Name: Overloading >>
 * Return 		:
 * Comments 	:
 **********************************************************************/
std::istream& operator>>(std::istream& in, Vertex& Pt)
{

	in >> Pt.arr[0];
	in >> Pt.arr[1];
	in >> Pt.arr[2];
	Pt.arr[3] = 1;

	return in;
}

/**********************************************************************
 * Function_Name: Overloading +
 * Return 		:
 * Comments 	:
 **********************************************************************/
Vertex operator+( const Vertex& pt, const VectorSpace& v )
{
	Vertex ResultantPt = L_plus_tU(pt, v);

	return ResultantPt;
}


/**********************************************************************
 * Function_Name: Overloading +
 * Return 		:
 * Comments 	:
 **********************************************************************/
Vertex operator+( const VectorSpace& v, const Vertex& pt )
{
	Vertex ResultantPt = L_plus_tU(pt, v);

	return ResultantPt;
}


/**********************************************************************
 * Function_Name: L_plus_tU
 * Return 		:
 * Comments 	: This is used by the overloaded operator
 **********************************************************************/
Vertex L_plus_tU(const Vertex& pt, const VectorSpace &v)
{
	Vertex NewPt;

	for(unsigned int i = 0; i < 3; i++ )
	{
		NewPt.arr[i] = pt.arr[i] + v.vs[i];
	}

	return NewPt;

}


/**********************************************************************
 * Function_Name: Overloading =
 * Return 		:
 * Comments 	:
 **********************************************************************/
Vertex::Vertex( const VectorSpace& V1 )
{

	VectorSpace VsTemp = V1;
	VsTemp.DivideByScale();

	for(unsigned int i = 0; i < 4; i++ )
	{
		arr[i] = VsTemp.vs[i];
	}
}


/**********************************************************************
 * Function_Name: Distance
 * Return 		:
 * Comments 	:
 **********************************************************************/
double Vertex::Distance(const Vertex& pt) const
{
	double dist = 0;

	for( unsigned int i = 0; i < 3; i++)
	{
		dist += pow( ( arr[i] - pt.arr[i] ), 2 );
	}

	dist = sqrt( dist );

	return dist;
}


/**********************************************************************
 * Function_Name: Overloading -
 * Return 		:
 * Comments 	:
 **********************************************************************/
Vertex Vertex::operator -(const Vertex& pt) const
{
	Vertex Result;

	for( unsigned int i = 0; i < 3; i++)
	{
		Result.arr[i] = arr[i] - pt.arr[i];
	}

	return Result;

}


/**********************************************************************
 * Function_Name: Multiply
 * Return 		:
 * Comments 	:
 **********************************************************************/
Vertex Vertex::Multiply(const double d) const
{
	Vertex Result;

	for( unsigned int i = 0; i < 3; i++ )
	{
		Result.arr[i] = arr[i] * d;
	}

	return Result;
}

/**********************************************************************
 * Function_Name: Overloading *
 * Return 		:
 * Comments 	:
 **********************************************************************/
Vertex operator*( const double d, const Vertex& pt )
{
	return pt.Multiply( d );
}

/**********************************************************************
 * Function_Name: Overloading *
 * Return 		:
 * Comments 	:
 **********************************************************************/
Vertex operator*(  const Vertex& pt, const double d )
{
	return pt.Multiply(d);
}
