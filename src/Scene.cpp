/*
 * Scene.cpp
 *
 *  Created on: Sep 22, 2012
 *      Author: hrushi
 */

#include "Scene.h"

/**********************************************************************
 * Function_Name: Default Constructor
 * Return 		:
 * Comments 	:
 **********************************************************************/
Scene::Scene()
{

	NumGroups = 0;
	NumVertices = 0;

}


/**********************************************************************
 * Function_Name: Copy Constructor
 * Return 		:
 * Comments 	:
 **********************************************************************/
Scene::Scene(const Scene& rhsScene )
{

	NumVertices = rhsScene.NumVertices;
	NumGroups = rhsScene.NumGroups;

	Allocate(rhsScene);
	CopyScene(rhsScene);

}

/**********************************************************************
 * Function_Name: CopyScene
 * Return 		:
 * Comments 	: Copies the data from the scene
 **********************************************************************/
int Scene::CopyScene(const Scene& rhsScene )
{

	// Copy All the Groups
	if( g.size() == rhsScene.g.size() )
	{
		g.resize( rhsScene.g.size() );

		for( unsigned int i = 0; i < rhsScene.g.size(); i++ )
		{
			g.at(i) = rhsScene.g.at(i);
		}

	}
	else
	{
		cerr << "LHS Scene Size not equal to the RHS Scene " << endl;
		cerr << "Use Allocate Function first" << endl;
	}


	// Copy All the Vertices
	if( v.size() == rhsScene.v.size() )
	{
		v.resize( rhsScene.v.size() );

		for( unsigned int i = 0; i < rhsScene.v.size(); i++ )
		{
			v.at(i) = rhsScene.v.at(i);
		}
	}
	else
	{
		cerr << "LHS Vertices Size not equal to that of RHS Scene " << endl;
		cerr << "Use Allocate Function first" << endl;
	}


	// Copy All the Cameras
	if( c.size() == rhsScene.c.size() )
	{
		for( unsigned int i = 0; i < rhsScene.c.size(); i++ )
		{
			c.at(i) = rhsScene.c.at(i);
		}
	}
	else
	{
		cerr << "LHS Camera Size not equal to the RHS Scene" << endl;
		cerr << "Use Allocate Function First" << endl;
		exit(ERR_ALLOC);
	}

	// Copy Ellipse
	if( e.size() == rhsScene.e.size() )
	{
		for( unsigned int i = 0; i < rhsScene.e.size(); i++ )
		{
			e.at(i) = rhsScene.e.at(i);
		}
	}
	else
	{
		cerr << "LHS and RHS number of ellipse are close " << endl;
		exit(ERR_ALLOC);
	}

	// Copy the Light Sources
	if( lt.size() == rhsScene.lt.size() )
	{
		for( unsigned int i = 0; i < rhsScene.lt.size(); i++ )
		{
			lt.at(i) = rhsScene.lt.at(i);
		}
	}
	else
	{
		cout << "LHS and RHS number of Light Sources do not match" << endl;
		exit( ERR_ALLOC );
	}


	for(unsigned int i = 0; i < rhsScene.ListMtls.size(); i++)
	{
		ListMtls.at(i) = rhsScene.ListMtls.at(i);
	}

	// Copy all the Materials
	MaterialMap = rhsScene.MaterialMap;

	// Copy the Number of groups and vertices.
	NumGroups = rhsScene.NumGroups;
	NumVertices = rhsScene.NumVertices;


	return EXIT_SUCCESS;
}

/**********************************************************************
 * Function_Name: Allocate
 * Return 		:
 * Comments 	: Allocates data equal to the data to be copied. Used in
 * 				: the Assignment Operator and the copy constructor;
 * 				: Data to be copied should be passed as an argument to the
 * 				: function.
 **********************************************************************/
