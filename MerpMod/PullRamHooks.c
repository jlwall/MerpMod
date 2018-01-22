/*
	Copyright (C) 2012-2013 Merrill A. Myers III merrillamyersiii@gmail.com
	
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
*/

#include "EcuHacks.h"

float (*Pull3DHooked)(ThreeDTable* table, float xLookup, float yLookup) __attribute__ ((section ("RomHole_Functions"))) = (float(*)(ThreeDTable* table, float xLookup, float yLookup)) sPull3DFloat;
float (*Pull2DHooked)(TwoDTable* table, float xLookup) __attribute__ ((section ("RomHole_Functions"))) = (float(*)(TwoDTable* table, float xLookup)) sPull2DFloat;

//These are a simpler routines cast back to a FixedPoint value
unsigned char (*Pull2DHookedU8)(TwoDTable* table, float xLookup) __attribute__ ((section ("RomHole_Functions"))) = (unsigned char(*)(TwoDTable* table, float xLookup)) sPull2D_U8;
unsigned short (*Pull2DHookedU16)(TwoDTable* table, float xLookup) __attribute__ ((section ("RomHole_Functions"))) = (unsigned short(*)(TwoDTable* table, float xLookup)) sPull2D_U16;

//These are a simpler routine that finds the nearest lowest axis point, and return fixed point, with no Interp, no float, no Post/Scale / offset
unsigned char (*Pull2DHookedU8fp)(TwoDTableU8* table, unsigned long xLookup) __attribute__ ((section ("RomHole_Functions"))) = (unsigned char(*)(TwoDTableU8* table, unsigned long xLookup)) sPull2D_U8_U32Axis;
unsigned short (*Pull2DHookedU16fp)(TwoDTableU16* table, unsigned long xLookup) __attribute__ ((section ("RomHole_Functions"))) = (unsigned short(*)(TwoDTableU16* table, unsigned long xLookup)) sPull2D_U16_U32Axis;




#if SWITCH_HACKS
float (*ShortToFloatHooked)(unsigned short input, float grad, float offs) __attribute__ ((section ("RomHole_Functions"))) = (float(*)(unsigned short input, float grad, float offs)) sShortToFloat;
#endif

float Pull3DRamHook(float* table, float xLookup, float yLookup)
{
	//Check if r4 is ram or not??
	//WARNING: cannot use LOOKUP TABLES in this region (pRamVariables)!!!
	//Lookup tables must be static or this needs to change.
	if(((void*)table > (void*)&(pRamVariables.MasterInitFlag)) && ((void*)table < (void*)&(pRamVariables.RamHoleEndMarker)))
	{
		return *table;
	}
	else
	{
		return Pull3DHooked((ThreeDTable*)table, xLookup, yLookup);
	}
}

float Pull2DRamHook(float* table, float xLookup)
{
	//Check if r4 is ram or not??
	if(table > (float*)&(pRamVariables.MasterInitFlag))
	{
		return *table;
	}
	else
	{
		 return Pull2DHooked((TwoDTable*)table, xLookup);
	}
}