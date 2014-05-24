/*
 * Material.h
 *
 *  Created on: Nov 17, 2012
 *      Author: hrushi
 */

#ifndef MATERIAL_H_
#define MATERIAL_H_

#include "Includes.h"

class Material {
public:
	Material();
	virtual ~Material();

	Material( const Material& rhsMaterial); // Copy Constructor

	int CopyMaterial(const Material& rhsMaterial); // Copy the Material
	Material& operator=( const Material& rhsMaterial); // Equality Operator

	string MaterialName;
	double Ka[3]; // Abmient Reflection
	double Kd[3]; // Diffused Reflection
	double Ks[3]; // Specular Reflection
	double Ns;	// Alpha
	double d;	// Dissolve, some applications use d, others use Tr
	double Tr;  // hence the obj spec uses both d, and Tr.
	double N1; // Refractive Index of the object



};

std::istream& operator>>( std::istream& in, Material& Mat);
std::ostream& operator<< ( std::ostream& out, Material& Mat);

#endif /* MATERIAL_H_ */