int Scene::Allocate(const Scene& rhsScene)
{
	g.resize( rhsScene.g.size() );
	v.resize( rhsScene.v.size() );
	c.resize( rhsScene.c.size() );
	e.resize( rhsScene.e.size() );
	lt.resize( rhsScene.lt.size() );
	ListMtls.resize( rhsScene.ListMtls.size() );

	return EXIT_SUCCESS;
}

/**********************************************************************
 * Function_Name: Assignment Operator
 * Return 		:
 * Comments 	:
 **********************************************************************/
Scene& Scene::operator= ( const Scene& rhsScene )
{
	NumVertices = rhsScene.NumVertices;
	NumGroups = rhsScene.NumGroups;

	Allocate(rhsScene);
	CopyScene(rhsScene);

	return *this;

}
/**********************************************************************
 * Function_Name: Default Destructor
 * Return 		:
 * Comments 	:
 **********************************************************************/
Scene::~Scene() {
	// DONE Auto-generated destructor stub
}

/**********************************************************************
 * Function_Name: Add New Group
 * Return 		: Index of the added group
 * Comments 	: Adds a new default group in the scene.
 **********************************************************************/
int Scene::AddNewGroup()
{
	return AddNewGroup("default");

}

/**********************************************************************
 * Function_Name: AddNewGroup
 * Return 		: Index of the added group
 * Comments 	: Adds group with the given name
 **********************************************************************/
int Scene::AddNewGroup( string name )
{

	Group TempGroup;

	g.push_back(TempGroup);

	NumGroups = g.size();

	g.at( NumGroups - 1 ).name = name;

	int GroupIndex = NumGroups - 1;

	return GroupIndex ;
}


/**********************************************************************
 * Function_Name: ifGroupExist
 * Return 		: int
 * Comments 	: Returns the index of an already existing group, in the scene;
 * 				: -1 No Such Group Found
 * 				: <n> index to the name of the group if already exist
 **********************************************************************/
int Scene::ifGroupExist(string name)
{
	int iRet = 0;

	bool found = false;

	if( NumGroups == 0 )
	{
		return NO_SUCH_GROUP;
	}
	else
	{
		for(int i = 0; i < NumGroups; i++ )
		{
			if( g.at(i).name.compare( name ) == 0 )
			{
				cout << "Group With the same name found" << endl;
				cout << "Group " << i << " : " << g.at(i).name << endl;
				cout << "New Group Name " << name << endl;

				found = true;

				return i;
			} // if for string compare

		} // for - number of groups

		// if no such group was found
		if( !found )
		{
			return NO_SUCH_GROUP;
		}
	}

	return iRet;
}

/**********************************************************************
 * Function_Name: MakeGroupIdxUnique
 * Return 		: SUCCESS / FAILURE
 * Comments 	: Iterates through all the faceindex in all the groups
 * 				: and populates the list of all the unique elements.
 * 				: This is uses for Writing the file.
 **********************************************************************/
int Scene::MakeGroupIdxUnique()
{

	for( unsigned int i = 0; i < g.size(); i++ )
	{
		g.at(i).PopulateUniqueVertices();
	}

	return EXIT_SUCCESS;
}
/**********************************************************************
 * Function_Name: Print Scene Parameters
 * Return 		:
 * Comments 	:
 **********************************************************************/
int Scene::PrintSceneParams()
{


	cout << endl;
	cout << FEW_STARS << " Printing Group Specific Scene Information " << FEW_STARS << endl;

	for(unsigned int i = 0; i < g.size(); i++ )
	{
		cout << "Group # \t : " 	 << i << endl;
		cout << "Group Name \t : " 	 << g.at(i).name << endl;
		cout << "Num Faces  \t : " 	 << g.at(i).f.size() << endl;
		cout << "Num Vertices \t : " << g.at(i).GetTotalGroupVertices() << endl;
		cout << endl;
	}

	cout << FEW_STARS << " Printing Common Scene Information " << FEW_STARS << endl;

	cout << "General Scene Props " << endl;
	cout << "Total Vertices Read " << v.size() << endl;
	cout << "Num Cameras \t  : " << c.size() << endl;
	cout << "Num Ellipse \t  : " << e.size() << endl;
	cout << "Num Materials\t : " << MaterialMap.size() << endl;

	cout << STARS << endl;

	return EXIT_SUCCESS;
}

