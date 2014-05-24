/*
 * Group.cpp
 *
 *  Created on: Sep 22, 2012
 *      Author: hrushi
 */

#include "Group.h"

/**********************************************************************
 * Function_Name: Default Constructor
 * Return 		:
 * Comments 	:
 **********************************************************************/
Group::Group()
{
	// DONE Auto-generated constructor stub

	name = "default";
	NumFaces = 0;

	for(int i = 0; i < 4; i++ )
	{
		for( int j = 0; j < 4; j++)
		{
			if( i == j )
			{
				T[i][j] = 1;
			}
			else
			{
				T[i][j] = 0;
			}
		}
	}

}

/**********************************************************************
 * Function_Name: Copy Constructor
 * Return 		:
 * Comments 	:
 **********************************************************************/
Group::Group( const Group& rhsGroup )
{

	AllocateGroup(rhsGroup);
	CopyGroup( rhsGroup );

}

/**********************************************************************
 * Function_Name: Operator =
 * Return 		:
 * Comments 	:
 **********************************************************************/
Group& Group::operator =(const Group& rhsGroup )
{

	AllocateGroup(rhsGroup);
	CopyGroup(rhsGroup );

	return *this;
}

/**********************************************************************
 * Function_Name: CopyGroup
 * Return 		:
 * Comments 	:
 **********************************************************************/
int Group::CopyGroup(const Group& rhsGroup )
{

	// Copy the Group Name
	name = rhsGroup.name;

	if( f.size() == rhsGroup.f.size() )
	{
		f.resize( rhsGroup.f.size() );

		for( unsigned int i = 0; i < rhsGroup.f.size(); i++ )
		{
			f.at(i) = rhsGroup.f.at(i);
		}
	}
	else
	{
		cerr << "Error Copying Group, RHS and LHS dimensions should be same";
	}

	if( UniqueVertices.size() == rhsGroup.UniqueVertices.size() )
	{
		std::copy(rhsGroup.UniqueVertices.begin(), rhsGroup.UniqueVertices.end(), UniqueVertices.begin() );
	}
	else
	{
		cerr << "Error Copying Group, RHS and LHS dimensions should be same";
	}


	//Copying Transformation matrix
	for( int i = 0; i < 4; i++ )
	{
		for( int j = 0; j < 4; j++ )
		{
			T[i][j] = rhsGroup.T[i][j];
		}
	}




	// Copy the field number of faces
	NumFaces = rhsGroup.NumFaces;

	return EXIT_SUCCESS;
}
/**********************************************************************
 * Function_Name: Allocator
 * Return 		:
 * Comments 	:
 **********************************************************************/
int Group::AllocateGroup(const Group & rhsGroup )
{

	/*
	// Public Variables
		string name;
		vector<Face> f; 	// Vector of all the Faces
		vector<int> UniqueVertices;
		double T[4][4]; // Transformation Matrix

	 */

	f.resize( rhsGroup.f.size() );
	UniqueVertices.resize( rhsGroup.UniqueVertices.size() );


	return EXIT_SUCCESS;
}

/**********************************************************************
 * Function_Name: Default Destructor
 * Return 		:
 * Comments 	:
 **********************************************************************/
Group::~Group()
{
	// DONE Auto-generated destructor stub
}



/**********************************************************************
 * Function_Name: AddNewFace
 * Return 		: Returns the index of the newly created face
 * Comments 	:
 **********************************************************************/
int Group::AddNewFace()
{
	int iCurrentFaceIdx = -1;

	Face TempFace;

	f.push_back(TempFace);
	NumFaces = f.size();

	iCurrentFaceIdx = NumFaces - 1;

	return iCurrentFaceIdx;
}


/**********************************************************************
 * Function_Name: GetTotalGroupVertices
 * Return 		: Total Number of verticies returned in the group
 * Comments 	:
 **********************************************************************/
int Group::GetTotalGroupVertices() const
{

	int TotalGroupVerticies = 0;
	// For Every Face
	for(unsigned i = 0; i < f.size(); i++ )
	{
		TotalGroupVerticies += f.at(i).Index2Vertex.size();
	}

	return TotalGroupVerticies;

}

/**********************************************************************
 * Function_Name: Populate Unique Verticies
 * Return 		: SUCCESS / FAILURE
 * Comments 	: Since multiple faces in a group can point to a same vertex
 * 				: Like corner of a cube is shared by three faces, we should
 * 				: not wite the same vertex thrice. This function will
 * 				: remove such repeates vertices
 **********************************************************************/
