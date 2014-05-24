/*
 * RayTrace.cpp
 *
 *  Created on: Nov 18, 2012
 *      Author: hrushi
 */

#include "RayTrace.h"


/********************************************************************************************************************************************
 * Function_Name: Default Constructor
 * Return 		:
 * Comments 	:
 ********************************************************************************************************************************************/
RayTrace::RayTrace()
{
	OutputPath 	= "";
	width 		= 0;
	height 		= 0;
	depth		= 0;
}
/********************************************************************************************************************************************
 * Function_Name: Constructor
 * Return 		:
 * Comments 	:
 ********************************************************************************************************************************************/
RayTrace::RayTrace(istringstream& iss_line, const string& CmdFileName)
{

	iss_line.exceptions(istringstream::badbit | istringstream::failbit);

	// Initializing members, to remove the warning
	OutputPath 	= "";
	width 		= 0;
	height 		= 0;
	depth		= 0;

	try
	{
		iss_line >> OutputPath;

		AppendPPMToPath(CmdFileName, OutputPath);

		iss_line >> width;
		iss_line >> height;
		iss_line >> depth;
	}
	catch( istringstream::failure &e )
	{
		cout << "Error Reading Ray Trace Command" << endl;
		exit( ERR_RAY_TRACE_CMD);

	}

}

/********************************************************************************************************************************************
 * Function_Name: AppendPPMToPath
 * Return 		:
 * Comments 	: Appends ".ppm" to the path if required. If the path
 * 					file already contains .ppm then nothing is append
 ********************************************************************************************************************************************/
int RayTrace::AppendPPMToPath(const string& CmdFilePath, string& Path )
{
	string FileName;
	string FileExtension = ".ppm";
	string DirectoryPath;

	char* c_FilePath = new char[Path.size() + 1 ];
	strcpy(c_FilePath, Path.c_str() );
	FileName.assign( basename(c_FilePath) );


	char *c_CmdFilePath = new char[CmdFilePath.size() + 1 ];
	strcpy(c_CmdFilePath, CmdFilePath.data() );
	DirectoryPath.assign( dirname( c_CmdFilePath ));

	size_t found = FileName.find(FileExtension);

	if( found != string::npos )
	{
		cout << "Extension found, no need to append ppm " << endl;
		Path = DirectoryPath + "/" + FileName ;
	}
	else
	{
		Path = DirectoryPath + "/" + FileName + FileExtension;

	}

	delete[] c_FilePath;
	delete[] c_CmdFilePath;
	return EXIT_SUCCESS;
}

/********************************************************************************************************************************************
 * Function_Name: Render
 * Return 		:
 * Comments 	: Renders a test pattern
 * 					+-----------------------+
 * 					|   		|			|
 * 					|			|			|
 * 					|	Green	|	Red		|
 * 					|			|			|
 * 					+-----------+-----------+
 * 					|			|			|
 * 					|			|			|
 * 					|	Blue	|	Gray	|
 * 					|			|			|
 * 					+-----------------------+
 ********************************************************************************************************************************************/
CImage RayTrace::Render()
{
	CImage Frame( width + 1, height + 1);

	Color PixelColor;
	double a, b;

	double aInterval( (double)VIEW_PORT_WIDTH / width  );
	double bInterval( (double)VIEW_PORT_WIDTH / height );

	for( unsigned int iRow = 0; iRow < height; iRow++ )
	{
		for( unsigned int iCol = 0; iCol < width; iCol++ )
		{

			a = VIEW_PORT_MIN + aInterval * iCol;
			b = VIEW_PORT_MIN + bInterval * iRow;

			if( a > 0 &&  b > 0)
			{
				PixelColor.Set(255, 0, 0);
				Frame.SetPixel( iRow , iCol, PixelColor);
				PixelColor.Set(0, 0, 0);
			}

			if( a < 0 && b > 0)
			{
				PixelColor.Set(0, 255, 0);
				Frame.SetPixel( iRow , iCol, PixelColor);
				PixelColor.Set(0, 0, 0);
			}

			if( a < 0 && b < 0)
			{
				PixelColor.Set(0, 0, 255);
				Frame.SetPixel( iRow , iCol, PixelColor);
				PixelColor.Set(0, 0, 0);
			}


			if( a > 0 && b < 0)
			{
				PixelColor.Set(200, 200, 200);
				Frame.SetPixel( iRow , iCol, PixelColor);
				PixelColor.Set(0, 0, 0);
			}


		}
	}

	Frame.Write( OutputPath );
	return Frame;
}