/**********************************************************************
 * Function_Name: FindGroup
 * Return 		: index
 * Comments 	: Returns the index of the group with the same name
 **********************************************************************/
int Scene::FindGroup(string name)
{
	unsigned int iGrpIdx = 0;

	for( iGrpIdx = 0; iGrpIdx < g.size(); iGrpIdx ++)
	{

		if( g.at(iGrpIdx).name.compare(name) == 0 )
		{
			return iGrpIdx;
		}

	}

	if( iGrpIdx == g.size() )
	{
		throw ERR_GRP_NOT_FOUND;
	}

	return iGrpIdx;

}

/**********************************************************************
 * Function_Name: FindCam
 * Return 		: index
 * Comments 	: Returns the index of the camera with the same name
 **********************************************************************/
int Scene::FindCam(string name)
{

	unsigned int iCamIndx = 0;

	for( iCamIndx = 0; iCamIndx < c.size(); iCamIndx++ )
	{
		if( c.at(iCamIndx).CamName.compare(name) == 0)
		{
			return iCamIndx;
		}
	}

	if( iCamIndx == c.size())
	{
		cerr << "Camera Not Found" << endl;
		exit( ERR_CAM_NOT_FOUND );
	}

	return iCamIndx;

}

/**********************************************************************
 * Function_Name: GetNumVertices
 * Return 		: Number of vertices in the group
 * Comments 	:
 **********************************************************************/
int Scene::GetNumVertices() const
{
	return NumVertices;
}


/**********************************************************************
 * Function_Name: Add new Vertex
 * Return 		: Returns the index to the newly added vertex
 * Comments 	: Adds a new vertex
 **********************************************************************/
int Scene::AddNewVertex(double x, double y, double z, double scale)
{

	Vertex TempVertex;
	v.push_back(TempVertex);


	NumVertices = v.size();
	int iCurrentVertex = NumVertices - 1;


	v.at( iCurrentVertex ).Set(x, y, z, scale );
	return iCurrentVertex;

}


/**********************************************************************
 * Function_Name: Check
 * Return 		: Success / Failure
 * Comments 	: Check if the given scene is correct
 * 				: 1. Face with more than 3 Vertices
 *
 **********************************************************************/
int Scene::Check()
{

	for( unsigned int ig = 0; ig < g.size(); ig++)
	{
		try
		{
			g.at(ig).FaceCheck();
		}
		catch( int n )
		{
			switch(n)
			{

			case ERR_NON_COPLANAR_FACES:
				cerr << "NON-CO-PLANAR Faces " << endl;
				throw ERR_NON_COPLANAR_FACES;
				break;

			case ERR_COLINEAR:
				cerr << "COLINEAR Faces " << endl;
				throw ERR_COLINEAR;
				break;

			case ERR_CONVEX:
				cerr << "Non Convex Faces " << endl;
				throw ERR_CONVEX;
				break;
			}

		}
	}


	// Check for shared vertices
	try
	{
		SharedVerticies();
	}
	catch( int n )
	{
		switch(n)
		{
		case ERR_SHARED_VERTEX:
			cerr << "Shared Vertex Error " << endl;
			throw ERR_SHARED_VERTEX;
			break;
		}
	}
	return EXIT_SUCCESS;
}


/**********************************************************************
 * Function_Name: Shared Vertices
 * Return 		:
 * Comments 	:
 **********************************************************************/
