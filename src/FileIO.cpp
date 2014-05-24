/*
 * FileIO.cpp
 *
 *  Created on: Sep 22, 2012
 *      Author: hrushi
 */

#include "FileIO.h"

/**********************************************************************
 * Function_Name:
 * Return 		:
 * Comments 	:
 **********************************************************************/

/**********************************************************************
 * Function_Name: FileIO Constructor
 * Return 		:
 * Comments 	: Creates a ifstream pointer for this file path
 * 				: default mode for opening the file is Input
 **********************************************************************/
FileIO::FileIO(string Name, bool FileMode = INPUT) {
	// DONE Auto-generated constructor stub
	FileName = Name;
	cout << "The Name of the file is " << FileName << endl;


	OutputImagePath.clear();

	// Setting up Exceptions
	fptr.exceptions(fstream::failbit | fstream::badbit);

	// Copy Mode of Operation for the file
	Op_Mode = FileMode;
	cout << "File Mode - ";

	if (Op_Mode == INPUT) {
		cout << "Input " << endl;

		//Opening the file
		try {
			fptr.open(FileName.c_str());
		} catch (fstream::failure& e) {
			cerr << "Error Opening " << FileName << " : " << e.what() << endl;
			throw ERR_FILE_NOT_FOUND;
		}

		cout << "File Opening Success " << endl;
	} else {
		cout << "Output" << endl;
		//Opening the file

		try {
			fptr.open(FileName.c_str(), fstream::out);
		} catch (fstream::failure& e) {
			cerr << "Error Opening " << FileName << " in Write Mode : " << e.what() << endl;
		}

		cout << "File Opening Success " << endl;
	}

	EOF_BIT = false;

}


/**********************************************************************
 * Function_Name: Destructor
 * Return 		:
 * Comments 	: Closes the file
 **********************************************************************/
FileIO::~FileIO() {
	// DONE Auto-generated destructor stub

	if (fptr.is_open()) {
		cout << "Closing " << FileName << endl;
		fptr.close();
	}

}

/**********************************************************************
 * Function_Name:
 * Return 		:
 * Comments 	:
 **********************************************************************/

/**********************************************************************
 * Function_Name: Read Model File
 * Return 		: Object of Class Scene
 * Comments 	: Reads the model file and returns the object of class
 * 				: scene
 **********************************************************************/
Scene FileIO::ReadModelFile() {
	Scene s;
	string line;

	int iCurrentGroup = 0;

	if (fptr.is_open()) {

		if (Op_Mode == INPUT) {
			cout << "Reading " << FileName << endl;

			while (fptr.good()) {
				try {
					getline(fptr, line);

					ProcessLine(s, line, iCurrentGroup);

					if (fptr.fail() && !fptr.eof()) {
						throw;
					}
				} catch (fstream::failure& e) {
					if (fptr.eof()) {
						EOF_BIT = true;
					} else {
						throw;
					}
				}

			}

			fptr.clear();
		}
	} else {
		cout << "File Pointer not open" << endl;

	}

	// Make a list of all unique elements in the group
	s.MakeGroupIdxUnique();

	return s;

}

/**********************************************************************
 * Function_Name: Processes every line read from the model file
 * Return 		: SUCCESS / Failure
 * Comments 	: This is essentially the switch case for reading the model file
 **********************************************************************/
int FileIO::ProcessLine(Scene& s, string& line, int& iCurrentGroup){
	string str;
	istringstream iss_line;

	string GroupName;
	iss_line.str(line);

	str = FirstNonWhiteSpace(iss_line);



	if(!str.compare("mtllib"))
	{
		cout << "Reading Material" << endl;
		cout << "Model File Name" << FileName << endl;

		string MtlFileName;
		iss_line >> MtlFileName;

		string MtlFilePath = GetMtlFilePath(FileName, MtlFileName);
		cout << "MtlFilePath " << MtlFilePath << endl;

		LoadMtl(s, MtlFilePath);

	}
	else if(!str.compare("#"))
	{
		//Do nothing for the comment
	}

	else if(!str.compare("g"))
	{
		iCurrentGroup = LoadGroup(s, iss_line);
	}

	else if(!str.compare("v"))
	{

		// if there is no current group, create a default and add these points
		if (s.NumGroups == 0)
		{
			iCurrentGroup = s.AddNewGroup();
		}

		LoadVertices(s, iss_line);

	}
	// Read Faces
	else if(!str.compare( "f"))
	{
		if (s.NumGroups == 0) {
			iCurrentGroup = s.AddNewGroup();
		}

		LoadFaces(s, iss_line, iCurrentGroup);
	}
	else if( !str.compare("e"))
	{
		LoadEclipse( s, iss_line);
	}
	else if( !str.compare("usemtl") )
	{
		LoadMtlName(s, iss_line );
	}
	else
	{
		/*
		 * If there is anything else, skip !!
		 */
	}

	iss_line.clear();
	iss_line.str("");

	return EXIT_SUCCESS;
}

