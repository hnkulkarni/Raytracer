/*
 * Material.cpp
 *
 *  Created on: Nov 17, 2012
 *      Author: hrushi
 */

#include "Material.h"

/**********************************************************************
 * Function_Name: Default Constructor
 * Return 		:
 * Comments 	:
 **********************************************************************/
Material::Material() {
	// DONE Auto-generated constructor stub

	MaterialName = "";

	for(int i = 0; i < 3; i++)
	{
		Ka[i] 	= 1;
		Kd[i] 	= 1;
		Ks[i] 	= 1;
	}

	Ns 		= 1;
	d 		= 1;
	Tr 		= 1;
	N1		= 1; // Refractive Index of the object

}

/**********************************************************************
 * Function_Name: Default Destructor
 * Return 		:
 * Comments 	:
 **********************************************************************/
Material::~Material() {
	// DONE Auto-generated destructor stub
}




/**********************************************************************
 * Function_Name: Copy Constructor
 * Return 		:
 * Comments 	:
 **********************************************************************/
Material::Material(const Material& rhsMaterial)
{

	CopyMaterial(rhsMaterial);

}


/**********************************************************************
 * Function_Name: CopyMaterial
 * Return 		:
 * Comments 	:
 **********************************************************************/
int Material::CopyMaterial(const Material& rhsMaterial )
{
	MaterialName = rhsMaterial.MaterialName;

	for(int i = 0; i < 3; i++)
	{
		Ka[i] 	= rhsMaterial.Ka[i];
		Kd[i] 	= rhsMaterial.Kd[i];
		Ks[i] 	= rhsMaterial.Ks[i];
	}

	Ns	= rhsMaterial.Ns;
	d 	= rhsMaterial.d;
	Tr 	= rhsMaterial.Tr;
	N1	= rhsMaterial.N1;

	return EXIT_SUCCESS;

}

/**********************************************************************
 * Function_Name: Overloading =
 * Return 		:
 * Comments 	:
 **********************************************************************/
Material& Material::operator =(const Material& rhsMaterial )
{
	CopyMaterial(rhsMaterial);

	return *this;
}



/**********************************************************************
 * Function_Name: Overloading >>
 * Return 		:
 * Comments 	:
 **********************************************************************/
std::istream& operator>>( std::istream& in, Material& mat)
{

	in.exceptions(std::istream::badbit | std::ios::goodbit);

	unsigned int NumValuesSet  = 0;

	try
	{
		in >> mat.MaterialName;
		NumValuesSet++;
	}
	catch( std::istream::failure& e)
	{
		cout << "Cannot read the Material File Name " << endl;
		exit(ERR_CANNOT_READ_MTL);
	}

	string NonWhiteSpace;
	string line;
	istringstream iss_line;


	while( in.good() )
	{
		try
		{
			if( NumValuesSet < NUM_VALUES_IN_MTL )
			{
				getline(in, line);
				iss_line.str(line);

				iss_line >> NonWhiteSpace;

				if( CRITICAL_DEBUG )
				{
					cout << "DEBUG " << line << endl;
					cout << "DEBUG NON-WhiteSpace " << NonWhiteSpace << endl;
				}

				if(!NonWhiteSpace.compare("Ka")  || !NonWhiteSpace.compare("ka"))
				{
					for( int i = 0; i < 3; i++)
					{
						iss_line >> mat.Ka[i];
					}

					NumValuesSet++;
				}
				else if( !NonWhiteSpace.compare("Kd") || !NonWhiteSpace.compare("kd"))
				{
					for( int i = 0; i < 3; i++ )
					{
						iss_line >> mat.Kd[i];
					}

					NumValuesSet++;

				}
				else if( !NonWhiteSpace.compare("Ks") || !NonWhiteSpace.compare("ks"))
				{
					for( int i = 0; i < 3; i++ )
					{
						iss_line >> mat.Ks[i];
					}

					NumValuesSet++;

				}
				else if( !NonWhiteSpace.compare("Ns") || !NonWhiteSpace.compare("ns"))
				{
					iss_line >> mat.Ns;
					NumValuesSet++;
				}
				else if( !NonWhiteSpace.compare("d") || !NonWhiteSpace.compare("D"))
				{
					iss_line >> mat.d;
					NumValuesSet++;
				}
				else if( !NonWhiteSpace.compare("Tr") || !NonWhiteSpace.compare("tr"))
				{
					iss_line >> mat.Tr;
					NumValuesSet++;
				}
				else if( !NonWhiteSpace.compare("N1") || !NonWhiteSpace.compare("n1") )
				{
					iss_line >> mat.N1;
					NumValuesSet++;
				}

				// Setting Accumulative Data
				iss_line.clear();
				iss_line.str("");
				NonWhiteSpace.assign("");

			}
			else
			{
				break;
			}
		}
		catch( std::istream::failure& e)
		{
			cout << "Cannot read the Material File Name " << endl;
			exit(ERR_CANNOT_READ_MTL);
		}


	}

	return in;
}


/**********************************************************************
 * Function_Name: Overloading <<
 * Return 		:
 * Comments 	:
 **********************************************************************/
std::ostream& operator<< ( std::ostream& out, Material& mat)
{
	out << "Material Name ";
	out << mat.MaterialName << endl;

	out << "Ka";
	for(unsigned int i = 0; i < 3; i++)
	{
		out << " ";
		out << std::setprecision(5) << setw(8) <<  mat.Ka[i];
	}
	out << endl;

	out << "Kd";
	for(unsigned int i = 0; i < 3; i++)
	{
		out << " ";
		out << std::setprecision(5) << setw(8) << mat.Kd[i];
	}
	out << endl;

	out << "Ks";
	for(unsigned int i = 0; i < 3; i++)
	{
		out << " ";
		out << std::setprecision(5) << setw(8) << mat.Ks[i];
	}
	out << endl;

	out << "Ns " << std::setprecision(5) << setw(8) << mat.Ns << endl;
	out << "d  "  << std::setprecision(5) << setw(8) << mat.d << endl;
	out << "Tr " << std::setprecision(5) << setw(8) << mat.Tr << endl;
	out << "N1 " << std::setprecision(5) << setw(8) << mat.N1 << endl;

	return out;
}