int Scene::SharedVerticies()
{


	for( unsigned int i = 0 ; i < g.size(); i++ )
	{
		g.at(i).PopulateUniqueVertices();
	}

	// Check for shared Vertices
	for(unsigned int i = 0; i < g.size(); i++ )
	{
		for(unsigned int j = 0; j < g.size(); j++ )
		{
			if(i != j )
			{
				for( unsigned int k = 0; k < g.at(j).UniqueVertices.size(); k++ )
				{
					if( binary_search(g.at(i).UniqueVertices.begin(), g.at(i).UniqueVertices.end(), g.at(j).UniqueVertices.at(k)) )
					{
						cerr << "Found Repeated Vertex " << endl;
						cerr << "Shared with Group " << g.at(i).name << " and " << g.at(j).name << endl;
						throw ERR_SHARED_VERTEX;
					}
				} //For - Every Element in the Group
			} // If the target group not equal to the search group
		} // For - Every Search Group Vertex
	} // For - Every Target Group

	return EXIT_SUCCESS;
}

/**********************************************************************
 * Function_Name: Translate
 * Return 		:
 * Comments 	:
 **********************************************************************/
int Scene::Translate(string grp_name, double x, double y, double z)
{

	int GrpIndx = FindGroup(grp_name);

	g.at(GrpIndx).Translate(x, y, z);

	return EXIT_SUCCESS;
}


/**********************************************************************
 * Function_Name: Scale
 * Return 		:
 * Comments 	:
 **********************************************************************/
int Scene::Scale(string grp_name, double x, double y, double z)
{

	int GrpIndx = FindGroup(grp_name);

	g.at(GrpIndx).Scale(x, y, z);

	return EXIT_SUCCESS;
}


/**********************************************************************
 * Function_Name: Arbit
 * Return 		:
 * Comments 	:
 **********************************************************************/
int Scene::Arbit(string grp_name, const vector<double>& ArbitTranLine )
{
	int GrpIndx = FindGroup(grp_name);

	g.at(GrpIndx).Arbit(ArbitTranLine);

	return EXIT_SUCCESS;
}
/**********************************************************************
 * Function_Name: Tr2Point
 * Return 		:
 * Comments 	: Operates the Transformation Matrix from every group
 * 				: on all the verticies in the group.
 **********************************************************************/
int Scene::TrMat2Point()
{

	int unqVIdx = 0;
	Matrix Mat;

	for(unsigned int i = 0; i < g.size(); i++ )
	{

		for( unsigned int j = 0; j < g.at(i).UniqueVertices.size(); j++ )
		{
			unqVIdx = g.at(i).UniqueVertices.at(j) - 1;

			Mat.MatOnPt( g.at(i).T, v.at(unqVIdx).arr );

			if( v.at(unqVIdx).arr[3] > 1 )
			{
				// If the ouput point is
				// has a scale of more than 1, then divide it;
				for( int k = 0; k < 4; k++)
				{
					v.at(unqVIdx).arr[k] = v.at(unqVIdx).arr[k]/v.at(unqVIdx).arr[SCALE];
				}
			}

		}
	}

	return EXIT_SUCCESS;
}


/**********************************************************************
 * Function_Name: Rotate
 * Return 		:
 * Comments 	:
 **********************************************************************/
int Scene::Rotate( string grp_name, double theta, VectorSpace w )
{

	int GrpIndx = FindGroup(grp_name);

	g.at(GrpIndx).Rotate(theta, w);

	return EXIT_SUCCESS;
}

/**********************************************************************
 * Function_Name: AddNew Camera
 * Return 		:
 * Comments 	: Takes the issstreing and adds it to the camera
 **********************************************************************/
int Scene::AddNewCamera(istringstream& iss_line)
{

	Camera TempCam;
	c.push_back(TempCam);

	int iNumCameras = c.size();

	try
	{
		iss_line >> c.at(iNumCameras - 1);// Load the camera placed on the top of the vector space.
	}
	catch(int n)
	{
		if(n == ERR_ERROR_READING_VECTOR)
		{
			cerr << "Cannot read Camera " << endl;
			exit( ERR_CANNOT_READ_CAM );
		}
	}

	return EXIT_SUCCESS;
}


