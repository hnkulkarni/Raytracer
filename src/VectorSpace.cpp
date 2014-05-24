/*
 * VectorSpace.cpp
 *
 *  Created on: Sep 26, 2012
 *      Author: hrushi
 */

#include "VectorSpace.h"

/**********************************************************************
 * Function_Name: Default Constructor
 * Return 		:
 * Comments 	:
 **********************************************************************/
VectorSpace::VectorSpace()
{

	vs[0] = 0;
	vs[1] = 0;
	vs[2] = 0;
	vs[3] = 1;

	RayNVal = 1; // Default value of the Ray Refractive index;


}

/**********************************************************************
 * Function_Name: Default Constructor
 * Return 		:
 * Comments 	: Creates a vector between two points A and B
 **********************************************************************/
VectorSpace::VectorSpace(const double *ptA, const double *ptB )
{
	// DONE Auto-generated constructor stub

	VectorSpace vsA(ptA);
	VectorSpace vsB(ptB);

	CreateVector(vsA.vs, vsB.vs );

	vs[3] = 1;
}


/**********************************************************************
 * Function_Name: Default Constructor
 * Return 		:
 * Comments 	: Copies the vector into this space
 **********************************************************************/
VectorSpace::VectorSpace(const double *ptA)
{

	for( int i = 0; i < 4; i++)
	{
		vs[i] = ptA[i];
	}
}


VectorSpace::~VectorSpace() {
	// DONE Auto-generated destructor stub
}


/**********************************************************************
 * Function_Name: Copy Constructor
 * Return 		:
 * Comments 	:
 **********************************************************************/
VectorSpace::VectorSpace(const VectorSpace& rhsVectorSpace )
{
	CopyVector(rhsVectorSpace);
}



/**********************************************************************
 * Function_Name: Assignment Operator
 * Return 		:
 * Comments 	:
 **********************************************************************/
VectorSpace& VectorSpace::operator=( const VectorSpace& rhsVectorSpace )
{

	CopyVector(rhsVectorSpace);

	return *this;

}


/**********************************************************************
 * Function_Name: Copy
 * Return 		:
 * Comments 	: Copies the data
 **********************************************************************/

int VectorSpace::CopyVector(const VectorSpace& rhsvs)
{
	for( int i = 0; i < 4; i++ )
	{
		vs[i] = rhsvs.vs[i];
	}

	RayNVal = rhsvs.RayNVal;

	return EXIT_SUCCESS;
}

/**********************************************************************
 * Function_Name: CreateVector
 * Return 		:
 * Comments 	: Creates a Vector by subtracting B - A
 **********************************************************************/
int VectorSpace::CreateVector(const double *ptA, const double *ptB )
{

	double ptA_norm[4];
	DivideByScale( ptA_norm, ptA );

	double ptB_norm[4];
	DivideByScale( ptB_norm, ptB );

	for( int iCorr = 0; iCorr < 3; iCorr++ )
	{
		vs[iCorr] = ptB[iCorr] - ptA[iCorr];
	}

	return EXIT_SUCCESS;

}

/**********************************************************************
 * Function_Name: Print
 * Return 		:
 * Comments 	:
 **********************************************************************/
int VectorSpace::Print()
{
	Print("");
	return EXIT_SUCCESS;
}

/**********************************************************************
 * Function_Name: Print
 * Return 		:
 * Comments 	: Prints to the screen
 **********************************************************************/
int VectorSpace::Print(string Comment )
{

	cout << Comment;

	for( int i = 0; i < 4; i++ )
	{
		cout << " " << vs[i];
	}

	cout << endl;
	return EXIT_SUCCESS;
}

/**********************************************************************
 * Function_Name: Overloading <<
 * Return 		:
 * Comments 	:
 **********************************************************************/
std::ostream& operator<<( std::ostream& out, const VectorSpace& outVectorSpace)
{

	for(int i = 0; i < 4; i++ )
	{
		out << outVectorSpace.vs[i];
		cout << " ";
	}

	return out;
}

/**********************************************************************
 * Function_Name: Overloading -
 * Return 		:
 * Comments 	:
 **********************************************************************/
VectorSpace VectorSpace::operator -(const VectorSpace & rhsVs ) const
{
	VectorSpace Result;

	for( unsigned int i = 0; i < 3; i++ )
	{
		Result.vs[i] = vs[i] - rhsVs.vs[i];
	}

	return Result;
}


/**********************************************************************
 * Function_Name: Overloading >>
 * Return 		:
 * Comments 	:
 **********************************************************************/
std::istream& operator>> ( std::istream& in, VectorSpace& inVectorSpace )
{
	in.exceptions(std::istream::failbit | std::istream::badbit);

	for(int i = 0; i < 3; i++)
	{
		try
		{
		in >> inVectorSpace.vs[i];
		}
		catch( std::istream::failure &e )
		{

			cerr << "Cannot Read Vector " << endl;
			cerr << "Fewer than 3 elements given " << endl;
			cerr << e.what() << endl;

			throw ERR_ERROR_READING_VECTOR;
		}
	}

	inVectorSpace.vs[3] = 1;

	return in;
}


/**********************************************************************
 * Function_Name: Operator *
 * Return 		:
 * Comments 	:
 **********************************************************************/
VectorSpace operator *(const double Scale,  const VectorSpace &rhsVs)
{
	VectorSpace ResultVs = MultiplyByScale(rhsVs, Scale);
	return ResultVs;

}

/**********************************************************************
 * Function_Name: Operator *
 * Return 		:
 * Comments 	: Multiply by Constant
 **********************************************************************/
