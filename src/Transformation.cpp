/*
 * Transformation.cpp
 *
 *  Created on: Sep 22, 2012
 *      Author: hrushi
 */

#include "Transformation.h"

Transformation::Transformation() {
	// DONE Auto-generated constructor stub

}

Transformation::~Transformation() {
	// DONE Auto-generated destructor stub
}

/**********************************************************************
 * Function_Name: RotAxis
 * Return 		:
 * Comments 	:
 **********************************************************************/
int Transformation::RotAxis( double(&Rw)[4][4],  VectorSpace w )
{

	w.DoNormalization();

	VectorSpace m;

	for( int i = 0; i < 3; i++ )
	{
		m.vs[i] = (double)(rand() % 1000)/1000;
	}

	m.DoNormalization();


	VectorSpace u;

	u = w;
	u.CrossProduct(m);
	u.DoNormalization();

	VectorSpace v;
	v = w;
	v.CrossProduct(u);


	// Filling Up Rw
	FillUpRw( Rw, u.vs, v.vs, w.vs);

	CheckRotationMat(Rw);

	return EXIT_SUCCESS;
}

/**********************************************************************
 * Function_Name: FillUpRw
 * Return 		:
 * Comments 	: Takes the u, v, w vectors and fills up the Rw
 **********************************************************************/
int Transformation::FillUpRw(double(&Rw)[4][4], const double* u, const double* v, const double* w )
{

	for( int i = 0; i < 3; i++)
	{
		for( int j = 0; j < 3; j++)
		{
			if( i == 0)
			{
				Rw[i][j] = u[j];
			}
			else if( i == 1)
			{
				Rw[i][j] = v[j];
			}
			else if( i == 2)
			{
				Rw[i][j] = w[j];
			}
		}
	}

	Rw[3][3] = 1;

	return EXIT_SUCCESS;
}


/**********************************************************************
 * Function_Name: Cehck Rotation matrix
 * Return 		:
 * Comments 	: Rw * RwT = I
 **********************************************************************/
int Transformation::CheckRotationMat( double (&R)[4][4] )
{
	double RT[4][4] = {{0}};
	double R_RT[4][4] = {{0}};

	Transpose(RT, R );

	MatrixMult(R_RT, RT, R );

	try
	{

		for(int i = 0; i < 4; i++ )
		{
			for( int j = 0; j < 4; j++ )
			{
				if(i == j )
				{
					if(  ( R_RT[i][j] - 1 ) > SOME_SMALL_VALUE )
					{
						cerr << "Given Matrix is not Rotation" << endl;
						cerr << "R * RT != I " << endl;
						throw ERR_MAT_NOT_ROTATION;
						break;
					}
				}
				else
				{
					if( R_RT[i][j] > SOME_SMALL_VALUE )
					{
						cerr << "Given Matrix is not Rotation" << endl;
						cerr << "R * RT != I " << endl;
						throw ERR_MAT_NOT_ROTATION;
						break;
					}
				}

			}
		}


	}
	catch(int n)
	{
		if( n == ERR_MAT_NOT_ROTATION )
		{
			cout << "Rotation ERROR " << endl;
			throw ERR_MAT_NOT_ROTATION;
		}
	}


	return EXIT_SUCCESS;


}



/**********************************************************************
 * Function_Name: RotMatZ
 * Return 		:
 * Comments 	: Creates a standard Rotation along Z, with angle theta
 **********************************************************************/
int Transformation::RotMatZ(double (&Ro)[4][4], double theta )
{

	double C = cos(theta);
	double S = sin(theta);

	Ro[0][0] = C; 	Ro[0][1] = -1 * S; 	Ro[0][2] = 0; Ro[0][3] = 0;
	Ro[1][0] = S; 	Ro[1][1] = C; 		Ro[1][2] = 0; Ro[1][3] = 0;
	Ro[2][0] = 0; 	Ro[2][1] = 0;		Ro[2][2] = 1; Ro[2][3] = 0;
	Ro[3][0] = 0; 	Ro[3][1] = 0;		Ro[3][2] = 0; Ro[3][3] = 1;


	return EXIT_SUCCESS;
}