/**********************************************************************
 * Function_Name: PrintAllMtls
 * Return 		:
 * Comments 	:
 **********************************************************************/
int Scene::PrintAllMtls()
{

	map<string, Material>::const_iterator end = MaterialMap.end();

	for( map<string, Material>::const_iterator it = MaterialMap.begin(); it!=end; ++it)
	{
		cout << "Who(key = first) " << it->first;
		cout << "Score(key = second) " << MaterialMap[ it->first ];
	}
	return EXIT_SUCCESS;
}


/**********************************************************************
 * Function_Name: PrintSmin
 * Return 		:
 * Comments 	:
 **********************************************************************/
int Scene::PrintSminScene(const SurfMin& Smin ) const
{
	cout << STARS << endl;

	cout << "Group Name ";
	if( Smin.iGroupIdx > -1 )
	{
		cout << g.at( Smin.iGroupIdx ).name << endl;
	}
	else
	{
		cout << "NONE " << endl;
	}

	cout << "Face Index ";
	if( Smin.iFaceIdx > -1 )
	{
		cout << Smin.iFaceIdx << endl;
	}
	else
	{
		cout << "NONE " << endl;
	}

	cout << "Ellipse Index ";
	if( Smin.iEllipseIdx > -1 )
	{
		cout << Smin.iEllipseIdx  << endl;
	}
	else
	{
		cout << "NONE " << endl;
	}

	cout << STARS << endl;

	return EXIT_SUCCESS;
}

/********************************************************************************************************************************************
 * Function_Name: GetSurfaceNormal
 * Return 		:
 * Comments 	:
 ********************************************************************************************************************************************/
VectorSpace Scene::GetSurfaceNormal(const Vertex& Pt, const SurfMin& Smin) const
{

	VectorSpace SurfaceNormal;

	if( Smin.Type() == SMIN_POINT_ON_ELLIPSE)
	{
		SurfaceNormal = e.at( Smin.iEllipseIdx ).GetSurfaceNormal( Pt );
	}
	else
	{
		SurfaceNormal =  g.at(Smin.iGroupIdx).f.at( Smin.iFaceIdx ).SurFaceNormal;

	}

	return SurfaceNormal;
}


/********************************************************************************************************************************************
 * Function_Name: Intersectinon
 * Return 		:
 * Comments 	:
 ********************************************************************************************************************************************/
SurfMin Scene::Intersection(const VectorSpace& Ray, const Vertex& RayOrigin) const
{

	SurfMin Smin;
	double t = -1;           // t - value after intersection


	// For Standard Group
	for(unsigned int iGroup = 0; iGroup < g.size(); iGroup++ )
	{
		for( unsigned int iFace = 0; iFace < g.at(iGroup).f.size(); iFace++ )
		{

			t = GroupFaceIntersection(iGroup, iFace, Ray, RayOrigin);

			if( ( t > 0 ) &&  ( t < Smin.tMin ))
			{
				Smin.tMin = t;

				Smin.Set(iGroup, iFace, -1);
			}
		}
	}



	// For New Ellipse
	for( unsigned int iEllipse = 0; iEllipse < e.size(); iEllipse++ )
	{
		t = e.at( iEllipse ).Intersection( RayOrigin, Ray);

		if( t > -1)
		{
			if( ( t > 0 ) &&  ( t < Smin.tMin ))
			{
				Smin.tMin = t;

				Smin.Set( -1, -1, iEllipse);
			}
		}
	}

	return Smin;
}
/**********************************************************************
 * Function_Name: GroupFaceIntersection
 * Return 		:
 * Comments 	: 	Tells if the given ray, starting at the given point
 * 					if it intersects the given face from the given group
 * 					Returns -1 if no intersection found, else returns the
 * 					t value
 **********************************************************************/
