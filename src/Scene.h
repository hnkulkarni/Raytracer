/*
 * Scene.h
 *
 *  Created on: Sep 22, 2012
 *      Author: hrushi
 */

#ifndef SCENE_H_
#define SCENE_H_

// Include all the scene components
#include "Group.h"
#include "Vertex.h"
#include "VectorSpace.h"
#include "Camera.h"
#include "Material.h"
#include "Ellipse.h"
#include "Light.h"

#include "SurfMin.h"

extern "C" void dgesv_( int* n, int* nrhs, double* a, int* lda, int* ipiv, double* b, int* ldb, int* info );

class Scene {

private:

	// Private Variables

	// Private Functions

public:

	/**********************************************************************
	 * Function Type : Constructors, Destructors
	 * Comments 	:
	 **********************************************************************/
	Scene();
	virtual ~Scene();
	Scene( const Scene& rhsScene);
	Scene& operator= ( const Scene& rhsScene );

	//Allocate All the objects]
	int Allocate( const Scene& rhsScene );
	int CopyScene( const Scene& rhsScene );

	/**********************************************************************
	 * Function Type : Member Functions
	 * Comments 	:
	 **********************************************************************/
	//Function for Group
	int AddNewGroup();
	int AddNewGroup(string name);
	int AddNewCamera(istringstream& iss_line);

	int ifGroupExist(string name);
	int FindGroup(string name);
	int MakeGroupIdxUnique();

	// Functions for vertices.
	int GetNumVertices()const;
	int AddNewVertex(double x, double y, double z, double scale);

	// Scene Functions
	int PrintSceneParams();
	int Check();
	int SharedVerticies();

	int Translate(string grp_name, double x, double y, double z);
	int Scale(string grp_name, double x, double y, double z);
	int Arbit(string grp_name, const vector<double>& ArbitTranLine );
	int Rotate( string grp_name, double theta, VectorSpace vRotAxis );
	int TrMat2Point();
	int PrintAllMtls();

	// Camera Functions
	int FindCam( string name);


	// Smin
	int PrintSminScene( const SurfMin& Smin) const;

	// Get Surface Normal
	VectorSpace GetSurfaceNormal(const Vertex& Pt, const SurfMin& Smin) const;


	// Get New Intersection
	SurfMin Intersection(const VectorSpace& Ray, const Vertex& RayOrigin) const;
	double GroupFaceIntersection(const unsigned int iGroupIdx, const unsigned int iFaceIdx, const VectorSpace& Ray, const Vertex& RayOrigin ) const;
	int LaPack( const Vertex A, const Vertex B, const Vertex C, const VectorSpace& Ray, const Vertex& FocalPt, double &beta, double &gamma, double &t ) const;

	/**********************************************************************
	 * Function Type : Member Variables
	 * Comments 	 :
	 **********************************************************************/

	//Public Variables
	vector<Group> g; 					// Vector of all the Groups
	vector<Vertex> v; 					// Vector of all the Vertices
	vector<Camera> c; 					// Vector of all cameras
	vector<Ellipse> e; 					// Vector of all ellipse
	map<string, Material> MaterialMap; 	// Map of all the materials
	vector<Light> lt; 					// Vector of Lights
	vector<string> ListMtls;			// Contains the list of all the materials

	int NumGroups;
	int NumVertices;

};

std::ostream& operator<<( std::ostream& out, const Scene& PrintScene);

#endif /* SCENE_H_ */