/**********************************************************************
 * Function_Name: LoadEclipse
 * Return 		:
 * Comments 	:
 **********************************************************************/
string FileIO::LoadMtlName( Scene &s, istringstream& iss_line )
{

	string MtlName;

	iss_line >> MtlName ;

	s.ListMtls.push_back( MtlName );

	return MtlName;
}
/**********************************************************************
 * Function_Name: LoadEclipse
 * Return 		:
 * Comments 	:
 **********************************************************************/
int FileIO::LoadEclipse( Scene& s, istringstream& iss_line )
{

	Ellipse TempEllipse;
	iss_line >> TempEllipse;
	TempEllipse.Center = s.v.at( TempEllipse.VertexIndx - 1);
	TempEllipse.iGroupIdx = s.g.size() -1;

	if( s.ListMtls.size() > 0 )
	{
		unsigned int MtlListIdx 	= s.ListMtls.size() - 1;
		TempEllipse.MtlName 		= s.ListMtls.at( MtlListIdx);
	}
	else
	{
		TempEllipse.MtlName = "";
	}

	s.e.push_back(TempEllipse);

	return EXIT_SUCCESS;
}
/**********************************************************************
 * Function_Name: LoadMaterials
 * Return 		:
 * Comments 	:
 **********************************************************************/
int FileIO::LoadMtl(Scene& s, string MtlFilePath)
{

	MtlFile CMtl(MtlFilePath);
	CMtl.LoadAllMtl();

	s.MaterialMap = CMtl.MtlMap;

	return EXIT_SUCCESS;
}

/**********************************************************************
 * Function_Name: GetMtlFilePath
 * Return 		: MaterialFilePath
 * Comments 	: The MaterialFile is in the same folder but with a different
 * 					name given by the 'mtllib' command in the obj file. This
 * 					function will take the objfile path, gets its directory name,
 * 					and then append the materialfilename at its end.
 **********************************************************************/
string FileIO::GetMtlFilePath(string ObjFilePath, string MtlFileName)
{

	string FilePath;
	char* cTemp = new char[ObjFilePath.size() + 1 ];
	strcpy(cTemp, ObjFilePath.c_str() );

	FilePath.assign( dirname(cTemp) );

	cout << "Output of Dirname " << FilePath << endl;

	cout << "FilePath " << MtlFileName << endl;

	FilePath += "/" + MtlFileName;


	delete[] cTemp;
	return FilePath;

}


/**********************************************************************
 * Function_Name: Load Faces
 * Return 		: Index to the recently added face
 * Comments 	:
 **********************************************************************/
