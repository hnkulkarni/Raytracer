/*
 * WireFrame.cpp
 *
 *  Created on: Oct 17, 2012
 *      Author: hrushi
 */

#include "WireFrame.h"



/**********************************************************************
 * Function_Name: Default Constructor
 * Return 		:
 * Comments 	:
 **********************************************************************/
WireFrame::WireFrame() {
	//  Auto-generated constructor stub

	for( int i = 0; i < 4; i++)
	{
		Limits[i] = 0;
	}

	SetMat(ProjMat,0);


}


/**********************************************************************
 * Function_Name: Overloaded Constructor
 * Return 		:
 * Comments 	: Takes in command line and fills in the member
 * 					variables
 **********************************************************************/
WireFrame::WireFrame(istringstream& iss_line)
{
	iss_line.exceptions(istringstream::failbit | istringstream::badbit);

	try
	{
		iss_line >> camName;

		for( int i = 0; i < 4; i++)
		{
			iss_line >> Limits[i];
		}
	}
	catch(istringstream::failure &e)
	{
		if( !iss_line.eof() )
		{
			cerr << "Error Reading WireFrame Data " << endl;
			exit( EXIT_FAILURE);
		}
	}

	// Create the Projection Matrix
	CreateProjectionMatrix();


}
/**********************************************************************
 * Function_Name: Default Destructor
 * Return 		:
 * Comments 	:
 **********************************************************************/
WireFrame::~WireFrame() {
	//  Auto-generated destructor stub
}


/**********************************************************************
 * Function_Name: Operator Overload << Print
 * Return 		:
 * Comments 	:
 **********************************************************************/
std::ostream& operator<<( std::ostream& out, const WireFrame& W)
{

	out << "Cam Name: " << W.camName << endl;
	out << " Xmin : " << W.Limits[0] << "\t";
	out << " Ymin : " << W.Limits[1] << endl;
	out << " Xmax : " << W.Limits[2] << "\t";
	out << " Ymax : " << W.Limits[3] << endl;
	out << " Proj : " << W.ProjMat << endl;
	out << endl;

	return out;
}

/**********************************************************************
 * Function_Name: Do
 * Return 		: Frame Buffer
 * Comments 	: Does everthing that is asked in the Assignment
 * 					1. Finds the Correct Camera Matrix;
 * 					2. Projects all the points on the image plane.
 * 					3. Clips the Lines
 * 					4. Calls Bresenham
 * 					5. Populates the Frame Buffer
 **********************************************************************/
CImage WireFrame::Render( Scene &s )
{
	CImage Frame(Limits);
	Drawing Draw;

	Vertex V1, V2;

	unsigned int camIdx = 0;
	if( !camName.length()  )
	{

		cerr << "Cam Name cannot be read in Wire-Frame" << endl;
		throw ERR_CAM_NOT_FOUND;
		exit( ERR_CAM_NOT_FOUND);
	}

	camIdx = s.FindCam(camName);
	cout << s.c.at(camIdx) << endl;


	vector<int>::iterator itNext;
	int iIdx2Vtx_Curr = 0;
	int iIdx2Vtx_Next = 0;

	// Declare a Clipping Plane
	Clip.SetLimits(Limits);

	bool bAccept_Rej;

	// For Every Group
	vector<int>::iterator itLast;
	for(unsigned int iG = 0; iG < s.g.size(); iG++)
	{
		// For Every Face in the Group
		for( unsigned int iF = 0; iF < s.g.at(iG).f.size(); iF++)
		{
			// For Every Vertex Pointed in the Face
			itLast = s.g.at(iG).f.at(iF).Index2Vertex.end() -1;
			for( vector<int>::iterator itCurr = s.g.at(iG).f.at(iF).Index2Vertex.begin(); itCurr < s.g.at(iG).f.at(iF).Index2Vertex.end();  itCurr++ )
			{

				if( itCurr == itLast)
				{
					itNext 	 = s.g.at(iG).f.at(iF).Index2Vertex.begin();
				}
				else
				{
					itNext = itCurr + 1;
				}

				iIdx2Vtx_Curr = *itCurr - 1; // The indexes in the model file are 1 indexed
				iIdx2Vtx_Next = *itNext - 1; // The indexes in the model file are 1 indexed. Hence subtracting one

				V1 = s.v.at( iIdx2Vtx_Curr);
				V1 = s.c.at(camIdx).ProjectPointToCam(V1);
				V1.DivideByScale();


				V2 = s.v.at( iIdx2Vtx_Next  );
				V2 = s.c.at(camIdx).ProjectPointToCam(V2);
				V2.DivideByScale();

				bAccept_Rej = Clip.ClipLine(V1, V2); // Points are Side-Effected.

				if( bAccept_Rej )
				{
					/* Project these points on the image plane
					 * in the Wire-Frame Format
					 */
					V1 = ProjectPtOnImage(V1);

					V2 = ProjectPtOnImage(V2);

					Draw.Line(Frame, V1, V2 );

				}
			}
		}

	}
	return Frame;
}


/**********************************************************************
 * Function_Name: WireFrameProjection
 * Return 		:
 * Comments 	:
 **********************************************************************/
Vertex WireFrame::ProjectPtOnImage(Vertex Pt)
{
	Pt.arr[0] += -1 * Limits[0];
	Pt.arr[1] += -1 * Limits[1];

	Pt.arr[1] *= -1;
	Pt.arr[1] += Limits[3] + (-1 * Limits[1]);

	return Pt;
}

/**********************************************************************
 * Function_Name: CreateProjectionMatrix
 * Return 		:
 * Comments 	: Creates the WireFrameProjection matrix.
 **********************************************************************/
int WireFrame::CreateProjectionMatrix()
{
	double a[4][4] = {{0}};
	SetAsEye(a);

	double b[4][4] = {{0}};
	SetAsEye(b);

	double c[4][4] = {{0}};
	SetAsEye(c);

	SetMat(ProjMat, 0);

	// Translate the origin to x_min and y_min
	c[0][3] = -1 * Limits[0]; // -1 * x_min
	c[1][3] = -1 * Limits[1]; // -1 * y_min


	// Translate the origin to the (0 , height)
	double height = Limits[3] - Limits[1]; // height = y_max - y_min
	b[1][3] = -1 * height;


	// Flip the image around X-Axis
	a[0][0] = 0;
	a[0][1] = 1;

	a[1][1] = 0;
	a[1][0] = 1;


	MatrixMult(ProjMat, a, b, c);

	return EXIT_SUCCESS;
}
