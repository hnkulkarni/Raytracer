/*
 * Light.cpp
 *
 *  Created on: Nov 21, 2012
 *      Author: hrushi
 */

#include "Light.h"


/**********************************************************************
 * Function_Name: Default Constructor
 * Return 		:
 * Comments 	:
 **********************************************************************/
Light::Light()
{



}


/**********************************************************************
 * Function_Name: Copy Constructor
 * Return 		:
 * Comments 	:
 **********************************************************************/
Light::Light(const Light& rhsLight )
{

	AllocateLight(rhsLight);
	CopyLight( rhsLight );

}
/**********************************************************************
 * Function_Name: Operator =
 * Return 		:
 * Comments 	:
 **********************************************************************/
Light& Light::operator =(const Light& rhsLight )
{
	AllocateLight(rhsLight);
	CopyLight(rhsLight);

	return *this;
}


/**********************************************************************
 * Function_Name: CopyLight
 * Return 		:
 * Comments 	:
 **********************************************************************/
int Light::CopyLight(const Light& rhsLight )
{
	Loc = rhsLight.Loc;
	RGB = rhsLight.RGB;

	return EXIT_SUCCESS;
}



/**********************************************************************
 * Function_Name: AllocateLight
 * Return 		:
 * Comments 	:
 **********************************************************************/
int Light::AllocateLight(const Light& rhsLight )
{

	return EXIT_SUCCESS;
}




/**********************************************************************
 * Function_Name: Operator >>
 * Return 		:
 * Comments 	:
 **********************************************************************/
std::istream& operator >> ( std::istream& in, Light& NewLight )
{

	in.exceptions(std::istream::badbit | std::istream::failbit );

	try
	{
		for( unsigned int i = 0; i < 4; i++ )
		{
			in >> NewLight.Loc.arr[i];
		}

		in >> NewLight.RGB;

	}
	catch( std::istream::failure &e)
	{
		if( !in.eof() )
		{
			cout << "Error Reading Light Source " << endl;
			exit(ERR_READING_LIGHT_SRC);
		}

	}

	return in;
}


/**********************************************************************
 * Function_Name: Operator <<
 * Return 		:
 * Comments 	:
 **********************************************************************/
std::ostream& operator << ( std::ostream& out, const Light& l)
{

	out << "Location " ;
	out << l.Loc;

	out << "Color " ;
	out << l.RGB;

	return out;
}


/**********************************************************************
 * Function_Name: GetLightVector
 * Return 		:
 * Comments 	:	Returns the unit length light vector starting from the point
 * 					in space, towards the light source;
 **********************************************************************/
VectorSpace Light::GetLightVector( const Vertex& Pt_in_Space ) const
{
	VectorSpace LightVector;

	LightVector.CreateVector( Pt_in_Space.arr, Loc.arr );

	return LightVector;
}


/**********************************************************************
 * Function_Name: Default Destructor
 * Return 		:
 * Comments 	:
 **********************************************************************/
Light::~Light()
{
	// DONE Auto-generated destructor stub
}

