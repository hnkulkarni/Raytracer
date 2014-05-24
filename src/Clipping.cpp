/*
 * Clipping.cpp
 *
 *  Created on: Oct 17, 2012
 *      Author: hrushi
 */

#include "Clipping.h"

/**********************************************************************
 * Function_Name: Default Constructor
 * Return 		:
 * Comments 	:
 **********************************************************************/
Clipping::Clipping() {
	// DONE Auto-generated constructor stub

	SetMat(ClipLimits, 0);
	xmin = ymin = xmax = ymax = 0;

}

/**********************************************************************
 * Function_Name: Default Destructor
 * Return 		:
 * Comments 	:
 **********************************************************************/
Clipping::~Clipping() {
	// DONE Auto-generated destructor stub
}



/**********************************************************************
 * Function_Name: SetLimits
 * Return 		:
 * Comments 	: Set the Clipping Limits to xmin, ymin, xmax, ymax
 **********************************************************************/
int Clipping::SetLimits(const double xMinLim, const double yMinLim, const double xMaxLim, const double yMaxLim )
{

	ClipLimits[0] = xMinLim;
	ClipLimits[1] = yMinLim;
	ClipLimits[2] = xMaxLim;
	ClipLimits[3] = yMaxLim;


	xmin = xMinLim;
	ymin = yMinLim;

	xmax = xMaxLim;
	ymax = yMaxLim;

	return EXIT_SUCCESS;
}



/**********************************************************************
 * Function_Name: SetLimits
 * Return 		:
 * Comments 	: Set the Clipping Limits to xmin, ymin, xmax, ymax
 **********************************************************************/
int Clipping::SetLimits(const double* Lim )
{

	for(int i = 0; i < 4; i++)
	{
		ClipLimits[i] = Lim[i];

		switch(i)
		{
		case 0:
			xmin = Lim[i];
			break;

		case 1:
			ymin = Lim[i];
			break;

		case 2:
			xmax = Lim[i];
			break;

		case 3:
			ymax = Lim[i];
			break;
		}
	}

	return EXIT_SUCCESS;
}

/**********************************************************************
 * Function_Name: ClipLine
 * Return 		:
 * Comments 	: The points are passed as a reference. The pints are
 * 					side-effected. The end points are passed as it is.
 **********************************************************************/
int Clipping::ClipLine(Vertex& V1, Vertex& V2)
{

	int V1_ClippingCode;
	int V2_ClippingCode;

	Vertex Intersection; // A Temp Vertex for intersection.
	int Intrstin_ClipCode = INSIDE;
	bool bAccept_Rej = false;

	double x,y, x0, y0, x1, y1;

	while(true)
	{
		V1_ClippingCode = GetCode(V1);
		V2_ClippingCode 	= GetCode(V2);
		/*
		 * Trivially accept or reject
		 */
		if( !(V1_ClippingCode | V2_ClippingCode) ) // Trivially Accept, or( code1, code2 ) = 0
		{
			bAccept_Rej = true;
			break; // Break the While Loop
		}
		else
		{
			if( V1_ClippingCode & V2_ClippingCode ) // Trivially Reject, and( code1, code2 ) != 0
			{
				bAccept_Rej = false;
				break;
			} // Trivial Reject
			else
			{

				// Pick any point outside the clipping plane.
				if( V1_ClippingCode != INSIDE )
				{
					Intrstin_ClipCode = V1_ClippingCode;
				}
				else
				{
					Intrstin_ClipCode = V2_ClippingCode;
				}

				/*
				 * Finding the Intersection Point using Slope Intersept Form
				 *  y = y0 + slope * (x1 - x0)
				 *  x = x0 + 1/slope * (y1 - y0)
				 */
				x0 = V1.arr[0];
				y0 = V1.arr[1];

				x1 = V2.arr[0];
				y1 = V2.arr[1];

				if( Intrstin_ClipCode & TOP )
				{
					x = x0 + (x1 - x0) * (ymax - y0) / (y1 - y0);
					y = ymax;
				}
				else if( Intrstin_ClipCode & BOTTOM)
				{
					x = x0 + (x1 - x0) * (ymin - y0) / (y1 - y0);
					y = ymin;
				}

				else if( Intrstin_ClipCode & RIGHT )
				{
					x = xmax;
					y = y0 + (y1 - y0) * (xmax - x0) / (x1 - x0);
				}
				else
				{
					x = xmin;
					y = y0 + (y1 - y0) * (xmin - x0) / (x1 - x0);
				}


				// Copying the points
				if( Intrstin_ClipCode & V1_ClippingCode)
				{
					V1.arr[0] = x;
					V1.arr[1] = y;
				}
				else
				{
					V2.arr[0] = x;
					V2.arr[1] = y;
				}

			} // Systematic Clipping
		}// Trivial Accept


	}// While Loop Ends

	return bAccept_Rej;
}

/**********************************************************************
 * Function_Name: GetCode
 * Return 		:
 * Comments 	: Returns the Clipping code for the the given point
 **********************************************************************/
int Clipping::GetCode(const Vertex Pt)
{

	int ClippingCode = INSIDE;

	// Check the X - LIMITS
	// If X is on the Left
	if( Pt.arr[0] < xmin)
	{
		ClippingCode |= LEFT;
	} // If X is on the Right
	else if( Pt.arr[0] > xmax)
	{
		ClippingCode |= RIGHT;
	}

	// Check the Y - LIMITS
	// Below Ymin
	if( Pt.arr[1] < ymin)
	{
		ClippingCode |= BOTTOM;
	} // Above Ymax
	else if( Pt.arr[1] > ymax)
	{

		ClippingCode |= TOP;
	}

	return ClippingCode;
}
