/*
 * SlopePtLine.h
 *
 *  Created on: Oct 20, 2012
 *      Author: hrushi
 */

#ifndef SLOPEPTLINE_H_
#define SLOPEPTLINE_H_

#include "CImage.h"

#include "Includes.h"

class SlopePtLine {

private:


public:
	SlopePtLine();
	virtual ~SlopePtLine();

	int Draw(CImage& Frame, const double x0, const double y0, const double x1, const double y1 );
	double GetSlope( const double x0, const double y0, const double x1, const double y1 );
};

#endif /* SLOPEPTLINE_H_ */
