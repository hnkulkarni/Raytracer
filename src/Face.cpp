/*
 * Face.cpp
 *
 *  Created on: Sep 22, 2012
 *      Author: hrushi
 */

#include "Face.h"

/**********************************************************************
 * Function_Name: Default Constructor
 * Return 		:
 * Comments 	:
 **********************************************************************/
Face::Face() {
	// DONE Auto-generated constructor stub

	NumVertexInFace = -1;

}

/**********************************************************************
 * Function_Name: Copy Constructor
 * Return 		:
 * Comments 	:
 **********************************************************************/
Face::Face(const Face& rhsFace )
{
	AllocateFaces(rhsFace );
	CopyFaces(rhsFace );

}

/**********************************************************************
 * Function_Name: Operator =
 * Return 		:
 * Comments 	:
 **********************************************************************/
Face& Face::operator =(const Face& rhsFace )
{

	AllocateFaces(rhsFace);
	CopyFaces(rhsFace);

	return *this;
}


/**********************************************************************
 * Function_Name: Copy Faces
 * Return 		:
 * Comments 	:
 **********************************************************************/
int Face::CopyFaces(const Face& rhsFace )
{
	if( Index2Vertex.size() == rhsFace.Index2Vertex.size() )
	{
		std::copy(rhsFace.Index2Vertex.begin(), rhsFace.Index2Vertex.end(), Index2Vertex.begin() );
	}
	else
	{
		cerr << "The LHS and RHS Faces should be of the same dimension" << endl;
		cerr << "Please use Allocate Faces First" << endl;
	}

	if( FaceVectors.size() == rhsFace.FaceVectors.size() )
	{
		for(unsigned int i = 0; i < rhsFace.FaceVectors.size(); i++ )
		{
			FaceVectors.at(i) = rhsFace.FaceVectors.at(i);
		}
	}

	SurFaceNormal	= rhsFace.SurFaceNormal;

	MtlName 	 	= rhsFace.MtlName;

	return EXIT_SUCCESS;
}


/**********************************************************************
 * Function_Name: Allocate Faces
 * Return 		:
 * Comments 	:
 **********************************************************************/
int Face::AllocateFaces(const Face& rhsFace )
{

	/*
	 * 	vector<int> Index2Vertex;
	VectorSpace SurFaceNormal;
	vector<VectorSpace> FaceVectors;
	 */
	Index2Vertex.resize(  rhsFace.Index2Vertex.size() );
	FaceVectors.resize( rhsFace.FaceVectors.size() );

	return EXIT_SUCCESS;
}

/**********************************************************************
 * Function_Name: Default Destructor
 * Return 		:
 * Comments 	:
 **********************************************************************/
Face::~Face() {
	// DONE Auto-generated destructor stub
}


/**********************************************************************
 * Function_Name: GetNumIndex2Vertex
 * Return 		: Number of index to vertex
 * Comments 	:
 **********************************************************************/
int Face::GetNumIndex2Vertex() const
{
	return NumVertexInFace;
}


/**********************************************************************
 * Function_Name: AddIndex2aVertex
 * Return 		: int
 * Comments 	: Returns the index to the latest added index of Index2aVector
 **********************************************************************/
int Face::AddIndex2aVertex(int idx)
{
	int iCurrentIndex2aVector = -1;

	Index2Vertex.push_back(idx);
	NumVertexInFace = Index2Vertex.size();

	iCurrentIndex2aVector = NumVertexInFace - 1;

	return iCurrentIndex2aVector;

}

/**********************************************************************
 * Function_Name: isCoplanar
 * Return 		:
 * Comments 	: Checks if the face is coplanar. The list of all the
 * 				: is required to be passed because we need to index
 * 				: into them.
 **********************************************************************/
