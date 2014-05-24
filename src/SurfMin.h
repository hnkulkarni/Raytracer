/*
 * SurfMin.h
 *
 *  Created on: Nov 23, 2012
 *      Author: hrushi
 *
 *
 *      Contains the index to the ( group, face ) or the ( Ellipse ),
 *      set to -1 if no index is defined
 */

#ifndef SURFMIN_H_
#define SURFMIN_H_


#include "Includes.h"

// Constants specific to only SurfMin Class
const int SMIN_UNINITIALIZED = 0;
const int SMIN_POINT_ON_FLAT_SURFACE = 1;
const int SMIN_POINT_ON_ELLIPSE = 2;

class SurfMin {
public:

	/**********************************************************************
	 * Function Type : Constructors, Destructors
	 * Comments 	:
	 **********************************************************************/
	SurfMin();
	virtual ~SurfMin();

	// Copy Constructor
	SurfMin( const SurfMin& rhsSurfMin );

	// Assignment Operator
	SurfMin& operator = ( const SurfMin& rhsSurfMin );

	// CopyFunction
	int CopySurf( const SurfMin& rhsSurfMin );


	/**********************************************************************
	 * Function Type : Member Functions
	 * Comments 	 :
	 **********************************************************************/
	int Set(const int iGroup, const int iFace, const int iEllipse );

	bool operator != ( const SurfMin& rhsSurf ) const;
	bool operator != ( const int CompareVal ) const;

	bool operator == ( const int CompareVal ) const;

	bool CompareSurfs( const SurfMin& rhsSurf ) const;
	bool CompareSurfs( const int CompareIdx ) const;
	bool isValid( const SurfMin& rhsSurf ) const;

	int Type() const;

	/**********************************************************************
	 * Function Type : Member Variables
	 * Comments 	 :
	 **********************************************************************/
	int iGroupIdx;
	int iFaceIdx;
	int iEllipseIdx;

	double tMin; // Contains the intersection 't' value
};

std::ostream& operator<< ( std::ostream& out, const SurfMin Smin );

#endif /* SURFMIN_H_ */
