/*
 * Group.h
 *
 *  Created on: Sep 22, 2012
 *      Author: hrushi
 */

#ifndef GROUP_H_
#define GROUP_H_

#include "Includes.h"
#include "Transformation.h"
#include "Vertex.h"
#include "Face.h"
#include "VectorSpace.h"

class Group: public Transformation
{
private:

public:
	Group();
	virtual ~Group();
	Group(const Group& rhsGroup); // Copy Constructor

	int AllocateGroup(const Group& rhsGroup ); // Allocator
	int CopyGroup( const Group& rhsGroup ); // Copy the content
	Group& operator=( const Group& rhsGroup ); // Operator =

	// Public Functions
	int GetTotalGroupVertices() const;
	int AddNewFace();
	int GetNumFaces() const;
	int PopulateUniqueVertices();

	int FaceCheck( );
	int Translate( double x, double y, double z);
	int Scale( double x, double y, double z);
	int Arbit( const vector<double>& ArbitLine );
	int Rotate(double theta, VectorSpace w );

	// Public Variables
	string name;
	vector<Face> f; 	// Vector of all the Faces
	vector<int> UniqueVertices;
	double T[4][4]; // Transformation Matrix
	int NumFaces;


};

#endif /* GROUP_H_ */