/********************************************************************************************************************************************
 * Function_Name: Render
 * Return 		:
 * Comments 	:
 ********************************************************************************************************************************************/
CImage RayTrace::Render(const Scene& s)
{
	CImage Frame( width + 1, height + 1 );

	Vertex Pxy;

	// Variables for every camera
	Vertex Cam_Focal_Pt;
	double Cam_focal_len;
	VectorSpace Cam_U, Cam_V, Cam_VPN;

	VectorSpace aU, bV, dVPN;

	double aInterval( (double)VIEW_PORT_WIDTH / width  );
	double bInterval( (double)VIEW_PORT_WIDTH / height );

	double a, b;

	VectorSpace Ray;

	Color PixelColor;

	unsigned int ReflectedDepth = 0;
	unsigned int RefractedDepth = 0;

	// For Every Camera
	for( unsigned int iCamera = 0; iCamera < s.c.size(); iCamera++ )
	{

		ReflectedDepth = 0;
		RefractedDepth = 0;

		Cam_Focal_Pt = s.c.at(iCamera).GetFocalPoint();
		Cam_focal_len = s.c.at( iCamera ).GetFocalLength();
		Cam_U = s.c.at( iCamera ).Get_u();
		Cam_V = s.c.at( iCamera ).Get_v();
		Cam_VPN = s.c.at( iCamera ).Get_VPN();

		dVPN = Cam_focal_len * Cam_VPN;

		for( unsigned int iRow = 0; iRow <= height; iRow++ )
		{
			for( unsigned int iCol = 0; iCol <= width; iCol++ )
			{

				a = VIEW_PORT_MIN + aInterval * iCol;
				b = VIEW_PORT_MIN + bInterval * iRow;

				aU = a * Cam_U ;

				if(CRITICAL_DEBUG)
				{
					cout << "aU " << aU << endl;
				}

				bV = b * Cam_V;

				if(CRITICAL_DEBUG)
				{
					cout << "bV " << bV << endl;
				}
				Pxy = Cam_Focal_Pt + (dVPN + aU + bV);

				if(CRITICAL_DEBUG)
				{
					if(( iRow == 50) && ( iCol == 33) )
						cout << "Break point over here " << endl;

					cout << "Pxy " << Pxy << endl;
					cout << "a:[" << iCol <<"] " <<  a << "\t" << "b:[" << iRow << "] " << b << endl;


					if( ( a == 0 && b == 0 ) | ( a == VIEW_PORT_MIN && b == VIEW_PORT_MIN ) )
						cout << "Break here " << endl;
				}

				Ray.CreateVector( Cam_Focal_Pt.arr, Pxy.arr);
				Ray.DoNormalization();

				if(CRITICAL_DEBUG)
				{
					cout << "Ray" << Ray << endl;
				}

				PixelColor = RayReflectance( Ray, s, Cam_Focal_Pt, ReflectedDepth, RefractedDepth);

				if(CRITICAL_DEBUG)
				{

					cout << "PixelColor" << PixelColor << endl;
				}


				Frame.SetPixel( iRow  , iCol, PixelColor);

			}

			if( !( iRow % 1 ) )
			{
				double pDone = 100 * (double)( iRow * width )/ (width * height);
				cout << "done " << pDone << " Please wait " <<  "\r" ;
			}

			if( CRITICAL_DEBUG )
			{

				Frame.Write( OutputPath );
			}
		}
	}

	Frame.Write( OutputPath );

	return Frame;
}


/********************************************************************************************************************************************
 * Function_Name: RayReflectance
 * Return 		:
 * Comments 	:
 ********************************************************************************************************************************************/
Color RayTrace::RayReflectance(const VectorSpace& Ray, const Scene& s, const Vertex& RayOrigin, const unsigned int CurrentReflectedDepth , const unsigned int CurrentRefractedDepth) const
{
	Color PixelColor = Color( 128, 128, 128);



	SurfMin Smin; 	// which has the minumum value of tmin
	// [Index_group, Index_face, Index_Ellipse];

	Smin = s.Intersection( Ray, RayOrigin);

	Vertex PointIn3D;

	Color Reflection;
	Color Refraction;
	Color Combination;
	Color Illum1, Illum2;



	if( Smin != NULL )
	{

		Material MtlProp = GetMaterial(s, Smin);

		PointIn3D = GetPointIn3D(RayOrigin, Ray, Smin.tMin);

		if(CRITICAL_DEBUG)
		{
			cout << "RayOrigin " << RayOrigin << endl;
			cout << "Ray " << Ray << endl;
			cout << "tmin " << Smin.tMin << endl;
			cout << "Ptin3D " << PointIn3D << endl;
		}


		Reflection.Set(0, 0, 0);

		PixelColor = PointReflectance( PointIn3D, Ray, s, Smin);


		Refraction = RefractedRecursion(Ray, s, PointIn3D, Smin, CurrentRefractedDepth );

		Reflection = ReflectedRecursion(Ray, s, PointIn3D, Smin, CurrentReflectedDepth );



		Illum1 =  PixelColor +  Reflection;
		Illum1 = Illum1 * (1 - MtlProp.Tr ) ;


		Illum2 =   Refraction * ( MtlProp.Tr);



		Combination = Illum1 + Illum2;



	}
	return Combination;
}



