//-----------------------------------------------------------------------------
//
// ImageLib Sources
// Copyright (C) 2000-2001 by Denton Woods
// Last modified: 11/28/2001 <--Y2K Compliant! =]
//
// Filename: openil/bmp.h
//
// Description: Reads and writes to a bitmap (.bmp) file.
//
//-----------------------------------------------------------------------------


#ifndef DDS_H
#define DDS_H

#include "il_internal.h"


#ifdef _WIN32
	#pragma pack(push, dds_struct, 1)
#endif
typedef struct DDSHEAD
{
	ILbyte	Signature[4];
    
	ILint	Size1;				// size of the structure (minus MagicNum)
    ILint	Flags1;				// determines what fields are valid
    ILint	Height;				// height of surface to be created
    ILint	Width;				// width of input surface
    ILint	LinearSize;			// Formless late-allocated optimized surface size
    ILint	Depth;				// Depth if a volume texture
    ILint	MipMapCount;		// number of mip-map levels requested
    ILint	AlphaBitDepth;		// depth of alpha buffer requested

	ILint	NotUsed[sizeof(ILint) * 10];

	ILint	Size2;				// size of structure
	ILint	Flags2;				// pixel format flags
	ILint	FourCC;				// (FOURCC code)
	ILint	RGBBitCount;		// how many bits per pixel
	ILint	RBitMask;			// mask for red bit
	ILint	GBitMask;			// mask for green bits
	ILint	BBitMask;			// mask for blue bits
	ILint	RGBAlphaBitMask;	// mask for alpha channel
	
    ILint	ddsCaps1, ddsCaps2, ddsCaps3, ddsCaps4; // direct draw surface capabilities
	ILint	TextureStage;
} IL_PACKSTRUCT DDSHEAD;
#ifdef _WIN32
	#pragma pack(pop, dds_struct)
#endif



// use cast to struct instead of RGBA_MAKE as struct is
//  much
typedef struct Color8888
{
	ILubyte r;		// change the order of names to change the 
	ILubyte g;		//  order of the output ARGB or BGRA, etc...
	ILubyte b;		//  Last one is MSB, 1st is LSB.
	ILubyte a;
} Color8888;


typedef struct Color565
{
	unsigned nBlue  : 5;		// order of names changes
	unsigned nGreen : 6;		//	byte order of output to 32 bit
	unsigned nRed	: 5;
} Color565;


typedef struct DXTColBlock
{
	ILshort col0;
	ILshort col1;

	// no bit fields - use bytes
	ILbyte row[4];
} DXTColBlock;

typedef struct DXTAlphaBlockExplicit
{
	ILshort row[4];
} DXTAlphaBlockExplicit;

typedef struct DXTAlphaBlock3BitLinear
{
	ILbyte alpha0;
	ILbyte alpha1;

	ILbyte stuff[6];
} DXTAlphaBlock3BitLinear;


// Defines
#define DDS_LINEARSIZE	0x00080000l
#define DDS_VOLUME		0x00200000L
#define DDS_COMPLEX		0x00000008l
#define DDS_DEPTH		0x00800000l



// Remove!
#ifndef MAKEFOURCC
    #define MAKEFOURCC(ch0, ch1, ch2, ch3)                              \
                ((ILint)(ILbyte)(ch0) | ((ILint)(ILbyte)(ch1) << 8) |   \
                ((ILint)(ILbyte)(ch2) << 16) | ((ILint)(ILbyte)(ch3) << 24 ))
#endif //defined(MAKEFOURCC)

enum PixFormat
{
	PF_ARGB,
	PF_DXT1,
	PF_DXT2,
	PF_DXT3,
	PF_DXT4,
	PF_DXT5,
	PF_UNKNOWN
};


// Global variables
DDSHEAD	Head;			// Image header
ILubyte	*CompData;		// Compressed data
ILubyte	*DecompData;	// Decompressed data
ILuint	CompSize;		// Compressed size
ILuint	CompLineSize;	// Compressed line size
ILuint	CompFormat;		// Compressed format


// Internal functions
ILboolean	iLoadDdsInternal(ILvoid);
ILboolean	iIsValidDds(ILvoid);
ILboolean	iCheckDds(DDSHEAD *Head);
ILboolean	ReadData(ILvoid);
ILboolean	Decompress(ILvoid);
ILvoid		DecodePixelFormat(ILvoid);
ILboolean	DecompressDXT1(ILvoid);
ILboolean	DecompressDXT2(ILvoid);
ILboolean	DecompressDXT3(ILvoid);
ILboolean	DecompressDXT4(ILvoid);
ILboolean	DecompressDXT5(ILvoid);


#endif//DDS_H