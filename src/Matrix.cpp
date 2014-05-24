/*
 * Matrix.cpp
 *
 *  Created on: Sep 22, 2012
 *      Author: hrushi
 */

#include "Matrix.h"

/**********************************************************************
 * Function_Name: Default Constructor
 * Return 		:
 * Comments 	:
 **********************************************************************/
Matrix::Matrix()
{
	// DONE Auto-generated constructor stub

}

/**********************************************************************
 * Function_Name: Default Destructor
 * Return 		:
 * Comments 	:
 **********************************************************************/
Matrix::~Matrix() {
	// DONE Auto-generated destructor stub
}


/**********************************************************************
 * Function_Name: Determinant
 * Return 		:
 * Comments 	: Calculates the determinant of the 3x3 matrix, returns
 * 				: a vector that can be used in the form of a vector.
 * 				: used in taking Cross Product
 **********************************************************************/
double Matrix::Determinant3x3 ( double* vD,  double  (&Mat)[3][3]  )
{
	vD[0] =  	Mat[0][0] * ( Mat[1][1] * Mat[2][2] - Mat[1][2] * Mat[2][1]	);
	vD[1] = -1 * Mat[0][1] * ( Mat[1][0] * Mat[2][2] - Mat[1][2] * Mat[2][0] );
	vD[2] =      Mat[0][2] * ( Mat[1][0] * Mat[2][1] - Mat[1][1] * Mat[2][0] );

	double final = vD[0] + vD[1] + vD[2];
	return final;
}

/**********************************************************************
 * Function_Name: Determinant
 * Return 		:
 * Comments 	: Calculates the determinant of the 3x3 matrix,
 * 				: returns a double
 **********************************************************************/
double Matrix::Determinant3x3( double (&Mat)[3][3] )
{
	double det[3] = {0};

	return Determinant3x3(det, Mat);

}

/**********************************************************************
 * Function_Name: Print
 * Return 		:
 * Comments 	:
 **********************************************************************/
int Matrix::Print(double (&Mat)[3][3], string str )
{
	cout << str << endl;
	for( int i = 0; i < 3; i++ )
	{
		for( int j = 0; j < 3; j++ )
		{
			cout <<  std::setprecision(10) << setw(20) << Mat[i][j];
		}

		cout << endl;
	}

	return EXIT_SUCCESS;

}


/**********************************************************************
 * Function_Name: Print
 * Return 		:
 * Comments 	:
 **********************************************************************/
int Matrix::Print( double(&Mat)[4][4], string str )
{
	cout << str << endl;

	for( int i = 0; i < 4; i++ )
	{
		for( int j = 0; j < 4; j++ )
		{
			cout << " ";
			cout << std::setprecision(10) << setw(20)  << Mat[i][j];
		}

		cout << endl;
	}

	cout << endl;
	return EXIT_SUCCESS;

}

/**********************************************************************
 * Function_Name: Print
 * Return 		:
 * Comments 	:
 **********************************************************************/
int Matrix::Print(double (&Mat)[3][3] )
{

	Print( Mat, " ");

	return EXIT_SUCCESS;
}



/**********************************************************************
 * Function_Name: Matrix Multiplication
 * Return 		:
 * Comments 	:
 **********************************************************************/
int Matrix::MatrixMult(double(&ans)[4][4], double(&lhs)[4][4], double (&rhs)[4][4] )
{
	SetMat(ans,0); // Had two bugs because of not putting this.

	for( int i = 0; i < 4; i++ )
	{
		for( int j = 0; j < 4; j++ )
		{
			for(int k = 0; k < 4; k++ )
			{
				ans[i][j] += lhs[i][k] * rhs[k][j];

				// Prints every small value
				if(CRITICAL_DEBUG)
				{
					cout << "i: " << i << " j: " << j << " k: " << k << " ans: " << ans[i][j] << " = " <<  lhs[i][k] << " * " << rhs[k][j]<< endl;
				}
			}
		}
	}

	return EXIT_SUCCESS;
}
/**********************************************************************
 * Function_Name: MatrixMult
 * Return 		:
 * Comments 	:
 **********************************************************************/