/********************************************************************************************************************************************
 * Function_Name: RefractedRecursion
 * Return 		:
 * Comments 	: Follow the Refracted ray, and get its reflectance
 ********************************************************************************************************************************************/
Color RayTrace::RefractedRecursion( const VectorSpace& Ray, const Scene& s, const Vertex& PtIn3D, const SurfMin& Smin, const unsigned int iCurrentDepth) const
{
	Color Refracted;

	if( iCurrentDepth < depth )
	{
		Material Mtrl = GetMaterial(s, Smin);

		unsigned int NewRefracDepth = iCurrentDepth + 1;


		double Alpha = Mtrl.Tr;
		double NCurrent = N_AIR;
		double NPrev;

		double Mu; // Refractive Index

		double Beta(0);

		VectorSpace T;

		const unsigned int ResetReflected = 0;

		if( Alpha > 0 && Alpha <= 1 )
		{

			VectorSpace SurfNormal = s.GetSurfaceNormal(PtIn3D, Smin);
			SurfNormal.DoNormalization();

			if( Ray.RayNVal == 1 )
			{
				SurfNormal = -1 * SurfNormal;
			}


			if( CRITICAL_DEBUG )
			{
				cout << "SurfNormal " <<  SurfNormal << endl;
				cout << "Ray " << Ray << endl;
			}

			double RayDotN = SurfNormal.Dot(Ray);

			if(Ray.RayNVal == 1)
			{
				NPrev 	= NCurrent;
				NCurrent = Mtrl.N1;

			}
			else
			{
				NPrev 	= Ray.RayNVal;
				NCurrent = 1;
			}


			Mu = NPrev / NCurrent;

			Beta = CalculateBeta( Ray, SurfNormal, Mu );

			if( Beta == DBL_MAX ) // Not valid beta
			{
				return Color(0, 0, 0);
			}

			T = Alpha * Ray + Beta * SurfNormal;
			T.RayNVal = NCurrent; // Update the Refractive Index of the Ray;

			if( CRITICAL_DEBUG )
			{
				cout << "Refracted Ray " << T << endl;
			}


			Vertex ExPt = PtIn3D + SOME_SMALL_VALUE * T;


			Refracted.Set(0, 0, 0);
			Refracted = RayReflectance(T, s, ExPt, ResetReflected, NewRefracDepth );

			if( CRITICAL_DEBUG )
			{
				cout << "iCurrentDepth " << iCurrentDepth << depth;
				cout << "Refracted " << Refracted << endl;
			}


		}

	}
	return Refracted;

}

/********************************************************************************************************************************************
 * Function_Name: ReflectedRecursion
 * Return 		:
 * Comments 	: Follow the reflected ray, and get its reflectance
 ********************************************************************************************************************************************/
double RayTrace::CalculateBeta(const VectorSpace& Ray, const VectorSpace& SurfNormal, const double Mu ) const
{
	double beta(0);

	double Mu2 = pow( Mu, 2);
	double RDotN = Ray.Dot(SurfNormal);

	double RDotN2 = pow( RDotN, 2);
	double UnderRootVal = 1 - Mu2 + Mu2 * RDotN2;

	if(UnderRootVal < 0 )
	{   // This is to tell the user the that beta value is not valid. Return a RBG = 0, 0, 0 to the user.
		return DBL_MAX;
	}

	double rootVal = sqrt(UnderRootVal);

	double MuRN = 1 * Mu * RDotN;
	beta = -1 * MuRN - rootVal;

	return beta;
}

/********************************************************************************************************************************************
 * Function_Name: ReflectedRecursion
 * Return 		:
 * Comments 	: Follow the reflected ray, and get its reflectance
 ********************************************************************************************************************************************/
