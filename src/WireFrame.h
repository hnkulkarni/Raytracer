/*
 * WireFrame.h
 *
 *  Created on: Oct 17, 2012
 *      Author: hrushi
 */

#ifndef WIREFRAME_H_
#define WIREFRAME_H_

#include "Clipping.h"
#include "Drawing.h"
#include "Scene.h"
#include "CImage.h"

#include "Includes.h"

class WireFrame: public Matrix{

private:

	double Limits[4];
	string camName;
	double ProjMat[4][4];

	Clipping Clip;

public:
	WireFrame();
	WireFrame(istringstream& iss_line);
	virtual ~WireFrame();

	CImage Render(  Scene &s );

	friend std::ostream& operator<<( std::ostream& out, const WireFrame& W);

	Vertex ProjectPtOnImage(Vertex Pt);

	int CreateProjectionMatrix();


};


// Functions for Operator Overloading


// Initialize the Static Variable

#endif /* WIREFRAME_H_ */
