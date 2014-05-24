/*
 * Drawing.h
 *
 *  Created on: Oct 17, 2012
 *      Author: hrushi
 */

#ifndef DRAWING_H_
#define DRAWING_H_

#include "SlopePtLine.h"
#include "CImage.h"
#include "Vertex.h"

#include "Includes.h"

class Drawing {
public:
	Drawing();
	virtual ~Drawing();

	int Line( CImage& image,  Vertex& V1,  Vertex& V2 ); // Draws line from V1 to V2;
};

#endif /* DRAWING_H_ */