Color RayTrace:: ReflectedRecursion( const VectorSpace& Ray, const Scene& s, const Vertex& PtIn3D, const SurfMin& Smin, const unsigned int iCurrentDepth ) const
{

	Color ReflectedColor;
	Vertex ExtraPt;

	const unsigned int ResetRefractedDepth = 0;

	if( iCurrentDepth < depth)
	{
		unsigned int NewDepth = (iCurrentDepth + 1);


		VectorSpace SurfaceNormal = s.GetSurfaceNormal(PtIn3D, Smin );

		double RayDotN = Ray.Dot(SurfaceNormal);

		VectorSpace ReflectedRay = -1 * GetReflactanceRay(RayDotN, Ray,SurfaceNormal);
		ReflectedRay.DoNormalization();

		ExtraPt = PtIn3D + SOME_SMALL_VALUE * ReflectedRay;


		ReflectedColor.Set(0, 0, 0);
		ReflectedColor = RayReflectance( ReflectedRay, s, ExtraPt, NewDepth, ResetRefractedDepth  );

		if( CRITICAL_DEBUG )
		{
			cout << "Reflected Color " << ReflectedColor << " iCurrentDepth " << iCurrentDepth << endl;
		}
	}

	return ReflectedColor;


}





/********************************************************************************************************************************************
 * Function_Name: PointReflectance
 * Return 		:
 * Comments 	:
 ********************************************************************************************************************************************/
Color RayTrace::PointReflectance( const Vertex& PtIn3D, const VectorSpace& Ray, const Scene& s, const SurfMin& Smin) const
{


	Color PixelColor;

	Color DiffuseColor, SpecularColor, Ambient;
	Color LightColor;


	Ambient.Set(5, 5, 5);

	unsigned int CurrentDepth = depth;

	for( unsigned int iLight = 0; iLight < s.lt.size(); iLight++ )
	{
		DiffuseColor.Set(0, 0, 0);
		SpecularColor.Set(0, 0, 0);

		LightColor= s.lt.at( iLight ).RGB;
		VectorSpace LightVector = s.lt.at(iLight ).GetLightVector( PtIn3D );

		//if( !ExternalShadows(PtIn3D, LightVector, s, Smin) ) // Get back to this after the break
		{

			/************* ATTENTION *************************************/
			VectorSpace NegLightVector = -1 * LightVector;
			LightVector = NegLightVector;
			/**************************************************/

			LightVector.DoNormalization();



			if(CRITICAL_DEBUG)
			{
				cout << "Lightvector " << LightVector << endl;
			}

			VectorSpace SurfaceNormal = s.GetSurfaceNormal(PtIn3D, Smin );
			SurfaceNormal.DoNormalization();

			if(CRITICAL_DEBUG)
			{
				cout << "SurfaceNormal " << SurfaceNormal << endl;
			}

			double LDotN = LightVector.Dot(SurfaceNormal);

			Material GroupMtl = GetMaterial(s, Smin);

			/*
			 * Learn't a new thing, it is tricky to have an assignment operator to a map, when it is constant. Had to copy to a temp map and then use it afterwords.
			 * This is because the map I am passing is constant. So according to the indexing of map, [key], if key is not present, then it creates a new element,
			 * of that type, using the default constant. But since the original map is constant, it will avoid creating a new type, if the key element is not found. Hence,
			 * we need to loop through the loop in searching for the keys, and then access that element.
			 */


			if( CRITICAL_DEBUG )
			{
				cout << "Light " << iLight << endl;

				cout << "Light Vector " <<  LightVector << endl;

				cout << "Surface Normal " << SurfaceNormal << endl;
				cout << "LDotN " << LDotN << endl;
			}

			if( LDotN >= 0 )
			{

				DiffuseColor = DiffuseReflectance(GroupMtl, LightColor, LDotN );
				SpecularColor = SpecularReflectance( LightVector, LightColor, SurfaceNormal, GroupMtl, Ray, LDotN);


				if( CRITICAL_DEBUG )
				{
					cout << "Diffuse " << DiffuseColor << endl;
					cout << "Specular " << SpecularColor << endl;
				}

			}

			PixelColor += Ambient + DiffuseColor  + SpecularColor ;


			if( CRITICAL_DEBUG )
			{
				cout << "Pixel Color " << PixelColor << endl;
			}
		}

	}

	return PixelColor;
}


/********************************************************************************************************************************************
 * Function_Name: PointReflectance
 * Return 		:
 * Comments 	:
 ********************************************************************************************************************************************/
