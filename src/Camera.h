/*
 * Camera.h
 *
 *  Created on: Oct 6, 2012
 *      Author: hrushi
 */

#ifndef CAMERA_H_
#define CAMERA_H_

#include "Transformation.h"
#include "Vertex.h"

#include "Includes.h"

class Camera: private Transformation
{

protected:

	double focal_length;

	VectorSpace VPN;
	VectorSpace VUP;
	VectorSpace VRP;
	Vertex Focal_Point;
	VectorSpace n, u, v;

	int CopyCam( const Camera& rhsCam ); // Copy the Camera
	int AllocateCam( const Camera& rhsCam ); // Allocate the Camera

	int MergeIntoPRT(double (&R)[4][4], const VectorSpace& u, const VectorSpace& v, const VectorSpace& n );
	int Make_P( double(&P)[4][4] );

public:

	/********** House Keeping ***********/
	Camera();
	Camera( const Camera& rhsCam);// Copy Constructor
	Camera& operator=( const Camera& rhsCam ); // Copy the camera
	virtual ~Camera();

	// Standalone function for Camera
	friend std::istringstream& operator>>( std::istringstream& iss_line, Camera& cam);
	friend std::ostream& operator<<( std::ostream& out, Camera& cam);

	int MakePRT();
	VectorSpace Get_u() const {return u;}
	VectorSpace Get_v() const {return v;}
	VectorSpace Get_n() const {return n;}
	Vertex GetFocalPoint() const { return Focal_Point; }
	double GetFocalLength() const { return focal_length; }
	VectorSpace Get_VPN() const { return VPN; }

	Vertex ProjectPointToCam(const Vertex& Vt);

	Vertex LocateFocalPoint(); // Given the VRP, VPN, and the focal_length, it locates the focal_point;

	// Public Variables
	string CamName;
	double PRT[4][4];

};


#endif /* CAMERA_H_ */
