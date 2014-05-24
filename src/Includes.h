/*
 * Includes.h
 *
 *  Created on: Sep 22, 2012
 *      Author: hrushi
 *
 *      This file contains all the standard includes that need to be included in multiple classes
 */

#ifndef INCLUDES_H_
#define INCLUDES_H_

#include <stdio.h>
#include <stdlib.h>

#include <vector>

//Includes for FileIO
#include<iostream>
#include<fstream>

//Includes for String
#include <string>
#include <sstream>
#include <cstring>

// Include all Constants
#include "Constants.h"

// Include all Error Codes
#include "Errors.h"

//Include vector
#include<vector>

//Time for Output File
#include <time.h>

// For all STL Algorithms
#include <algorithm>

// For all the Math Functions
#include <cmath>
#include <math.h>

// Formatting the output
#include <iomanip>

// Standard Exception
#include <stdexcept>


// For Maps
#include <map>

// For Floating point operations
#include <float.h>

// For File Parts
#include <libgen.h>

// STD - Flush
#include <unistd.h>



//Adding From Namespaces
using std::cout;
using std::endl;
using std::string;
using std::fstream;
using std::cerr;
using std::istringstream;
using std::vector;
using std::unique;
using std::unique_copy;
using std::sort;
using std::binary_search;
using std::setw;
using std::setfill;
using std::out_of_range;
using std::map;

#endif /* INCLUDES_H_ */
