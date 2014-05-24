/*
 * Face.h
 *
 *  Created on: Sep 22, 2012
 *      Author: hrushi
 */

#ifndef FACE_H_
#define FACE_H_

#include "Includes.h"

#include "VectorSpace.h"
#include "Vertex.h"
#include "Matrix.h"

class Face {

	int NumVertexInFace;

public:
	Face();
	virtual ~Face();
	Face( const Face& rhsFace ); // Copy Constructor

	int AllocateFaces( const Face& rhsFace );
	int CopyFaces( const Face& rhsFace );
	Face& operator=( const Face& rhsFace );

	//Public Functions
	int GetNumIndex2Vertex() const;
	int AddIndex2aVertex(int idx);

	bool isCoplanar( );
	bool isCoLinear( );
	bool isConvex( );

	int MakeFaceVectors( vector<Vertex> & v  );
	VectorSpace GetSurfaceNormal( );

	double Intersection( const VectorSpace& Ray) const; // Check interesection of this ray with the face;

	//Public Variable
	vector<int> Index2Vertex;
	VectorSpace SurFaceNormal;
	vector<VectorSpace> FaceVectors;
	string MtlName;
};

#endif /* FACE_H_ */