int FileIO::LoadFaces(Scene& s, istringstream& iss_line, int iCurrentGrpIdx) {

	int iCurrentFace = -1;
	iss_line.exceptions(istringstream::failbit | istringstream::badbit);

	int Index2aVertex;
	iCurrentFace = s.g.at(iCurrentGrpIdx).AddNewFace();

	string tempstr;
	char tempchar = 0;

	while (iss_line.good())
	{
		try
		{
			iss_line >> Index2aVertex;
			s.g.at(iCurrentGrpIdx).f.at(iCurrentFace).AddIndex2aVertex( Index2aVertex);
			s.v.at( Index2aVertex - 1).FaceIdx.push_back( iCurrentFace  );
		}

		catch (istringstream::failure &e)
		{
			if( !iss_line.eof() )
			{
				iss_line.clear();
				iss_line >> tempstr;
				tempchar = tempstr.at(0);
				if( tempchar == '/')
				{
					/*
					 * This is done to read the model file from SketchUp-Pro.
					 *[Example] f 1/1/1 2/2/2 3/3/3
					 * in this case, only the first '1' is read, and then rest is skipped till the
					 * next whitespace.
					 *
					 * So we will end up reading
					 * f 1 2 3
					 */
					iss_line.clear();
					continue;

				}
				else
				{
					cout << "Cannot Read Index To a Vertex in Face " << iCurrentFace << " of Group " << s.g.at(iCurrentGrpIdx).name << endl;
					iss_line.clear();
					exit( ERR_CANNOT_READ_INDEX2VERTEX );
				}
			}
		}
	}

	if(s.g.at(iCurrentGrpIdx).f.at(iCurrentFace).Index2Vertex.size() < MIN_VERTICES_PER_FACE )
	{
		cerr << "Face " << iCurrentFace << " of Group " << s.g.at( iCurrentGrpIdx).name;
		cerr << " has less than " << MIN_VERTICES_PER_FACE << " Vertices" << endl;

		throw ERR_LESS_THAN_MIN_VERTICES;
	}


	// Create Vectors along the sides of the face
	s.g.at(iCurrentGrpIdx).f.at(iCurrentFace).MakeFaceVectors( s.v );
	s.g.at(iCurrentGrpIdx).f.at(iCurrentFace).GetSurfaceNormal();

	if( s.ListMtls.size()  > 0 )
	{
		unsigned int MtlListIndx = s.ListMtls.size() -1 ; // Contians the most recent material added to the file
		s.g.at( iCurrentGrpIdx ).f.at( iCurrentFace ).MtlName = s.ListMtls.at( MtlListIndx );

		if( CRITICAL_DEBUG )
		{
			cout << "Loaded Material " << s.g.at( iCurrentGrpIdx ).f.at( iCurrentFace ).MtlName << endl;
		}
	}
	else
	{
		s.g.at( iCurrentGrpIdx ).f.at( iCurrentFace ).MtlName  = "";
	}

	return iCurrentFace;
}

/**********************************************************************
 * Function_Name: LoadVertices
 * Return 		: Index to the latest vertices loaded
 * Comments 	:
 **********************************************************************/
int FileIO::LoadVertices(Scene&s, istringstream& iss_line)
{
	int iCurrentVetex = -1;

	iss_line.exceptions(istringstream::failbit | istringstream::badbit);
	double x, y, z, scale;

	// Read Value for X
	try {
		iss_line >> x;
	} catch (istringstream::failure &e) {
		cerr << "Cannot Read Vertices" << endl;
		cerr << "Cannot Read double for x " << endl;
		throw ERR_CANNOT_READ_DOUBLE;
	}

	// Read Value for Y
	try {
		iss_line >> y;
	} catch (istringstream::failure &e) {
		cerr << "Cannot Read Vertices" << endl;
		cerr << "Cannot Read double for y " << endl;
		throw ERR_CANNOT_READ_DOUBLE;
	}

	// Read value for Z
	try {
		iss_line >> z;
	} catch (istringstream::failure &e) {
		cerr << "Cannot Read Vertices" << endl;
		cerr << "Cannot Read double for z " << endl;
		throw ERR_CANNOT_READ_DOUBLE;
	}

	// Reading value for scale
	try {
		iss_line >> scale;
	} catch (istringstream::failure &e) {
		/*
		 * Reading default value of scale
		 */
		scale = 1;
	}

	iCurrentVetex = s.AddNewVertex(x, y, z, scale);

	return iCurrentVetex;
}

/**********************************************************************
 * Function_Name: LoadGroup
 * Return 		: int
 * Comments 	: Returns the index of the group to which the following
 * 				: vertices should be added
 **********************************************************************/
int FileIO::LoadGroup(Scene& s, istringstream& line) {

	string Group_Name;

	line.exceptions(istringstream::failbit | istringstream::badbit);

	try{
		line >> Group_Name;
	} catch( istringstream::failure& e)
	{
		if(line.eof())
		{
			Group_Name = "default";

		}
		else
		{
			cerr << "Error Reading Group Name " << endl;
			throw ERR_CANNOT_READ_GROUPNAME;

		}
	}

	int iCurrentGrp = 0;
	// return the index of the group if already exists
	iCurrentGrp = s.ifGroupExist(Group_Name);

	if (iCurrentGrp == NO_SUCH_GROUP) {
		// Add a new group and load its index
		iCurrentGrp = s.AddNewGroup(Group_Name);
	} else {
		cout << "New vertices will be added to the Group Num " << iCurrentGrp
				<< endl;
		cout << "As it has the same name " << Group_Name << endl;
	}

	return iCurrentGrp;
}

/**********************************************************************
 * Function_Name: FirstNonWhiteSpace
 * Return 		: string
 * Comments 	: Returns the first non white space character from the string
 **********************************************************************/
string FileIO::FirstNonWhiteSpace(istringstream& iss)
{

	string str;
	iss >> str;

	return str;
}



