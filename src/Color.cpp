/*
 * Color.cpp
 *
 *  Created on: Oct 18, 2012
 *      Author: hrushi
 */

#include "Color.h"

/**********************************************************************
 * Function_Name: Default Constructor
 * Return 		:
 * Comments 	:
 **********************************************************************/
Color::Color() {
	// DONE Auto-generated constructor stub

	for(int i = 0; i < 3; i++)
	{
		RGB[i] = 0;
	}




}


/**********************************************************************
 * Function_Name: Constructor
 * Return 		:
 * Comments 	:
 **********************************************************************/
Color::Color(const unsigned int R, const unsigned int G, const unsigned int B)
{
	RGB[0] = R;
	RGB[1] = G;
	RGB[2] = B;


}
/**********************************************************************
 * Function_Name: Copy Constructor
 * Return 		:
 * Comments 	:
 **********************************************************************/
Color::Color( const Color& rhsColor )
{
	CopyColor(rhsColor);

}

/**********************************************************************
 * Function_Name: Overloading =
 * Return 		:
 * Comments 	: so that Color c1 = c2 works!!
 **********************************************************************/
Color& Color::operator =(const Color& rhsColor)
{
	CopyColor(rhsColor);
	return *this;
}

/**********************************************************************
 * Function_Name: Overloading +=
 * Return 		:
 * Comments 	: so that Color c1 += c2 works!!
 **********************************************************************/
Color& Color::operator += ( const Color& rhsColor)
				{

	RGB[0] += rhsColor.RGB[0];
	RGB[1] += rhsColor.RGB[1];
	RGB[2] += rhsColor.RGB[2];



	return *this;
				}
/**********************************************************************
 * Function_Name: Set
 * Return 		:
 * Comments 	:
 **********************************************************************/
int Color::Set(const unsigned int R, const unsigned int G, const unsigned int B)
{
	RGB[0] = R;
	RGB[1] = G;
	RGB[2] = B;

	return EXIT_SUCCESS;
}

/**********************************************************************
 * Function_Name: Set
 * Return 		:
 * Comments 	:
 **********************************************************************/
int Color::Set(const double *d )
{

	for( unsigned int i = 0; i < 3; i++ )
	{
		RGB[i] = d[i];
	}

	return EXIT_SUCCESS;
}
/**********************************************************************
 * Function_Name: CopyColor
 * Return 		:
 * Comments 	: Otherwise I have to write the same function again.
 * 					Repeating code is not a good idea.
 **********************************************************************/
int Color::CopyColor(const Color& rhsColor)
{
	for( int i = 0; i < 3; i++)
	{
		RGB[i] = rhsColor.RGB[i];
	}

	return EXIT_SUCCESS;
}
/**********************************************************************
 * Function_Name: Default Destructor
 * Return 		:
 * Comments 	:
 **********************************************************************/
Color::~Color() {
	// DONE Auto-generated destructor stub
}


/**********************************************************************
 * Function_Name: Overloading <<
 * Return 		:
 * Comments 	:
 **********************************************************************/
std::ostream& operator<< ( std::ostream& out, const Color& c )
{
	for( int i = 0; i < 3; i++)
	{
		out << c.RGB[i] << " ";
	}

	return out;
}


/**********************************************************************
 * Function_Name: Overloading /
 * Return 		:
 * Comments 	:
 **********************************************************************/
Color & operator/(Color& c, const double d)
{
	for(int i = 0; i < 3; i++)
	{
		c.RGB[i] = (double)c.RGB[i]/d;
	}
	return c;
}

/**********************************************************************
 * Function_Name: Overloading +
 * Return 		:
 * Comments 	:
 **********************************************************************/
Color Color::operator +(const Color& rhsColor)
{

	Color Result;

	for( unsigned int i = 0; i < 3; i++ )
	{
		Result.RGB[i] = RGB[i] + rhsColor.RGB[i];
	}

	return Result;
}


/**********************************************************************
 * Function_Name: Overloading *
 * Return 		:
 * Comments 	:
 **********************************************************************/
Color Color::operator *(const double Val  ) const
{
	Color Result;

	for( unsigned int i = 0; i < 3; i++ )
	{
		Result.RGB[i] = RGB[i] * Val;
	}

	return Result;
}
/**********************************************************************
 * Function_Name: Overloading >>
 * Return 		:
 * Comments 	:
 **********************************************************************/
std::istream& operator >> ( std::istream& in, Color & c )
{

	for( unsigned int i = 0; i < 3; i++ )
	{
		in >> c.RGB[i];
	}

	return in;
}


/**********************************************************************
 * Function_Name: Saturates
 * Return 		:
 * Comments 	: Saturats the pixel at this value
 * 					. If the pixel value is greater than the given value,
 * 					  it will round it off to the given value
 **********************************************************************/
Color Color::Saturate(const unsigned int Val)
{
	Color SaturatedColor;

	for( unsigned int i = 0; i < 3; i++ )
	{
		if( RGB[i] > Val )
		{
			SaturatedColor.RGB[i] = Val;
		}
		else
		{
			SaturatedColor.RGB[i] =  RGB[i];
		}
	}

	return SaturatedColor;
}
