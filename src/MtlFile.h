/*
 * MtlFile.h
 *
 *  Created on: Nov 18, 2012
 *      Author: hrushi
 */

#ifndef MTLFILE_H_
#define MTLFILE_H_


#include "Includes.h"
#include "Material.h"

class MtlFile
{

protected:
	string MtlFilePath;
	std::ifstream MtlFilePtr;

	string GetMtlFilePath( string ObjFilePath, string MtlFileName);
	int OpenMtlFile(string Path);

public:
	MtlFile(string FileName);
	virtual ~MtlFile();

	int LoadAllMtl();
	string GetMtlPath(){ return MtlFilePath; }

	int PrintAllMtls();

	vector<Material> AllMaterials;

	map<string, Material> MtlMap;



};

#endif /* MTLFILE_H_ */