/**********************************************************************
 * Function_Name: isEndOfFile
 * Return 		: bool
 * Comments 	: Returns the end of file bit for the FileIO, can be use
 * 				: if try catch exception fails after the EOF of the file
 **********************************************************************/
bool FileIO::isEndOfFile() {
	return EOF_BIT;
}

/**********************************************************************
 * Function_Name: Mode
 * Return 		: bool
 * Comments 	: Returns the mode of operation in which the file was
 * 				: opened.
 * 				: True - Input mode
 * 				: False - Output
 **********************************************************************/
bool FileIO::Mode() {
	return Op_Mode;
}

/**********************************************************************
 * Function_Name: Path
 * Return 		: string
 * Comments 	: Returns the path of this file pointer
 **********************************************************************/
string FileIO::Path() {
	return FileName;
}



/**********************************************************************
 * Function_Name: WriteModelFile
 * Return 		: SUCCESS/FAILURE
 * Comments 	: Writes the given model file
 **********************************************************************/
int FileIO::WriteModelFile(const Scene& s, string InputFileName = "", string TransformFileName = "" )
{

	time_t rawtime;
	struct tm * timeinfo;

	time ( &rawtime );
	timeinfo = localtime ( &rawtime );

	if( fptr.is_open() )
	{

		fptr << "#########################################################" << endl;
		fptr << "#" << endl;
		fptr << "# Input Model File \t : " << InputFileName << endl;
		fptr << "# Transform File \t : " << TransformFileName << endl;
		fptr << "# Created On \t \t : " << asctime (timeinfo);
		fptr << "#" << endl;
		fptr << "#########################################################" << endl;

		fptr << endl;

		for(unsigned int iGrp = 0; iGrp < s.g.size(); iGrp++ )
		{
			// Print Group

			fptr << endl;
			fptr << "# Groups" << endl;
			fptr << endl;
			fptr << "g " << s.g.at(iGrp).name << endl;

			fptr << endl;

			// Printing Vertex of the group faces.
			if( iGrp == 0 )
			{
				for( unsigned int u = 0; u < s.v.size(); u++ )
				{
					fptr << "v";

					// For every co-ordinate
					for( unsigned int k = 0; k < 4; k++ )
					{
						fptr << " " << s.v.at(u).arr[k];
					}

					fptr << endl;
				}
			}

			fptr << endl;
			fptr << "# Faces" << endl;
			fptr << endl;

			// Printing Faces
			for(unsigned int iFace = 0; iFace < s.g.at(iGrp).f.size(); iFace++ )
			{
				fptr << "f";

				for( unsigned j = 0; j < s.g.at(iGrp).f.at(iFace).Index2Vertex.size(); j++ )
				{
					fptr << " "<< s.g.at(iGrp).f.at(iFace).Index2Vertex.at(j);
				}

				fptr << endl;
			}
		}
	}
	else
	{
		cout << "Output File not opened." << endl;
	}


	return EXIT_SUCCESS;
}



/**********************************************************************
 * Function_Name: OpCommand
 * Return 		:
 * Comments 	: Reads the command file and operates on the scene.
 **********************************************************************/
int FileIO::OpCommand(Scene& s)
{
	string line;

	if( fptr.is_open() )
	{
		cout << "Reading all commands now " << endl;

		while( fptr.good() )
		{

			try
			{
				getline(fptr, line);

				RunCommand(s, line);

				if (fptr.fail() && !fptr.eof())
				{
					throw ERR_READING_CMD;
				}

			}
			catch (fstream::failure& e)
			{
				if (fptr.eof())
				{
					EOF_BIT = true;
				}
				else
				{
					throw ERR_READING_CMD;
				}
			}
		}
	}


	return EXIT_SUCCESS;
}


/**********************************************************************
 * Function_Name: RunCommand
 * Return 		:
 * Comments 	: Runs the command from the given line on the
 * 				: scene
 **********************************************************************/
