/*
 * Drawing.cpp
 *
 *  Created on: Oct 17, 2012
 *      Author: hrushi
 */

#include "Drawing.h"

/**********************************************************************
 * Function_Name: Default Constructor
 * Return 		:
 * Comments 	:
 **********************************************************************/
Drawing::Drawing()
{
	// DONE Auto-generated constructor stub

	// Nothing much to do

}


/**********************************************************************
 * Function_Name: Default Destructor
 * Return 		:
 * Comments 	:
 **********************************************************************/
Drawing::~Drawing() {
	// DONE Auto-generated destructor stub

	// Nothing much to remove.
}


/**********************************************************************
 * Function_Name: DrawLine
 * Return 		:
 * Comments 	:
 **********************************************************************/
int Drawing::Line( CImage& image,  Vertex& V1,  Vertex& V2 ) // Draws line from V1 to V2;
{

	double x0 = V1.arr[0];
	double y0 = V1.arr[1];

	double x1 = V2.arr[0];
	double y1 = V2.arr[1];

/*
 * Drawing line using a premitive Slope Point Format. Very slow process.
 */
	SlopePtLine Spl;
	Spl.Draw(image, x0, y0, x1, y1);

	return EXIT_SUCCESS;
}

