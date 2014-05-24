/*
 * Ellipse.cpp
 *
 *  Created on: Nov 17, 2012
 *      Author: hrushi
 */

#include "Ellipse.h"

/**********************************************************************
 * Function_Name: Default Constructor
 * Return 		:
 * Comments 	:
 **********************************************************************/
Ellipse::Ellipse()
{
	// DONE Auto-generated constructor stub
	VertexIndx = 0; /* Since all the vertex index start with 1,
						a zero for a VertexIndx means that it is
						un-initialized.*/
	rx = 0;
	ry = 0;
	rz = 0;

	mean_radius = 0;
	iGroupIdx = -1; // Group index start with 0, so initializing with -1


}


/**********************************************************************
 * Function_Name: Copy Constructor
 * Return 		:
 * Comments 	:
 **********************************************************************/
Ellipse::Ellipse(const Ellipse& rhs)
{
	CopyEllipse(rhs);

}



/**********************************************************************
 * Function_Name: CopyEllipse
 * Return 		:
 * Comments 	:
 **********************************************************************/
int Ellipse::CopyEllipse( const Ellipse& rhs )
{
	VertexIndx = rhs.VertexIndx;
	rx 		= rhs.rx;
	ry 		= rhs.ry;
	rz 		= rhs.ry;
	Center 	= rhs.Center;
	mean_radius = rhs.mean_radius;
	iGroupIdx 	= rhs.iGroupIdx;
	MtlName 	= rhs.MtlName;

	return EXIT_SUCCESS;
}

/**********************************************************************
 * Function_Name: Operator =
 * Return 		:
 * Comments 	:
 **********************************************************************/
Ellipse& Ellipse::operator =(const Ellipse& rhs)
{
	CopyEllipse(rhs);
	return *this;
}



/**********************************************************************
 * Function_Name: Intersection
 * Return 		: double
 * Comments 	: returns the dist_from_sphere, if the intersection
 * 				 	else it returns a -1
 **********************************************************************/
double Ellipse::Intersection(const Vertex& RayOrigin, const VectorSpace& Ray) const
{
	Vertex V_Point = GetInversection_v_Point(RayOrigin, Ray);

	VectorSpace RayOrig2EllipCenter(  RayOrigin.arr, Center.arr );
	VectorSpace RayOrig2Ellip_Norm;
	RayOrig2Ellip_Norm = RayOrig2EllipCenter;
	RayOrig2Ellip_Norm.DoNormalization();

	VectorSpace RayNorm;
	RayNorm = Ray;
	RayNorm.DoNormalization();

	double c_dot_v  = RayOrig2Ellip_Norm.Dot( RayNorm );

	if( c_dot_v > 0 || Ray.RayNVal != 1 ) // Sphere is not behind the ray origin
	{
		double r = mean_radius;
		double c = RayOrigin.Distance( Center );

		double v = V_Point.Distance( RayOrigin );

		double v2 = pow(v,2);
		double c2 = pow(c,2);
		double r2 = pow(r,2);
		double dSquare = r2 - c2 + v2;

		if( dSquare < 0 )
		{
			return -1;
		}
		else
		{
			double d = sqrt( dSquare );
			double t;

			if( Ray.RayNVal == 1)
			{
				t = v - d;
				return t;
			}
			else
			{
				t = v + d;
				return t;
			}
		}

	}

	return -1;
}


/**********************************************************************
 * Function_Name: GetInversection_v_Point
 * Return 		:
 * Comments 	: Get the point on the ray, for which the radius is
 * 					perpendicular, i.e. point on the dot product on the
 * 					ray and the vector joining the camera focal point and
 * 					the center of the sphere
 **********************************************************************/
Vertex Ellipse::GetInversection_v_Point(const Vertex& RayOrigin, const VectorSpace& Ray) const
{
	VectorSpace FP2EllipCenter(  RayOrigin.arr, Center.arr );

	double c_dot_v = FP2EllipCenter.Dot( Ray );

	Vertex L_plus_tu = RayOrigin + c_dot_v * Ray;

	return L_plus_tu;

}
/**********************************************************************
 * Function_Name: DistFromSprCtr
 * Return 		:
 * Comments 	: returns the distance from the center.
 **********************************************************************/
double Ellipse::DistFromSprCtr(const Vertex& Cam_Focal_pt, const VectorSpace& Ray) const
{
	Vertex L_plus_tu = GetInversection_v_Point(Cam_Focal_pt, Ray);

	double dist_from_sphere_center = L_plus_tu.Distance( Center );


	return dist_from_sphere_center;

}
/**********************************************************************
 * Function_Name: Default Destructor
 * Return 		:
 * Comments 	:
 **********************************************************************/
Ellipse::~Ellipse()
{
	// DONE Auto-generated destructor stub
}

/**********************************************************************
 * Function_Name: Operator >>
 * Return 		:
 * Comments 	:
 **********************************************************************/
std::istream& operator>>( std::istream& in, Ellipse& ellp )
{

	in.exceptions(std::istream::failbit | std::istream::badbit );

	try
	{
		in >> ellp.VertexIndx;
		in >> ellp.rx;
		in >> ellp.ry;
		in >> ellp.rz;

		// Calculate the man radius
		ellp.mean_radius = ( ellp.rx + ellp.ry + ellp.rz )/3;

	}
	catch(std::istream::failure &e)
	{
		cerr << "Cannot read Ellipse " << endl;
		exit(ERR_CANNOT_READ_ELLIPSE);
	}

	return in;
}


/**********************************************************************
 * Function_Name: Operator <<
 * Return 		:
 * Comments 	:
 **********************************************************************/
std::ostream& operator<<( std::ostream& out, Ellipse& ellp )
{

	out << "Center ";
	out << ellp.VertexIndx;
	out << endl;

	out << "rx ";
	out << ellp.rx;
	out<< endl;

	out << "ry ";
	out << ellp.ry;
	out << endl;

	out << "rz ";
	out << ellp.rz;
	out << endl;

	out << "Associated with GroupIdx: " << ellp.iGroupIdx;
	out << endl;

	return out;
}


/**********************************************************************
 * Function_Name: GetSurfaceNormal
 * Return 		:
 * Comments 	:
 **********************************************************************/
VectorSpace Ellipse::GetSurfaceNormal( const Vertex& Pt) const
{
	VectorSpace SurfaceNormal;

	SurfaceNormal.CreateVector(Pt.arr, Center.arr);

	return SurfaceNormal;
}

