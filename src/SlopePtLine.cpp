/*
 * SlopePtLine.cpp
 *
 *  Created on: Oct 20, 2012
 *      Author: hrushi
 */

#include "SlopePtLine.h"


/**********************************************************************
 * Function_Name: Default Constructor
 * Return 		:
 * Comments 	:
 **********************************************************************/
SlopePtLine::SlopePtLine() {
	// DONE Auto-generated constructor stub

}


/**********************************************************************
 * Function_Name: Default Destructor
 * Return 		:
 * Comments 	:
 **********************************************************************/
SlopePtLine::~SlopePtLine() {
	// DONE Auto-generated destructor stub
}


/**********************************************************************
 * Function_Name: DrawLine
 * Return 		:
 * Comments 	: Draws the line from Vertex P1 to Vertex P2 using the
 * 					slope point form. It is simple, quick to implement,
 * 					but very slow.
 **********************************************************************/
int SlopePtLine:: Draw(CImage& Frame, const double ax, const double ay, const double bx, const double by  )
{
	double tempx, tempy;
	double x0 = ax;
	double y0 = ay;
	double x1 = bx;
	double y1 = by;

	if(x1 < x0)
	{
		tempx = x0;
		x0 = x1;
		x1 = tempx;

		tempy = y0;
		y0 = y1;
		y1 = tempy;
	}

	double slope = GetSlope(x0, y0, x1, y1);
	double slope_inv = (double)1/slope;

	int x = 0;
	int y = 0;

	Frame.SetPixel(x0,y0, 255, 255, 255);
	if( slope >= 1  )
	{
		// Y Major
		for( y = y0; y <= y1; y++)
		{
			x = x0 + slope_inv * (y - y0);
			Frame.SetPixel(x,y, 255, 255, 255);
		}
	}

	// X Major
	else if( slope >= 0 && slope < 1)
	{
		for(x = x0; x <= x1; x++)
		{
			y = y0 + slope * (x - x0);
			Frame.SetPixel(x,y, 255, 255, 255);
		}
	}
	else if( slope < 0 && slope > -1)
	{
		for( x = x0; x <= x1; x++)
		{
			y = y0 + slope * (x - x0);
			Frame.SetPixel(x,y, 255, 255, 255);
		}
	}
	else if( slope < -1 )
	{
		// Y Major
		for( y = y0; y >= y1; y--)
		{
			x = x0 + slope_inv * (y - y0);
			Frame.SetPixel(x,y, 255, 255, 255);
		}
	}



	return EXIT_SUCCESS;
}


/**********************************************************************
 * Function_Name: Slope
 * Return 		:
 * Comments 	:
 **********************************************************************/
double SlopePtLine::GetSlope( const double x0, const double y0, const double x1, const double y1 )
{
	double s = (double)(y1 - y0)/(x1 - x0);
	return s;
}
