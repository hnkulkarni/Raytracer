/*
 * Constants.h
 *
 *  Created on: Sep 22, 2012
 *      Author: hrushi
 */

#ifndef CONSTANTS_H_
#define CONSTANTS_H_

const int NO_SUCH_GROUP = -1;

const bool INPUT = true;

const bool OUTPUT = false;

const unsigned int MIN_VERTICES_PER_FACE = 3;

const bool TRUE = 1;

const bool FALSE = 0;

const int SCALE = 3; // in the sense of x, y, z, scale

const double SOME_SMALL_VALUE = 1e-6;

const bool CRITICAL_DEBUG = 0; // Prints out every small value.

const unsigned int MAX_COLOR_VAL = 256;

const unsigned int NUM_VALUES_IN_MTL = 8;

const char STARS[256] = "**********************************************";

const char FEW_STARS[256] = "*********";

const int VIEW_PORT_MIN = -1;
const int VIEW_PORT_MAX = 1;

const unsigned int VIEW_PORT_WIDTH = VIEW_PORT_MAX - VIEW_PORT_MIN;

const unsigned int N_AIR = 1;



#endif /* CONSTANTS_H_ */
