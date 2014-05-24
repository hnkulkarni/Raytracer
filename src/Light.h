/*
 * Light.h
 *
 *  Created on: Nov 21, 2012
 *      Author: hrushi
 */

#ifndef LIGHT_H_
#define LIGHT_H_

#include "Includes.h"
#include "Vertex.h"
#include "Color.h"

#include "VectorSpace.h"

class Light
{
public:
	Light();
	Light( const Light& rhsLight);

	int CopyLight(const Light& rhsLight );
	int AllocateLight( const Light& rhsLight );
	Light& operator=( const Light& rhsLight );


	virtual ~Light();

	// Member Functions
	VectorSpace GetLightVector( const Vertex& Pt_in_Space ) const;

	// Member Variables
	Vertex Loc;
	Color RGB;
};


// Overloaded Operators
std::istream& operator >> ( std::istream& in, Light& NewLight );
std::ostream& operator << ( std::ostream& out, const Light& l);

#endif /* LIGHT_H_ */
