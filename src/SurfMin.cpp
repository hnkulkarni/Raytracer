/*
 * SurfMin.cpp
 *
 *  Created on: Nov 23, 2012
 *      Author: hrushi
 */

#include "SurfMin.h"

/**********************************************************************
 *					CODE SECTION - Constructors
 **********************************************************************
 1. Constructor
 2. Copy Constructor
 3. Assignment Operator
 4. Copy_SurfMin
 **********************************************************************
 *
 **********************************************************************/


/**********************************************************************
 * Function_Name: Default Constructor
 * Return 		:
 * Comments 	:
 **********************************************************************/
SurfMin::SurfMin() {
	// DONE Auto-generated constructor stub

	iGroupIdx = -1;
	iFaceIdx  = -1;
	iEllipseIdx = -1;

	tMin = DBL_MAX;

}


/**********************************************************************
 * Function_Name: Copy Constructor
 * Return 		:
 * Comments 	:
 **********************************************************************/
SurfMin::SurfMin(const SurfMin& rhsSurfMin )
{

	CopySurf(rhsSurfMin);

}


/**********************************************************************
 * Function_Name: Assignment Operator
 * Return 		:
 * Comments 	:
 **********************************************************************/
SurfMin& SurfMin::operator =(const SurfMin& rhsSurfMin )
{
	CopySurf( rhsSurfMin );

	return *this;
}

/**********************************************************************
 * Function_Name: CopySurfMin
 * Return 		:
 * Comments 	:
 **********************************************************************/
int SurfMin::CopySurf(const SurfMin& rhsSurfMin )
{

	iGroupIdx = rhsSurfMin.iGroupIdx;
	iFaceIdx  = rhsSurfMin.iFaceIdx;
	iEllipseIdx = rhsSurfMin.iEllipseIdx;
	tMin			= rhsSurfMin.tMin;
	return EXIT_SUCCESS;
}


/**********************************************************************
 *					CODE SECTION - Member Functions
 **********************************************************************
 + Set
 + OperatorOverload !=
 + CompareSurfs
 	 L CompareSurfs( SurfMin )
 	 L CompareSurfs ( int )
 + isValidSurfs
 **********************************************************************
 *
 **********************************************************************/



/**********************************************************************
 * Function_Name: Set
 * Return 		:
 * Comments 	:
 **********************************************************************/
int SurfMin::Set(const int iGroup, const int iFace, const int iEllipse )
{

	iGroupIdx = iGroup;
	iFaceIdx  = iFace;
	iEllipseIdx = iEllipse;

	return EXIT_SUCCESS;
}


/**********************************************************************
 * Function_Name: operator !=
 * Return 		:
 * Comments 	:
 **********************************************************************/
bool SurfMin::operator !=(const SurfMin& rhsSurf ) const
		{

	bool decision;

	decision  = CompareSurfs(rhsSurf);

	return !decision;
		}

/**********************************************************************
 * Function_Name: operator !=
 * Return 		:
 * Comments 	:
 **********************************************************************/
bool SurfMin::operator !=(const int CompareVal) const
{
	bool decision = ( *this == NULL );

	return !decision;
}

/**********************************************************************
 * Function_Name: operator ==
 * Return 		:
 * Comments 	:
 **********************************************************************/
bool SurfMin:: operator ==(const int CompareVal ) const
{

	bool decision = false;

	if( CompareVal == NULL )
	{
		decision = isValid( *this );
		return !decision;

	}

	return decision;
}

/**********************************************************************
 * Function_Name: CompareSurfs
 * Return 		:
 * Comments 	:
 **********************************************************************/
bool SurfMin::CompareSurfs(const SurfMin& rhsSurf) const
{
	bool decision = false;



	if( iGroupIdx == rhsSurf.iGroupIdx )
	{

		if( iFaceIdx == rhsSurf.iFaceIdx )
		{
			if( iEllipseIdx == rhsSurf.iEllipseIdx)
			{
				decision = true;
				return decision;
			}
			else
			{
				decision = false;
				return decision;
			}
		}
		else
		{
			decision =  false;
			return decision;
		}
	}
	else
	{
		decision = false;
		return decision;
	}




	return decision;
}

/**********************************************************************
 * Function_Name: CompareSurfs
 * Return 		:
 * Comments 	:
 **********************************************************************/
bool SurfMin::CompareSurfs(const int CompareIdx ) const
{
	bool decision = false;

	if( ( iGroupIdx == CompareIdx ) & ( iFaceIdx == CompareIdx ) & ( iEllipseIdx == CompareIdx ) )
	{
		decision = true;
		return decision;
	}

	return decision;

}


/**********************************************************************
 * Function_Name: isValidSurfs
 * Return 		:
 * Comments 	: checks if there was atleast any one valid intersection
 * 					this means either iGroupIdx or iFaceIdx != -1
 * 					or iEllipseIdx != -1
 **********************************************************************/
bool SurfMin::isValid(const SurfMin& rhsSurf ) const
{
	bool decision = false;

	bool Cmp_Minus1 = CompareSurfs( -1 );

	if( Cmp_Minus1 == true )
	{
		decision = false;
		return decision;
	}
	else
	{
		decision = true;
		return decision;
	}

	return decision;
}


/********************************************************************************************************************************************
 * Function_Name: SminType
 * Return 		:
 * Comments 	:
 ********************************************************************************************************************************************/
int SurfMin::Type() const
{
	if( ( iGroupIdx == -1 ) & (iFaceIdx == -1) & (iEllipseIdx != -1 ) )
	{
		return SMIN_POINT_ON_ELLIPSE;
	}
	else if( ( iGroupIdx != -1 ) & (iFaceIdx != -1) & (iEllipseIdx == -1 ) )
	{
		return SMIN_POINT_ON_FLAT_SURFACE;
	}

	return SMIN_UNINITIALIZED;
}


/**********************************************************************
 * Function_Name: Default Destructor
 * Return 		:
 * Comments 	:
 **********************************************************************/
SurfMin::~SurfMin() {
	// DONE Auto-generated destructor stub
}


/**********************************************************************
 * Function_Name: Operator <<
 * Return 		:
 * Comments 	:
 **********************************************************************/
std::ostream& operator<< ( std::ostream& out, const SurfMin Smin )
{
	out << "GroupIdx " 	<< Smin.iGroupIdx << endl;
	out << "FaceIds "  	<< Smin.iFaceIdx << endl;
	out << "EllipseIdx "<< Smin.iEllipseIdx << endl;
	out << "Tmin "		<< Smin.tMin << endl;

	return out;
}
