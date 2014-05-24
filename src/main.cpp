//============================================================================
// Name        : HW1.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C, Ansi-style
//============================================================================

#include "Includes.h"
#include "FileIO.h"

#include "Scene.h"

void help()
{
	cerr << "Invalid Number of Arguments " << endl;
	cerr << "Three Arguments are Expected " << endl;
	cerr << "Example - HW1 model.obj transform output.obj" << endl;
}

int main(int argc, char* argv[] )
{

	// Check for correct number of arguments.
	if(argc != 4 )
	{
		help();
		return EXIT_FAILURE;
	}

	Scene s;

	// Read and Check the Model File;
	try
	{
		FileIO ModelFile( argv[1] , INPUT);

		try
		{
			// Read the Model File
			s = ModelFile.ReadModelFile();

			// Print the Scene Parameters
			s.PrintSceneParams();

			// Perform Checks
			s.Check();

		}
		catch(int Err_Num)
		{
			if( !ModelFile.isEndOfFile() )
			{
				cerr << "Some problem reading the Model file " << endl;
			}
			return EXIT_FAILURE;
		}
	}
	catch(int n)
	{

		cerr << "CHECK ERROR Closing Program " << endl;
		return EXIT_FAILURE;

	}

	//************* Perform Transformation Operations.*********************//
	try
	{
		FileIO TransFormation(argv[2], INPUT);
		TransFormation.OutputImagePath.assign(argv[3]); // This is required for the wireframe command to generate the strings.
														// Actually a very bad style of code, but I will come back to this again.
		TransFormation.OpCommand(s);

	}
	catch(int iErr )
	{
		cerr << "Cannot find Transformation matrix " << endl;
		return EXIT_FAILURE;
	}

	// Write the Model File
	try
	{
		FileIO OutputModelFile(argv[3], OUTPUT);

		OutputModelFile.WriteModelFile(s, argv[1], argv[2]);

	}
	catch(int n)
	{
		if( n == ERR_FILE_NOT_FOUND)
		{
			cerr << "Closing Program " << endl;
			return EXIT_FAILURE;
		}
	}
	return EXIT_SUCCESS;
}