int FileIO::RunCommand(Scene& s, string line )
{

	istringstream iss_line;

	string GroupName;
	iss_line.str(line);

	string ch = FirstNonWhiteSpace(iss_line);

	char Cmd;

	/*
	 * If the Length of the line is zero,
	 * then pass in the first character as NULL
	 */
	if( ch.length() > 0 )
	{
		Cmd = ch.at(0);
	}
	else
	{
		Cmd = '\0';
	}

	if( line.length() )
	{
		switch (Cmd)
		{
		case '#':
			//Do nothing for the comment
			cout << "Skips : " << line << endl;
			break;

		case 't':
			cout << "Translate Command \t : " << line << endl;
			RunTranslate(s, iss_line);

			cout << "Run Translate on all the pointS " << endl;
			s.TrMat2Point();

			break;

		case 's':
			cout << "Running Scale Command \t : " << line << endl;
			RunScale(s, iss_line);

			cout << "Run Scale on all the pointS " << endl;
			s.TrMat2Point();


			break;

		case 'a':
			cout << "Running Arbit Command \t : " << line << endl;
			RunArbit(s, iss_line);

			cout << "Run Arbit on all the pointS " << endl;
			s.TrMat2Point();

			break;

		case 'r':
			cout << "Running Rotation \t : " << line << endl;
			RunRotate(s, iss_line);


			cout << "Run Rotate on all the pointS " << endl;
			s.TrMat2Point();

			break;

		case 'c':
			cout << "Camera Command \t \t : " << line << endl;
			RunCamera(s, iss_line);
			break;

		case 'w':
			cout << "Wire Frame Command \t \t: " << line << endl;
			RunWireFrame(s, iss_line);
			break;

		case ' ':
			cout << "Blank Command " << line << endl;
			break;

		case 'q':
			cout << "Ray Tracing " << line << endl;
			RunRayTrace(s, iss_line, FileName );

			break;

		case 'l':
			cout << "Loading the Light " << line << endl;
			LoadLight(s, iss_line );
			break;

		default:
			cout << "Invalid Command \t : " << line << endl;
			cout << "Skip" << endl;
			break;
		}
	}
	else
	{
		cout << "Skipping Empty Line" << endl;
	}

	return EXIT_SUCCESS;
}


/**********************************************************************
 * Function_Name: LoadLight
 * Return 		:
 * Comments 	:
 **********************************************************************/
int FileIO:: LoadLight( Scene &s, istringstream& iss_line )
{

	Light TempLight;

	iss_line >> TempLight;

	s.lt.push_back(TempLight);

	return EXIT_SUCCESS;
}
/**********************************************************************
 * Function_Name: RunRayTrace
 * Return 		:
 * Comments 	:
 **********************************************************************/
CImage FileIO::RunRayTrace(Scene& s, istringstream& iss_line, const string& CmdFileName )
{

	string TempStr = CmdFileName;

	RayTrace RT( iss_line, TempStr );
	CImage Frame = RT.Render(s);


	return Frame;

}
/**********************************************************************
 * Function_Name: RunWireFrame
 * Return 		:
 * Comments 	: Reads the WireFrame Command and runs the WireFrame
 * 					command
 **********************************************************************/
CImage FileIO::RunWireFrame( Scene& s, istringstream& iss_line)
{
	static int  WireFrameCmdID = 0;

	WireFrameCmdID++;
	WireFrame oWireFrame(iss_line);

	cout << oWireFrame;

	cout << "WireFrameCmdId " <<  WireFrameCmdID << endl;
	CImage Frame = oWireFrame.Render(s);

	size_t found_dot = OutputImagePath.find(".");
	cout << "First Dot in " << OutputImagePath <<  " is at " << int(found_dot) << endl;

	size_t found_Slash = OutputImagePath.find("/");

	string TempStr;
	string ClippedOutputName;


	if(found_Slash - found_dot == 1)
	{
		TempStr.assign(OutputImagePath, found_Slash,  OutputImagePath.length() );

		found_dot = TempStr.find("." );
		cout << TempStr << " " << found_dot <<  endl;

		ClippedOutputName.assign(OutputImagePath, 0 , found_Slash + found_dot );
		cout << "Clipped Name " << ClippedOutputName << endl;
	}

	std::stringstream WriteImageFileName;
	if(ClippedOutputName.size())
	{
		WriteImageFileName << ClippedOutputName << std::setw(3) << std::setfill('0') << WireFrameCmdID << ".ppm";
	}
	else
	{
		WriteImageFileName << OutputImagePath << std::setw(3) << std::setfill('0') << WireFrameCmdID << ".ppm";
	}

	cout << WriteImageFileName.str() <<endl;

	Frame.Write(WriteImageFileName.str());

	// Clear the stream;
	WriteImageFileName.clear();
	WriteImageFileName.str("");

	return Frame;
}
/**********************************************************************
 * Function_Name: RunCamera
 * Return 		: EXIT SUCCESS - FAILURE
 * Comments 	: Reads the string and then run the camera command
 **********************************************************************/
