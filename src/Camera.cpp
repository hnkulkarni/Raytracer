/*
 * Camera.cpp
 *
 *  Created on: Oct 6, 2012
 *      Author: hrushi
 */

#include "Camera.h"


/**********************************************************************
 * Function_Name: Default Constructor
 * Return 		:
 * Comments 	:
 **********************************************************************/
Camera::Camera()
{

	//Initialize the Camera PRT matrix to Zero
	SetMat(PRT, 0 );
	focal_length = 0;

}

/**********************************************************************
 * Function_Name: Copy Constructor
 * Return 		:
 * Comments 	:
 **********************************************************************/
Camera::Camera(const Camera &rhsCam)
{
	AllocateCam(rhsCam);
	CopyCam(rhsCam);
}


/**********************************************************************
 * Function_Name: Overloading=
 * Return 		:
 * Comments 	:
 **********************************************************************/
Camera& Camera::operator=(const Camera &rhsCam)
{

	AllocateCam(rhsCam);
	CopyCam(rhsCam);

	return *this;
}
/**********************************************************************
 * Function_Name: CopyCam
 * Return 		:
 * Comments 	:
 **********************************************************************/
int Camera::CopyCam(const Camera& rhsCam)
{

	CamName = rhsCam.CamName;
	focal_length = rhsCam.focal_length;

	for(int i = 0; i < 4; i++ )
	{
		for( int j = 0; j < 4; j++ )
		{
			PRT[i][j] = rhsCam.PRT[i][j];
		}
	}

	VPN = rhsCam.VPN;
	VUP = rhsCam.VUP;
	VRP = rhsCam.VRP;

	u = rhsCam.u;
	v = rhsCam.v;
	n = rhsCam.n;

	Focal_Point = rhsCam.Focal_Point;

	return EXIT_SUCCESS;
}
/**********************************************************************
 * Function_Name: AllocateCam
 * Return 		:
 * Comments 	: Allocates the required space for the camera
 **********************************************************************/
int Camera::AllocateCam(const Camera& rhsCam)
{


	return EXIT_SUCCESS;
}
/**********************************************************************
 * Function_Name: Default Destructor
 * Return 		:
 * Comments 	:
 **********************************************************************/
Camera::~Camera() {
	// DONE Auto-generated destructor stub
}



/**********************************************************************
 * Function_Name: Operator >>
 * Return 		:
 * Comments 	: Overloaded for reading the camera
 **********************************************************************/
std::istringstream& operator>>( std::istringstream& iss_line, Camera& cam)
{

	iss_line.exceptions(istringstream::failbit | istringstream::badbit);

	try
	{

		// Copy the Camera Name
		iss_line >> cam.CamName;

		// Copy the Camera Focal length
		iss_line >> cam.focal_length;

		// Copy the VRP
		try
		{

			iss_line >> cam.VRP;

		}
		catch(int n)
		{
			if(n == ERR_ERROR_READING_VECTOR)
			{
				cerr << "Cannot read VRP " << endl;
				throw ERR_ERROR_READING_VECTOR;
			}
		}

		// Copy the VPN

		try
		{
			iss_line >> cam.VPN;

		}
		catch(int n)
		{
			if(n == ERR_ERROR_READING_VECTOR)
			{
				cerr << "Cannot read VPN " << endl;
				throw ERR_ERROR_READING_VECTOR;
			}
		}


		// Copy the VUP
		try
		{
			iss_line >> cam.VUP;

		}
		catch(int n)
		{
			if(n == ERR_ERROR_READING_VECTOR)
			{
				cerr << "Cannot read VUP " << endl;
				throw ERR_ERROR_READING_VECTOR;
			}
		}
	}
	catch( istringstream::failure &e)
	{

		cerr << "Error Reading Cameras " << e.what() << endl;
		exit( ERR_CANNOT_READ_CAM );
	}


	return iss_line;
}


/**********************************************************************
 * Function_Name: Operator <<
 * Return 		:
 * Comments 	: Overloaded for printing Camera Prameters
 **********************************************************************/
