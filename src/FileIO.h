/*
 * FileIO.h
 *
 *  Created on: Sep 22, 2012
 *      Author: hrushi
 */

#ifndef FILEIO_H_
#define FILEIO_H_

#include "Includes.h"
#include "Scene.h"
#include "VectorSpace.h"
#include "WireFrame.h"
#include "CImage.h"

#include "Light.h"

#include "MtlFile.h"
#include "RayTrace.h"

class FileIO {

private:

	// Private Variables

	bool Op_Mode; // Mode of operation for the file; true - Input, false - Output

	//File Pointer
	fstream fptr;
	bool EOF_BIT;

	//Private Functions
	string FirstNonWhiteSpace(istringstream& iss);
	int ProcessLine(Scene& s, string& line, int& iCurrentGroup);
	int LoadGroup(Scene& s, istringstream& line );
	int LoadVertices(Scene& s, istringstream& iss_line );
	int LoadFaces( Scene& s, istringstream& iss_line, int iCurrentGrpIdx );
	int LoadMtl(Scene& s, string MtlFilePath);
	int LoadEclipse( Scene& s, istringstream& iss_line );
	int LoadLight( Scene &s, istringstream& iss_line );
	string LoadMtlName( Scene &s, istringstream& iss_line );

	string GetMtlFilePath(string ObjFilePath, string MtlFileName);



public:
	FileIO( string Name , bool FileMode);
	virtual ~FileIO();

	// Public Functions
	string Path();
	Scene ReadModelFile( );
	bool Mode() ;
	bool isEndOfFile();
	int WriteModelFile(const Scene& s, string InputFileName, string TransformFileName );
	int OpCommand( Scene&s );
	int RunCommand( Scene&s, string line );


	// Run Individual Commands
	int RunTranslate( Scene& s, istringstream& iss_line );
	int RunScale( Scene& s, istringstream& iss_line );
	int RunArbit( Scene& s, istringstream& iss_line );
	int RunRotate( Scene& s, istringstream& iss_line );
	int RunCamera( Scene& s, istringstream& iss_line );
	CImage RunWireFrame(  Scene &s, istringstream& iss_line );
	CImage RunRayTrace( Scene &s, istringstream& iss_line, const string& CmdFileName );



	// Public Variables
	string OutputImagePath;
	string FileName;

};

#endif /* FILEIO_H_ */