VectorSpace operator *( const VectorSpace& rhsVs, const double Scale)
{
	VectorSpace ResultVs = MultiplyByScale(rhsVs, Scale);
	return ResultVs;

}


/**********************************************************************
 * Function_Name: MultiplyByScale
 * Return 		:
 * Comments 	: Multiply by Constant
 **********************************************************************/
VectorSpace MultiplyByScale(const VectorSpace& V1, const double & scale)
{
	VectorSpace Temp;

	for( unsigned int i = 0; i < 3; i++ )
	{
		Temp.vs[i] = V1.vs[i] * scale;
	}

	return Temp;
}


/**********************************************************************
 * Function_Name: Scale
 * Return 		:
 * Comments 	:
 **********************************************************************/
VectorSpace& VectorSpace::ScaleVS( const double Scale,  VectorSpace& rhsVs)
{

	for(int i = 0; i < 3; i++)
	{
		rhsVs.vs[i] *= Scale;
	}

	return rhsVs;
}


/**********************************************************************
 * Function_Name: Operator *
 * Return 		:
 * Comments 	: Cross Product
 **********************************************************************/
VectorSpace operator*(VectorSpace& V1, VectorSpace& V2)
{

	VectorSpace TempVS = V1;

	TempVS.CrossProduct( V2 );

	return TempVS;

}

/**********************************************************************
 * Function_Name: DoNormalization
 * Return 		:
 * Comments 	: Normalizes the Vector
 **********************************************************************/
int VectorSpace::DoNormalization()
{
	Normalize( vs );
	return EXIT_SUCCESS;
}

/**********************************************************************
 * Function_Name: Normalize
 * Return 		: int
 * Comments 	: Normalizes the Given Co-ordinates by dividing with the
 * 				: scale value
 **********************************************************************/
int VectorSpace::DivideByScale( double* aNorm, const double *a)
{
	if(a[SCALE] > DBL_MIN ) // Non Zero Scale
	{
		for( int i = 0; i < 4; i++ )
		{
			aNorm[i] = a[i] / a[SCALE];
		}
	}
	return EXIT_SUCCESS;
}



/**********************************************************************
 * Function_Name: Normalize
 * Return 		: int
 * Comments 	: Normalizes the Given Co-ordinates by dividing with the
 * 				: scale value, and this operation is performed inplace
 **********************************************************************/
int VectorSpace::DivideByScale( double * a)
{
	for( int i = 0; i < 4; i++ )
	{
		a[i] = a[i] / a[SCALE];
	}

	return EXIT_SUCCESS;
}

/**********************************************************************
 * Function_Name: DivideByScale
 * Return 		:
 * Comments 	:
 **********************************************************************/
int VectorSpace::DivideByScale()
{
	DivideByScale( vs );

	return EXIT_SUCCESS;
}

/**********************************************************************
 * Function_Name: Normalize the Vector
 * Return 		:
 * Comments 	: Normalizes the Vector by dividing with the magnitude
 **********************************************************************/
int VectorSpace::Normalize( double *a )
{

	double mag = Magnitude(a);


	if( mag > DBL_MIN ) // Avoiding the 0/0 division
	{
		for( int i = 0; i < 3; i++ )
		{
			a[i] = a[i]/mag;
		}
	}


	return EXIT_SUCCESS;
}


/**********************************************************************
 * Function_Name: Magnitude
 * Return 		:
 * Comments 	: Returns the Magnitude of the Function
 **********************************************************************/
double VectorSpace::Magnitude(const double *a )
{

	double mag = 0;

	for( int i = 0; i < 3; i++ )
	{
		mag += a[i] * a[i];
	}

	mag = sqrt( mag );

	return mag;
}


/**********************************************************************
 * Function_Name: Magnitude
 * Return 		:
 * Comments 	: Returns the magnitude of the self vector
 **********************************************************************/
double VectorSpace::Magnitude()
{
	return Magnitude( vs );
}
/**********************************************************************
 * Function_Name: CrossProduct
 * Return 		:
 * Comments 	: Returns the Magnitude of the Function
 **********************************************************************/
int VectorSpace::CrossProduct( VectorSpace v2)
{
	double Mat3x3[3][3];

	// Initialize the Matrix
	Mat3x3[0][0] = 1;  			Mat3x3[0][1] = 1; 			Mat3x3[0][2] = 1;
	Mat3x3[1][0] = vs[0];  		Mat3x3[1][1] = vs[1]; 		Mat3x3[1][2] = vs[2];
	Mat3x3[2][0] = v2.vs[0];  	Mat3x3[2][1] = v2.vs[1]; 	Mat3x3[2][2] = v2.vs[2];

	Matrix Mat;
	Mat.Determinant3x3(vs, Mat3x3);

	return EXIT_SUCCESS;

}

/**********************************************************************
 * Function_Name: Dot Product
 * Return 		:
 * Comments 	: Calculates the Dot Product of two Vectors,
 * 				: v1 is the self vector
 * 				: v2 is the vector with which this has to be dotted
 **********************************************************************/
double VectorSpace::Dot( const VectorSpace v2 ) const
{
	double DotProd = 0;

	for(int i = 0; i < 3; i++ )
	{
		DotProd += vs[i] * v2.vs[i];
	}

	return DotProd;
}


/**********************************************************************
 * Function_Name: Operator +
 * Return 		:
 * Comments 	:
 **********************************************************************/
VectorSpace  operator+( const VectorSpace& V1, const VectorSpace& V2)
{
	VectorSpace Result;

	for( unsigned int i = 0; i < 3; i++ )
	{
		Result.vs[i] = V1.vs[i] + V2.vs[i];
	}

	return Result;
}