double Scene::GroupFaceIntersection(const unsigned int iGroupIdx, const unsigned int iFaceIdx, const VectorSpace& Ray, const Vertex& RayOrigin ) const
{
	Vertex A, B, C, LA;

	unsigned int iTriangleA, iTriangleB, iTriangleC;

	iTriangleA = g.at(iGroupIdx).f.at(iFaceIdx).Index2Vertex.at(0) -1;
	iTriangleB = g.at(iGroupIdx).f.at(iFaceIdx).Index2Vertex.at(0 + 1) -1;
	iTriangleC = g.at(iGroupIdx).f.at(iFaceIdx).Index2Vertex.at(0 + 2) -1;

	if(CRITICAL_DEBUG)
	{
		cout << "Index to Vertices are " << iTriangleA << " " << iTriangleB << " " << iTriangleC << endl;
	}

	A = v.at(iTriangleA);

	if(CRITICAL_DEBUG)
	{
		cout << "A " << A;
	}

	B = v.at(iTriangleB);

	if(CRITICAL_DEBUG)
	{
		cout << "B " << B;
	}

	C = v.at(iTriangleC);

	if(CRITICAL_DEBUG)
	{
		cout << "C " << C;
	}

	double beta, gamma, t;
	//Vertex FocalPt = c.at(iCamIdx).GetFocalPoint();

	if(CRITICAL_DEBUG)
	{
		cout << "RayOrigin" << RayOrigin << endl;
	}

	LaPack(A, B, C, Ray,RayOrigin, beta, gamma, t );

	if(CRITICAL_DEBUG)
	{
		cout << "Beta " <<  beta << endl;
		cout << "Gamma " << gamma << endl;
		cout << "t " << t << endl;
	}

	double beta_plus_gamma = beta + gamma;

	if(CRITICAL_DEBUG)
	{
		cout << "beta_plus_gamma" << beta_plus_gamma << endl;
	}

	if( beta >= 0 )
	{
		if( gamma >= 0 )
		{
			if( beta_plus_gamma <= 1 )
			{
				return t;
			}
		}
	}

	return -1;
}


/**********************************************************************
 * Function_Name: Intersection
 * Return 		: SUCCESS FAILURE STATUS
 * Comments 	: Uses LaPack to compile, takes in 3 points on the face,
 * 					A, B, C, Ray, FocalPT. Returns the beta, gamma, and t;
 **********************************************************************/
int Scene::LaPack( const Vertex A, const Vertex B, const Vertex C, const VectorSpace& Ray, const Vertex& FocalPt, double &beta, double &gamma, double &t ) const
{

	int n1 = 3, nrhs = 1, lda = 3, ldb = 3, info, ipiv[3];

	Vertex C_minus_A = C - A;

	if(CRITICAL_DEBUG)
	{
		cout << "C_minus_A " << C_minus_A << endl;
	}

	Vertex B_minus_A = B - A;

	if(CRITICAL_DEBUG)
	{
		cout << "B_minus_A " << B_minus_A << endl;
	}

	Vertex L_minus_A = FocalPt - A;

	if(CRITICAL_DEBUG)
	{
		cout << "L_minus_A " << L_minus_A << endl;
	}

	double a[3*3] = { B_minus_A.arr[0], B_minus_A.arr[1], B_minus_A.arr[2],    C_minus_A.arr[0], C_minus_A.arr[1], C_minus_A.arr[2],  -Ray.vs[0], -Ray.vs[1], -Ray.vs[2] };
	double b[3*1] = { L_minus_A.arr[0], L_minus_A.arr[1], L_minus_A.arr[2] };

	dgesv_( &n1, &nrhs, a, &lda, ipiv, b, &ldb, &info );
	beta = b[0], gamma = b[1], t = b[2];

	return EXIT_SUCCESS;

}


