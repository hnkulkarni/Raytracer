/*
 * DoMath.cpp
 *
 *  Created on: Oct 20, 2012
 *      Author: hrushi
 */

#include "DoMath.h"

/**********************************************************************
 * Function_Name: Default Constructor
 * Return 		:
 * Comments 	:
 **********************************************************************/
DoMath::DoMath() {
	// DONE Auto-generated constructor stub

}


/**********************************************************************
 * Function_Name: Default Destructor
 * Return 		:
 * Comments 	:
 **********************************************************************/
DoMath::~DoMath() {
	// DONE Auto-generated destructor stub
}


/**********************************************************************
 * Function_Name: CalcSlope
 * Return 		:
 * Comments 	: Calculates the Slope of the line joining the two Vertex
 **********************************************************************/
double DoMath::CalcSlope(const Vertex& V1, const Vertex& V2 )
{

	double slope = 0;

	slope = (double)(V1.arr[1] - V2.arr[1])/(V1.arr[0] - V2.arr[0]) ;

	return slope;

}
