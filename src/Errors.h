/*
 * Errors.h
 *
 *  Created on: Oct 12, 2012
 *      Author: hrushi
 */

#ifndef ERRORS_H_
#define ERRORS_H_

const int ERR_FILE_NOT_FOUND 			= 1;
const int ERR_CANNOT_READ_DOUBLE 		= 2;
const int ERR_CANNOT_READ_INDEX2VERTEX 	= 3;
const int ERR_CANNOT_READ_GROUPNAME 	= 4;
const int ERR_LESS_THAN_MIN_VERTICES	= 5;
const int ERR_NON_COPLANAR_FACES		= 6;
const int ERR_COLINEAR 					= 7;
const int ERR_CONVEX					= 8;
const int ERR_SHARED_VERTEX				= 9;
const int ERR_READING_CMD				= 10;
const int ERR_MAT_NOT_ROTATION			= 11;
const int ERR_GRP_NOT_FOUND				= 12;
const int ERR_VECTOR_OUT_OF_RANGE		= 13;
const int ERR_ERROR_READING_VECTOR		= 14;
const int ERR_CANNOT_READ_CAM			= 15;
const int ERR_CAM_NOT_FOUND				= 16;
const int ERR_CANNOT_READ_MTL			= 17;
const int ERR_CANNOT_READ_ELLIPSE		= 18;
const int ERR_RAY_TRACE_CMD				= 19;
const int ERR_READING_LIGHT_SRC			= 20;
const int ERR_ALLOC						= 21;
const int ERR_ASSOCIATING_MTLNAME		= 22;

#endif /* ERRORS_H_ */