int Matrix::MatrixMult( double *ans, const double (&lhs)[3][3], const double* rhs )
{

	for( unsigned int i = 0; i < 3; i++)
	{
		ans[i] = 0;
	}

	for(unsigned int i = 0; i < 3; i++ )
	{
		for( unsigned int j = 0; j < 3; j++ )
		{
			ans[i] += lhs[i][j] * rhs[j];
		}
	}


	return EXIT_SUCCESS;
}
/**********************************************************************
 * Function_Name: Multiplies 3 Matrices
 * Return 		:
 * Comments 	:
 **********************************************************************/
int Matrix::MatrixMult( double (&ans)[4][4], double (&m1)[4][4], double (&m2)[4][4], double (&m3)[4][4] )
{
	double MTemp[4][4];

	MatrixMult(MTemp, m1, m2);

	// Prints every small value
	if(CRITICAL_DEBUG)
	{
		cout << "m1" << endl << m1 << endl;
		cout << "m2" << endl << m2 << endl;
		cout << "MTemp" << endl << MTemp << endl;
	}

	MatrixMult( ans, MTemp, m3);

	// Prints every small value
	if(CRITICAL_DEBUG)
	{
		cout << "m3" << endl << m3 << endl;
		cout << "ans" << endl << ans << endl;
	}

	return EXIT_SUCCESS;

}

/**********************************************************************
 * Function_Name: Copy Matrix
 * Return 		:
 * Comments 	:
 **********************************************************************/
int Matrix::CopyMatrix( const double(&src)[4][4], double(&dest)[4][4] )
{

	for(int i = 0; i < 4; i++ )
	{
		for( int j = 0; j < 4; j++ )
		{
			dest[i][j] = src[i][j];
		}
	}

	return EXIT_SUCCESS;
}


/**********************************************************************
 * Function_Name: MatOnPt
 * Return 		:
 * Comments 	:
 **********************************************************************/
int Matrix:: MatOnPt( double(&TrMat)[4][4], double *pt )
{

	double ans[4] = {0};

	for( int i = 0; i < 4; i++ )
	{
		for( int j = 0; j < 4; j++ )
		{
			ans[i] += TrMat[i][j] * pt[j];
		}
	}

	for(int i = 0; i < 4; i ++ )
	{
		pt[i] = ans[i];
	}

	return EXIT_SUCCESS;

}


/**********************************************************************
 * Function_Name: Transpose
 * Return 		:
 * Comments 	:
 **********************************************************************/
int Matrix::Transpose( double (&Transpose)[4][4] , const double(& rhs)[4][4])
{

	for(int i = 0; i < 4; i++ )
	{
		for(int j = 0; j < 4; j++ )
		{
			Transpose[j][i] = rhs[i][j];
		}
	}

	return EXIT_SUCCESS;
}


/**********************************************************************
 * Function_Name: SetMat
 * Return 		:
 * Comments 	:
 **********************************************************************/
int Matrix::SetMat(double(&Mat)[4][4], const double dVal )
{

	for(int i = 0; i < 4; i++ )
	{
		for(int j = 0; j < 4; j++ )
		{
			Mat[j][i] = dVal;
		}
	}

	return EXIT_SUCCESS;
}

/**********************************************************************
 * Function_Name: SetMat
 * Return 		:
 * Comments 	:
 **********************************************************************/
int Matrix::SetMat(double *Mat, double dVal)
{

	for(int i = 0; i < 4; i++)
	{
		Mat[i] = dVal;
	}

	return EXIT_SUCCESS;
}

/**********************************************************************
 * Function_Name: SetAsEye
 * Return 		:
 * Comments 	:
 **********************************************************************/
