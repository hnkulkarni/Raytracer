/*
 * CImage.cpp
 *
 *  Created on: Oct 17, 2012
 *      Author: hrushi
 */

#include "CImage.h"

/**********************************************************************
 * Function_Name: Initialize the Image
 * Return 		:
 * Comments 	:
 **********************************************************************/
CImage::CImage(double *lim)
{
	width 	= lim[2] - lim[0] + 1;
	height 	= lim[3] - lim[1] + 1;

	size = width * height;

	Initialize(size);
}


/**********************************************************************
 * Function_Name: Constructor;
 * Return 		:
 * Comments 	:
 **********************************************************************/
CImage::CImage(double ImageWidth, double ImageHeight)
{

	width = ImageWidth;
	height = ImageHeight;
	size = ImageWidth * ImageHeight;

	Initialize(width * height);
}

/**********************************************************************
 * Function_Name: Initialize
 * Return 		:
 * Comments 	:
 **********************************************************************/
int CImage::Initialize(double ImageSize)
{

	Data.resize( ImageSize );

	// Set a blank black pixel
	Color C;
	Data.assign( ImageSize , C);

	return EXIT_SUCCESS;
}
/**********************************************************************
 * Function_Name: Default Destructor
 * Return 		:
 * Comments 	:
 **********************************************************************/
CImage::~CImage() {
	// DONE Auto-generated destructor stub
}


/**********************************************************************
 * Function_Name: CopyConstructor
 * Return 		:
 * Comments 	:
 **********************************************************************/
CImage::CImage(const CImage& rhsImage)
{

	CopyImage(rhsImage);
}


/**********************************************************************
 * Function_Name: Overloading =
 * Return 		:
 * Comments 	: So that we can do image1 = image2;
 **********************************************************************/
CImage& CImage::operator =(const CImage& rhsImage)
{
	CopyImage(rhsImage);

	return (*this);
}

/**********************************************************************
 * Function_Name: CopyImage
 * Return 		:
 * Comments 	: Writing as a seprate function so that there is
 * 					no repeat in code.
 **********************************************************************/
int CImage::CopyImage(const CImage& rhsImage)
{
	Data.resize( rhsImage.Data.size() );
	width 	= rhsImage.width;
	height 	= rhsImage.height;
	size  	= rhsImage.size;
	Data 	= rhsImage.Data;

	return EXIT_SUCCESS;

}

/**********************************************************************
 * Function_Name: SetPixel
 * Return 		:
 * Comments 	: + Swaps X and Y for transfroming -1, -1 from the viewport,
 * 					which is on the bottom left, to the 0,0 of image which
 * 					is on the top left.
 * 				  + Subtracts the height from the iX, to write using the raster
 * 				  	scanning technique
 **********************************************************************/
int CImage::SetPixel ( const unsigned int iX, const unsigned int iY, const unsigned int R, const unsigned int G, const unsigned int B)
{

	Color Val(R, G, B);

	Val = Val.Saturate(255);

	unsigned int Viewport_height = height - 1; // Image has one pixel more than the given width and height,
												// because of the zero pixel that sits in between.
	try
	{
		// Swapping the X and Y because we are writing in the clipping plane
		Data.at( iY * width + abs( Viewport_height - iX )  ) = Val;

	}
	catch(...)
	{
		cerr << "Cannot Set Pixel Val " << endl;
		cerr << "given iX " << iX << " iY " << iY << endl;
		cerr << "Error in  " << iY * width + abs( Viewport_height - iX )  << " Out of " << Data.size() << endl;
	}

	return EXIT_SUCCESS;
}



/**********************************************************************
 * Function_Name: SetPixel
 * Return 		:
 * Comments 	:
 **********************************************************************/
int CImage::SetPixel(const unsigned int iX, const unsigned int iY, const Color& PixColor )
{

	SetPixel(iX, iY, PixColor.RGB[0], PixColor.RGB[1], PixColor.RGB[2] );

	return EXIT_SUCCESS;
}

/**********************************************************************
 * Function_Name: Write
 * Return 		:
 * Comments 	: Writes the image to the path
 **********************************************************************/
int CImage::Write(string FilePath)
{

	std::ofstream OutputImgPtr;
	OutputImgPtr.exceptions( std::ofstream::failbit | std::ofstream::badbit );

	try
	{
		OutputImgPtr.open( FilePath.c_str() );
	}
	catch( std::ofstream::failure &e)
	{
		cerr << "Error Opening file : " << FilePath << endl;
		exit( EXIT_FAILURE );
	}

	OutputImgPtr << "P3 " << width << " " << height << " " << MAX_COLOR_VAL << endl;
	for(unsigned int i = 0; i < width; i++ )
	{
		for( unsigned int j = 0; j < height; j++ )
		{
			OutputImgPtr << Data.at(i + j * width);
		}

		OutputImgPtr << endl;
	}

	return EXIT_SUCCESS;
}