int FileIO::RunCamera( Scene& s, istringstream& iss_line )
{

	s.AddNewCamera(iss_line);

	int iNumCamera = s.c.size();

	s.c.at( iNumCamera - 1).MakePRT();

	return EXIT_SUCCESS;

}

/**********************************************************************
 * Function_Name: RunRotate
 * Return 		:
 * Comments 	: Runs the Rotate Line Command
 **********************************************************************/
int FileIO::RunRotate( Scene& s, istringstream& iss_line )
{

	iss_line.exceptions(istringstream::failbit | istringstream::badbit);

	string name;
	double theta, extra;
	VectorSpace vRotAxis;
	try{

		iss_line >> name;
		iss_line >> theta;
		iss_line >> vRotAxis.vs[0];
		iss_line >> vRotAxis.vs[1];
		iss_line >> vRotAxis.vs[2];

	}catch( istringstream::failure &e){

		cerr << "Error Reading Rotate Command " << endl;
	}

	try{
		iss_line >> extra; // This is to check if we have been given any extra element in the translate command.
	}catch( istringstream::failure &e ){
		// Ideally the above line should not work.
		if(iss_line.eof())
		{
			s.Rotate(name, theta, vRotAxis);
		}
		else
		{
			cerr << "Error Reading Rotate Command " << endl;
			throw ERR_READING_CMD;
		}
	}

	return EXIT_SUCCESS;

}
/**********************************************************************
 * Function_Name: RunArbit
 * Return 		:
 * Comments 	: Runs the Arbit Line Command
 **********************************************************************/
int FileIO::RunArbit(Scene& s, istringstream& iss_line )
{
	iss_line.exceptions(istringstream::failbit | istringstream::badbit);

	string name;
	double extra;

	double temp;
	vector<double> arbit(0,16); // 16 elements of double initialized to 0

	try{

		iss_line >> name;

		// 16 elements in the arbit matrix - 4x4
		for(int i = 0; i < 16; i++ )
		{
			iss_line >> temp;
			arbit.push_back(temp);
		}

	}catch( istringstream::failure &e){

		cerr << "Error Reading Arbit Command " << endl;
	}

	try{
		iss_line >> extra; // This is to check if we have been given any extra element in the translate command.
	}catch( istringstream::failure &e ){
		// Ideally the above line should not work.
		if(iss_line.eof())
		{
			s.Arbit(name, arbit);
		}
		else
		{
			cerr << "Error Reading Arbit Command " << endl;
			throw ERR_READING_CMD;
		}


	}


	return EXIT_SUCCESS;
}

/**********************************************************************
 * Function_Name: Run Scale
 * Return 		:
 * Comments 	: Runs the Scale Command
 **********************************************************************/
int FileIO::RunScale(Scene& s, istringstream& iss_line )
{
	iss_line.exceptions(istringstream::failbit | istringstream::badbit );

	string name;
	double x, y, z, extra;

	try{

		iss_line >> name;

		iss_line >> x;
		iss_line >> y;
		iss_line >> z;

	}catch( istringstream::failure &e){

		cerr << "Error Reading Scale Command " << endl;
		exit(ERR_READING_CMD);
	}

	try
	{
		iss_line >> extra; // This is to check if we have been given any extra element in the translate command.

	}
	catch( istringstream::failure &e )
	{
		// Ideally the above line should not work.

		if( iss_line.eof() )
		{
			s.Scale(name, x, y, z);
		}

		else
		{
			cerr << "Error Reading Scale Command " << endl;
			throw ERR_READING_CMD;
		}

	}

	return EXIT_SUCCESS;
}
/**********************************************************************
 * Function_Name: Run Translate
 * Return 		:
 * Comments 	: Runs the Translate Command
 **********************************************************************/
int FileIO::RunTranslate(Scene& s, istringstream& iss_line )
{

	iss_line.exceptions(istringstream::failbit | istringstream::badbit);

	string name;
	double x,y,z;
	double extra;
	try{

		iss_line >> name;
		iss_line >> x;
		iss_line >> y;
		iss_line >> z;

	}catch( istringstream::failure &e){

		cerr << "Error Reading Translate Command " << endl;
	}

	try{
		iss_line >> extra; // This is to check if we have been given any extra element in the translate command.
	}catch( istringstream::failure &e ){
		// Ideally the above line should not work.

		if( iss_line.eof() )
		{
			s.Translate(name, x, y, z);
		}

		else
		{
			cerr << "Error Reading Translate Command " << endl;
			throw ERR_READING_CMD;
		}
	}

	return EXIT_SUCCESS;
}