int Matrix::SetAsEye( double(&Mat)[4][4])
{
	SetMat(Mat, 0);

	for(int i = 0; i < 4; i++ )
	{
		for(int j = 0; j < 4; j++ )
		{
			if( i == j)
			{
				Mat[j][i] = 1;
			}
		}
	}

	return EXIT_SUCCESS;
}

/**********************************************************************
 * Function_Name: Overload <<
 * Return 		:
 * Comments 	: Prints a 4 x 4 Matrix
 **********************************************************************/
std::ostream& operator<<( std::ostream& out, const double (&Mat)[4][4])
{

	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			out << " ";
			out.precision(10);
			out.width(20);
			out << Mat[i][j];
		}

		out << endl;
	}

	return out;
}


/**********************************************************************
 * Function_Name: Overload <<
 * Return 		:
 * Comments 	: Prints a 4 x 1 Matrix
 **********************************************************************/
std::ostream& operator<< ( std::ostream& out, const double *Mat)
{

	for(int i = 0; i < 4; i++)
	{
		out << Mat[i] << endl;
	}

	cout << endl;

	return out;
}



/**********************************************************************
 * Function_Name: ElementWiseMultiply
 * Return 		: int
 * Comments 	: Performns element wise multiplication of one element
 * 					with the another
 **********************************************************************/
int Matrix::ElementWiseMultiply( double* ans, const double* Mat1, const double* Mat2 )
{
	for( unsigned int i = 0; i < 3; i++ )
	{
		ans[i] = Mat1[i] * Mat2[i];
	}

	return EXIT_SUCCESS;
}


/**********************************************************************
 * Function_Name: ElementWiseMultiply
 * Return 		: int
 * Comments 	: Performns element wise multiplication of one element
 * 					with the another
 **********************************************************************/
int Matrix:: ElementWiseMultiply( double* ans, const unsigned int* Mat1, const double* Mat2 )
{
	for( unsigned int i = 0; i < 3; i++ )
	{
		ans[i] = Mat1[i] * Mat2[i];
	}

	return EXIT_SUCCESS;
}



/**********************************************************************
 * Function_Name: MultiplyByConst
 * Return 		:
 * Comments 	:
 **********************************************************************/
int Matrix::MultiplyByConst(double* ans, double * Mat, const double d)
{

	for( unsigned int i = 0; i < 3; i++ )
	{
		ans[i] = Mat[i] * d;
	}

	return EXIT_SUCCESS;
}


/**********************************************************************
 * Function_Name: Print
 * Return 		:
 * Comments 	:
 **********************************************************************/
int Matrix::Print(double *Mat, string str = "" )
{

	cout << str << " ";
	for( unsigned int i = 0; i < 3; i++ )
	{
		cout << Mat[i] << " ";
	}

	cout << endl;

	return EXIT_SUCCESS;
}


/**********************************************************************
 * Function_Name: BuildMat
 * Return 		:
 * Comments 	:
 **********************************************************************/
int Matrix::BuildMat( double(&Mat)[3][3], const double* x0, const double* x1, const double * x2)
{

	for (unsigned int i = 0; i < 3; i++)
	{
		for (unsigned  int j = 0; j < 3; j++)
		{
			if( j == 0 )
			{
				Mat[i][j] = x0[i];
			}
			else if( j == 1 )
			{
				Mat[i][j] = x1[i];
			}
			else if( j == 2 )
			{
				Mat[i][j] = x2[i];
			}
		}
	}


	return EXIT_SUCCESS;
}


/**********************************************************************
 * Function_Name: BuildMat
 * Return 		:
 * Comments 	:
 **********************************************************************/
int Matrix::MultiplyByConst( double(&ans)[3][3], const double(&Mat)[3][3], const double d)
{

	for( int iCol = 0; iCol < 3; iCol++ )
	{
		for( int iRow = 0; iRow < 3; iRow++)
		{
			ans[iRow][iCol] = Mat[iRow][iCol] * d;
		}
	}

	return EXIT_SUCCESS;
}
