/*
 * Color.h
 *
 *  Created on: Oct 18, 2012
 *      Author: hrushi
 */

#ifndef COLOR_H_
#define COLOR_H_


#include "Includes.h"


class Color {

protected:


public:
	Color();
	virtual ~Color();

	Color(const unsigned int R, const unsigned int G, const unsigned int B);
	Color(const Color& rhsColor);// Copy Constructor
	Color& operator=(const Color& rhsColor); // Overloading =

	Color& operator +=( const Color& rhsColor ); // Overloading +=
	Color operator+( const Color& rhsColor );
	Color operator*( const double Val ) const;

	int CopyColor(const Color& rhsColor );
	int Set(const unsigned int R, const unsigned int G, const unsigned int B);
	int Set( const double* d);
	Color Saturate( const unsigned int Val );

	unsigned int RGB[3];

};

//Overloading operators
std::ostream& operator<< ( std::ostream& out, const Color& c );
Color & operator/(Color& c, const double d);
std::istream& operator >>( std::istream& in, Color& c);
#endif /* COLOR_H_ */