bool Face::isCoplanar(  )
{

	double DotProd = 0;
	double absDotProd = 0;


	for( unsigned int i = 0; i < Index2Vertex.size(); i++ )
	{

		DotProd = SurFaceNormal.Dot( FaceVectors.at( i ) );

		absDotProd =  sqrt( DotProd * DotProd );
		if( absDotProd >= SOME_SMALL_VALUE )
		{
			cerr << "Face Vertex are Non Coplanar " << endl;
			throw ERR_NON_COPLANAR_FACES;
		}

	}

	return TRUE;
}
/**********************************************************************
 * Function_Name: Make Face Vectors
 * Return 		:
 * Comments 	: Creates Unit Vectors between every side of the face
 **********************************************************************/
int Face::MakeFaceVectors( vector<Vertex> & v  )
{

	unsigned int iCurrent = 0;
	unsigned int iNext = 0;

	// Allocate a Vector space for all the slides
	FaceVectors.resize( Index2Vertex.size() );

	for(unsigned int i = 0; i < Index2Vertex.size(); i++)
	{
		iCurrent = Index2Vertex.at(i) - 1; // OBJ Files indexes start with 1

		if( i == Index2Vertex.size() - 1)
		{
			iNext = Index2Vertex.at(0) - 1; // OBJ Files indexes start with 1
		}
		else
		{
			iNext = Index2Vertex.at( i + 1 )  - 1; // OBJ Files indexes start with 1
		}

		try
		{
			FaceVectors.at(i).CreateVector( v.at(iCurrent).arr , v.at(iNext).arr );
			FaceVectors.at(i).DoNormalization();
		}
		catch(out_of_range & oor)
		{
			cerr << "Out of Range Vector: " << oor.what() << endl;
			throw ERR_VECTOR_OUT_OF_RANGE;
		}

	}

	return EXIT_SUCCESS;

}

/**********************************************************************
 * Function_Name: Find Surface Normal
 * Return 		:
 * Comments 	:
 **********************************************************************/
VectorSpace Face::GetSurfaceNormal()
{

	SurFaceNormal = FaceVectors.at(1);
	SurFaceNormal.CrossProduct( FaceVectors.at(0) );
	return SurFaceNormal;

}

/**********************************************************************
 * Function_Name: isCoLinear
 * Return 		:
 * Comments 	: Vertices of the Face Should be Non-Colinear
 **********************************************************************/
bool Face::isCoLinear( )
{

	Matrix Mat;

	VectorSpace vCross;

	double Mag = 0;

	for( unsigned int i = 1; i <  Index2Vertex.size() ; i++ )
	{

		vCross = FaceVectors.at( i - 1);
		vCross.CrossProduct(  FaceVectors.at( i ) );

		Mag = vCross.Magnitude();

		if( Mag < SOME_SMALL_VALUE )
		{
			cerr << "Face Verticies are Colinear " << endl;
			throw ERR_COLINEAR;
		}

	}

	return TRUE;
}



/**********************************************************************
 * Function_Name: isConvex
 * Return 		: TRUE - CONVEX, FALSE - NON_CONVEX
 * Comments 	: Checks if the given face is Convex.
 **********************************************************************/
bool Face::isConvex()
{

	double DotProd = 1;


	if( Index2Vertex.size() > 3 )
	{
		vector<VectorSpace> vsCross(Index2Vertex.size() );

		for( unsigned int i = 0; i <  Index2Vertex.size() ; i++ )
		{
			if( i == Index2Vertex.size() - 1)
			{
				vsCross.at(i) = FaceVectors.at(i);
				vsCross.at(i).CrossProduct( FaceVectors.at(0) );
			}
			else
			{
				vsCross.at(i) = FaceVectors.at(i);
				vsCross.at(i).CrossProduct( FaceVectors.at(i+1) );
			}
		}

		for( unsigned int i = 0; i <  Index2Vertex.size() ; i++ )
		{

			if( i == Index2Vertex.size() - 1)
			{

				DotProd = vsCross.at(i).Dot( vsCross.at(0) );
			}
			else
			{
				DotProd = vsCross.at(i).Dot( vsCross.at(i+1) );
			}

			if( DotProd < 0 )
			{
				cerr << "Face is non-convex " << endl;
				exit( ERR_CONVEX );
			}

		}

	}


	return TRUE;
}