std::ostream& operator<<( std::ostream& out, Camera& cam)
{
	out << STARS << endl;
	out << "Name :" << cam.CamName << endl;
	out << "Focal Length : " << cam.focal_length << endl;
	out << "VRP  : " << cam.VRP << endl;
	out << "VPN  : " << cam.VPN << endl;
	out << "VUP  : " << cam.VUP << endl;

	out << "PRT Matrix " << endl;
	out << cam.PRT << endl;

	out << "Camera U Vector ";
	out << cam.Get_u() << endl;

	out << "Camera V Vector ";
	out << cam.Get_v() << endl;

	out << "Camera N Vector ";
	out << cam.Get_n() << endl;

	out << STARS << endl;

	return out;
}

/**********************************************************************
 * Function_Name: MakePRT
 * Return 		:
 * Comments 	: Creates the Camera Matrix using the given VRP, VPN, VUP
 **********************************************************************/
int Camera::MakePRT()
{

	// Create Translation Matrix
	double T[4][4];
	SetAsEye(T);
	T[3][3] = 1;

	VectorSpace NegVRP = VRP * -1;

	// Fill in the proper places in the T Matrix for the VRP
	for(int i = 0; i < 3; i++)
	{
		T[i][3] = NegVRP.vs[i];
	}

	// Creating Camera Rotation Matrix
	double R[4][4];
	SetMat(R, 0);
	R[3][3] = 1;

	VPN.DoNormalization();
	VUP.DoNormalization();

	n = VPN; // NVector

	u =  VUP * n ; // Cross Product, overloaded operator *

	u.DoNormalization();

	v = n * u;
	v.DoNormalization();

	MergeIntoPRT(R, u, v, n);

	// Creating Camera P Matrix
	double P[4][4];
	Make_P(P);

	if(CRITICAL_DEBUG)
	{
		Print(P, "Camera Projection Matrix ");
	}

	MatrixMult(PRT, P, R, T);

	Focal_Point = LocateFocalPoint();

	return EXIT_SUCCESS;
}

/**********************************************************************
 * Function_Name: Make_P
 * Return 		:
 * Comments 	: Creates a Projection Matrix P, using the Focal Length
 * 					from the member variable
 **********************************************************************/
int Camera::Make_P( double(&P)[4][4] )
{

	if( focal_length > DBL_MIN )
	{

	SetMat(P, 0);
	P[0][0] = 1;
	P[1][1] = 1;
	P[3][3] = 1;

	P[3][2] = (double)1/focal_length;


	}
	else
	{
		cerr << "Focal Length is zero, please check" << endl;
		exit( EXIT_FAILURE);
	}

	return EXIT_SUCCESS;
}
/**********************************************************************
 * Function_Name: MakePRT
 * Return 		:
 * Comments 	: Creates the Camera Matrix using the given VRP, VPN, VUP
 **********************************************************************/
int Camera::MergeIntoPRT(double (&R)[4][4], const VectorSpace& u, const VectorSpace& v, const VectorSpace& n )
{

	for( int i = 0; i < 3; i++)
	{
		for( int j = 0; j < 3; j++)
		{
			switch(i)
			{
			case 0:
				R[i][j] = u.vs[j];
				break;

			case 1:
				R[i][j] = v.vs[j];
				break;

			case 2:
				R[i][j] = n.vs[j];
				break;
			}
		}
	}

	return EXIT_SUCCESS;
}


/**********************************************************************
 * Function_Name: ProjectPointToCam
 * Return 		:
 * Comments 	: Projects the point to the Image plane. Returns the point.
 **********************************************************************/
Vertex Camera::ProjectPointToCam(const Vertex& Vt)
{
	Vertex VTemp = Vt;
	Matrix Mat;

	Mat.MatOnPt(PRT, VTemp.arr);


	return VTemp;
}

/**********************************************************************
 * Function_Name: LocateFocalPoint
 * Return 		:
 * Comments 	: Given the VRP, VPN, and the Focal_Length, it locates the
 * 					Focal_
 **********************************************************************/
Vertex Camera::LocateFocalPoint()
{

	Vertex Fp_point;

	VectorSpace NegVPN = -1 * VPN;

	Vertex VRP_pt( VRP ); // Taking the Point of the vector. Confusing, but this
							// has been done because the VRP was creates as a vectorspace.
	Fp_point = VRP_pt + ( focal_length * NegVPN );

	return Fp_point;
}