int Group::PopulateUniqueVertices()
{

	int temp;
	for( unsigned int iFace = 0; iFace < f.size(); iFace++ )
	{
		for( unsigned int iIndex = 0; iIndex < f.at(iFace).Index2Vertex.size(); iIndex++ )
		{
			temp = f.at( iFace ).Index2Vertex.at( iIndex );
			UniqueVertices.push_back( temp );
		}

	}

	vector<int>::iterator it;
	sort( UniqueVertices.begin(), UniqueVertices.end() );
	it = unique( UniqueVertices.begin(), UniqueVertices.end() );

	UniqueVertices.resize(it - UniqueVertices.begin() );

	return EXIT_SUCCESS;
}

/**********************************************************************
 * Function_Name: GetNumFaces
 * Return 		: Number of Faces in the group
 * Comments 	:
 **********************************************************************/
int Group::GetNumFaces() const
{
	return NumFaces;
}


/**********************************************************************
 * Function_Name: FaceCoplanarity
 * Return 		:
 * Comments 	: Checks the Coplanarity for all the faces in the group
 **********************************************************************/
int Group::FaceCheck( )
{
	for( unsigned int i = 0; i < f.size(); i++)
	{
		if( ! f.at( i ).isCoplanar() )
		{
			cerr << "The Face " << i << " is not Co-planar " << endl;
			throw ERR_NON_COPLANAR_FACES;
		}

		if(  !f.at(i).isCoLinear() )
		{
			cerr <<  "The Face " << i << " is Collinear " << endl;
			throw ERR_COLINEAR;
		}


		if( !f.at(i).isConvex() )
		{
			cerr << "The Face " << i << " is Non-Convex " << endl;
			throw ERR_CONVEX;
		}
	}

	return EXIT_SUCCESS;
}

/**********************************************************************
 * Function_Name: Translate
 * Return 		:
 * Comments 	: Multiples the Group Transformation Matrix by the
 * 				: Transformation matrix created over here.
 **********************************************************************/
int Group::Translate(double x, double y, double z)
{

	double Trnsl[4][4] = {{0}}; // This is the translation matrix

	// Initialize to identity
	for(int i = 0; i < 4; i++ )
	{
		for( int j = 0; j < 4; j++)
		{
			if( i == j )
			{
				Trnsl[i][j] = 1;
			}
			else
			{
				Trnsl[i][j] = 0;
			}
		}
	}

	Trnsl[0][3] = x;
	Trnsl[1][3] = y;
	Trnsl[2][3] = z;
	Trnsl[3][3] = 1;

	CopyMatrix(Trnsl, T );


	return EXIT_SUCCESS;
}


/**********************************************************************
 * Function_Name: Scales the group Vertices
 * Return 		:
 * Comments 	: Multiples the Group Transformation Matrix by the
 * 				: Transformation matrix created over here.
 **********************************************************************/
int Group::Scale(double x, double y, double z)
{

	double ScaleTransMat[4][4] = {{0}}; // This is the translation matrix

	// Initialize to identity
	for(int i = 0; i < 4; i++ )
	{
		for( int j = 0; j < 4; j++)
		{
			if( i == j )
			{
				ScaleTransMat[i][j] = 1;
			}
			else
			{
				ScaleTransMat[i][j] = 0;
			}
		}
	}

	ScaleTransMat[0][0] = x;
	ScaleTransMat[1][1] = y;
	ScaleTransMat[2][2] = z;
	ScaleTransMat[3][3] = 1;

	CopyMatrix(ScaleTransMat, T );

	return EXIT_SUCCESS;
}


/**********************************************************************
 * Function_Name: Arbit
 * Return 		:
 * Comments 	: Multiples the Group Transformation Matrix by the
 * 				: Transformation matrix created over here.
 **********************************************************************/
int Group::Arbit( const vector<double>& ArbitLine )
{
	double ArbitMat[4][4] = {{0}};

	for(int i = 0; i < 4; i++ )
	{
		for( int j = 0; j < 4; j++ )
		{
			ArbitMat[i][j] = ArbitLine.at(i * 4 + j);
		}
	}

	CopyMatrix(ArbitMat, T );

	return EXIT_SUCCESS;
}


/**********************************************************************
 * Function_Name: Rotate
 * Return 		:
 * Comments 	:
 **********************************************************************/
int Group::Rotate(double theta, VectorSpace w )
{

	double Rw[4][4] = {{0}};
	double RwT[4][4] = {{0}};
	double Temp[4][4] = {{0}};
	double R[4][4] = {{0}};

	// Get the matrix for making the w as the z axis. This will give
	// us the rotation matrix for the same
	RotAxis(Rw, w);

	Transpose(RwT, Rw );

	CheckRotationMat(Rw);

	double Ro[4][4] = {{0}};
	RotMatZ(Ro, theta);


	CheckRotationMat(Ro);

	MatrixMult(Temp, Ro, Rw );
	MatrixMult(R, RwT, Temp );

	CheckRotationMat(R);


	CopyMatrix(R, T );

	return EXIT_SUCCESS;
}




