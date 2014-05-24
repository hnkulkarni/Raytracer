/*
 * RayTrace.h
 *
 *  Created on: Nov 18, 2012
 *      Author: hrushi
 */

#ifndef RAYTRACE_H_
#define RAYTRACE_H_

#include "Scene.h"
#include "CImage.h"
#include "Color.h"
#include "SurfMin.h"
#include "Material.h"

#include "Includes.h"

class RayTrace
{


public:

	/**********************************************************************
	 * Function Type : Constructors, Destructors
	 * Comments 	:
	 **********************************************************************/
	RayTrace();
	RayTrace(istringstream& iss_line, const string& CmdFileName);
	virtual ~RayTrace();


	/**********************************************************************
	 * Function Type : Member Functions
	 * Comments 	 :
	 **********************************************************************/
	int AppendPPMToPath( const string& CmdFilePath, string& Path ); // Appends a .ppm if required.
	CImage Render( const Scene& s );
	CImage Render( );

	Color RayReflectance( const VectorSpace& Ray, const Scene& s, const Vertex& RayOrigin, const unsigned int CurrentReflectedDepth, const unsigned int CurrentRefractedDepth )const;
	Color PointReflectance( const Vertex& PtIn3D, const VectorSpace& Ray, const Scene& s, const SurfMin& Smin) const;
	Color DiffuseReflectance( const Material& GroupMtl, const Color& LightColor, const double LDotN) const;
	Color SpecularReflectance(const VectorSpace& LightVector, const Color& LightColor,  const VectorSpace & SurfaceNormal, const Material& GroupMtl, const VectorSpace& Ray, const double LDotN) const;
	VectorSpace GetReflactanceRay( const double LDotN,  const VectorSpace& LightVector, const VectorSpace& SurfaceNormal ) const;

	// Recursive Functions
	Color ReflectedRecursion( const VectorSpace& Ray, const Scene& s, const Vertex& PtIn3D, const SurfMin& Smin, const unsigned int iCurrentDepth) const;
	Color RefractedRecursion( const VectorSpace& Ray, const Scene& s, const Vertex& PtIn3D, const SurfMin& Smin, const unsigned int iCurrentDepth) const;
	double CalculateBeta( const VectorSpace& Ray, const VectorSpace& SurfNormal, const double Mu ) const;

	// Get the point on SurfMin, along the ray
	Vertex GetPointIn3D( const Vertex& RayOrigin, const VectorSpace& Ray, const double t) const;
	Material GetMaterial( const Scene& s, const SurfMin & Smin) const;

	bool ExternalShadows(const Vertex& Pt, const VectorSpace& LightRay, const Scene& s,  const SurfMin& Smin) const;

	/**********************************************************************
	 * Function Type : Member Variables
	 * Comments 	 :
	 **********************************************************************/
	string OutputPath;
	unsigned int width;
	unsigned int height;
	unsigned int depth;


};

#endif /* RAYTRACE_H_ */
