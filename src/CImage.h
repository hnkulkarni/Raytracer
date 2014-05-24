/*
 * CImage.h
 *
 *  Created on: Oct 17, 2012
 *      Author: hrushi
 */

#ifndef CIMAGE_H_
#define CIMAGE_H_

#include "Color.h"
#include "Includes.h"

class CImage {

	 vector< Color > Data;


public:
	CImage(double* Lim);
	CImage(double width, double height);
	virtual ~CImage();

	CImage(const CImage& rhsImage);
	CImage& operator=( const CImage& rhsImage);


	int Initialize(double size);
	int CopyImage(const CImage& rhsImage);
	int SetPixel (const unsigned int iX, const unsigned int iY, const unsigned R, const unsigned int G, const unsigned int B );
	int SetPixel (const unsigned int iX, const unsigned int iY, const Color& PixColor );

	int Write( string FilePath );

	// Public Variables
	unsigned int width, height, size;
};

#endif /* CIMAGE_H_ */
