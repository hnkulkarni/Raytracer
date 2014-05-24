/*
 * Ellipse.h
 *
 *  Created on: Nov 17, 2012
 *      Author: hrushi
 */

#ifndef ELLIPSE_H_
#define ELLIPSE_H_

#include "Vertex.h"
#include "Includes.h"

class Ellipse {
public:
	/**********************************************************************
	 * Function Type : Constructors, Destructors
	 * Comments 	:
	 **********************************************************************/

	Ellipse();
	virtual ~Ellipse();

	Ellipse(const Ellipse& rhs);
	Ellipse& operator=(const Ellipse& rhs );
	int CopyEllipse( const Ellipse& rhs );

	/**********************************************************************
	 * Function Type : Member Functions
	 * Comments 	 :
	 **********************************************************************/
	double Intersection( const Vertex& Cam_Focal_pt, const VectorSpace& Ray) const; // Intersection of the given ray
	// with the ellipse

	double DistFromSprCtr( const Vertex& Cam_Focal_pt, const VectorSpace& Ray) const;
	Vertex GetInversection_v_Point(const Vertex& Cam_Focal_pt, const VectorSpace& Ray) const;

	VectorSpace GetSurfaceNormal( const Vertex& Pt) const;

	/**********************************************************************
	 * Function Type : Member Variables
	 * Comments 	 :
	 **********************************************************************/
	unsigned int  VertexIndx;
	Vertex Center;
	double rx;
	double ry;
	double rz;
	double mean_radius;
	unsigned int iGroupIdx;
	string MtlName;

};

std::istream& operator>>( std::istream& in, Ellipse& ellp );
std::ostream& operator<<( std::ostream& out, Ellipse& ellp );
#endif /* ELLIPSE_H_ */