bool RayTrace::ExternalShadows(const Vertex& Pt, const VectorSpace& LightRay, const Scene& s,  const SurfMin& Smin) const
{
	Vertex ExtraPt = Pt + SOME_SMALL_VALUE * LightRay;

	SurfMin LSurfMin;
	LSurfMin = s.Intersection( LightRay, ExtraPt );

	if( LSurfMin.tMin > SOME_SMALL_VALUE && LSurfMin.tMin < 1)
	{
		return true;
	}
	return false;
}


/********************************************************************************************************************************************
 * Function_Name: SpecularReflectance
 * Return 		:
 * Comments 	:
 ********************************************************************************************************************************************/
Color RayTrace::SpecularReflectance(const VectorSpace& LightVector, const Color& LightColor,  const VectorSpace& SurfaceNormal, const Material& GroupMtl, const VectorSpace& Ray, const double LDotN) const
{
	Color Specular;


	VectorSpace ReflectanceRay = GetReflactanceRay( LDotN,  LightVector, SurfaceNormal );

	double VDotR = Ray.Dot( ReflectanceRay );

	if( VDotR > DBL_MIN )
	{

		double Alpha = GroupMtl.Ns;

		double VDot_Alpha = pow( VDotR, Alpha);

		double IpKs[3] = {0};

		Matrix oMat;

		oMat.ElementWiseMultiply( IpKs,  LightColor.RGB, GroupMtl.Ks);

		double IpKs_VR_Alpha[3] = {0};

		oMat.MultiplyByConst( IpKs_VR_Alpha, IpKs, VDot_Alpha );

		Specular.Set(IpKs_VR_Alpha );
	}
	return Specular;

}



/********************************************************************************************************************************************
 * Function_Name: DiffuseReflectance
 * Return 		:
 * Comments 	:
 ********************************************************************************************************************************************/
Color RayTrace:: DiffuseReflectance( const Material& GroupMtl, const Color& LightColor, const double LDotN) const
{
	Color DiffuseColor;
	Matrix oMat;

	double IaKd[3] = {0};
	oMat.ElementWiseMultiply(IaKd, LightColor.RGB, GroupMtl.Kd);

	double IaKdCosTheta[3];
	oMat.MultiplyByConst( IaKdCosTheta, IaKd,  LDotN );

	DiffuseColor.Set(IaKdCosTheta);

	return DiffuseColor;
}





/********************************************************************************************************************************************
 * Function_Name: GetReflactanceRay
 * Return 		:
 * Comments 	:
 ********************************************************************************************************************************************/
Material RayTrace::GetMaterial( const Scene& s, const SurfMin & Smin) const
{
	Material GroupMtl;
	map<string, Material> TempMap = s.MaterialMap;

	if( Smin.Type() == SMIN_POINT_ON_ELLIPSE )
	{

		unsigned int iEllipseIdx = Smin.iEllipseIdx;

		string MtlName = s.e.at( iEllipseIdx ).MtlName;
		GroupMtl = TempMap[MtlName];
	}
	else
	{
		GroupMtl = TempMap[s.g.at(Smin.iGroupIdx).f.at(Smin.iFaceIdx).MtlName];
	}

	return GroupMtl;
}
/********************************************************************************************************************************************
 * Function_Name: GetReflactanceRay
 * Return 		:
 * Comments 	:
 ********************************************************************************************************************************************/
VectorSpace RayTrace::GetReflactanceRay( const double LDotN, const VectorSpace& LightVector, const VectorSpace& SurfaceNormal ) const
{
	VectorSpace ReflectanceRay;

	VectorSpace LDotN_N = LDotN * SurfaceNormal;

	VectorSpace TwiceLDotN_N = 2 *  LDotN_N;

	ReflectanceRay = TwiceLDotN_N - LightVector;

	return ReflectanceRay;
}





/**********************************************************************
 * Function_Name: PrintSmin
 * Return 		:
 * Comments 	: Get the point on SurfMin, along the ray
 **********************************************************************/
Vertex RayTrace::GetPointIn3D( const Vertex& RayOrigin, const VectorSpace& Ray, const double t) const
{

	Vertex PointIn3D;

	PointIn3D = RayOrigin + ( t * Ray );

	return PointIn3D;
}


/********************************************************************************************************************************************
 * Function_Name: Default Destructor
 * Return 		:
 * Comments 	:
 ********************************************************************************************************************************************/
RayTrace::~RayTrace()
{

}

