/*
 * MtlFile.cpp
 *
 *  Created on: Nov 18, 2012
 *      Author: hrushi
 */

#include "MtlFile.h"

/**********************************************************************
 * Function_Name: Default Constructor
 * Return 		:
 * Comments 	:
 **********************************************************************/
MtlFile::MtlFile( string FilePath)
{
	// DONE Auto-generated constructor stub

	MtlFilePath = FilePath;
	OpenMtlFile(FilePath);
}


/**********************************************************************
 * Function_Name: Opens the file
 * Return 		: int
 * Comments 	: returns EXIT_FAILURE, if the material file cannot be opened
 *
 **********************************************************************/
int MtlFile::OpenMtlFile(string Path)
{

	MtlFilePtr.exceptions(std::ifstream::failbit | std::ifstream::badbit );

	try
	{

		MtlFilePtr.open(Path.c_str());
		cout << "DEBUG Reading " << Path << endl;


	}
	catch(std::ifstream::failure &e)
	{
		cout << "Error Opening the Material File " << endl;
		cout << "Exit " << endl;
		exit(ERR_CANNOT_READ_MTL);
	}

	return EXIT_SUCCESS;
}
/**********************************************************************
 * Function_Name: Default Destructor
 * Return 		:
 * Comments 	:
 **********************************************************************/
MtlFile::~MtlFile()
{
	// DONE Auto-generated destructor stub

	if( MtlFilePtr.is_open())
	{
		MtlFilePtr.close();

		cout << "Closing " << MtlFilePath;
		cout << endl;

	}
}


/**********************************************************************
 * Function_Name: LoadAllMtl
 * Return 		:
 * Comments 	:
 **********************************************************************/
int MtlFile::LoadAllMtl()
{

	string line;

	std::stringstream iss_line;
	string NonWhiteSpace;

	Material Temp_Mtl;

	while( MtlFilePtr.good() )
	{
		MtlFilePtr >> NonWhiteSpace;
		iss_line << line;

		iss_line >> NonWhiteSpace;

		if( CRITICAL_DEBUG )
		{
			cout << "NonWhiteSpace " << NonWhiteSpace << endl;
		}

		if( !NonWhiteSpace.compare("#"))
		{
			// Do Nothing
		}
		else if( !NonWhiteSpace.compare("newmtl"))
		{

			MtlFilePtr >> Temp_Mtl;
			MtlMap[Temp_Mtl.MaterialName] = Temp_Mtl;
		}
		else if( !NonWhiteSpace.compare("#EOF"))
		{
			// Clear Cumulative Variables
			iss_line.clear();
			iss_line.str("");
			NonWhiteSpace.clear();

			return EXIT_SUCCESS;
		}

		// Clear Cumulative Variables
		iss_line.clear();
		iss_line.str("");
		NonWhiteSpace.clear();

	}

	cout << endl;


	return EXIT_SUCCESS;
}


/**********************************************************************
 * Function_Name: PrintAllMtls
 * Return 		:
 * Comments 	:
 **********************************************************************/
int MtlFile::PrintAllMtls()
{

	map<string, Material>::const_iterator end = MtlMap.end();

	for( map<string, Material>::const_iterator it = MtlMap.begin(); it!=end; ++it)
	{
		cout << "Who(key = first) " << it->first;
		cout << "Score(key = second) " << MtlMap[ it->first ];
	}
	return EXIT_SUCCESS;
}


