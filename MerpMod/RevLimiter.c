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

#if REVLIM_HACKS

void RevLimReset()
{

	if (pRamVariables.ValetMode == ValetModeEnabled)
	{
		pRamVariables.RevLimCut = ValetModeRevLim;
		pRamVariables.RevLimResume = ValetModeRevLim - Abs(DefaultFlatFootShiftHyst);
	}
	else
	{
		pRamVariables.RevLimCut = DefaultRedLineCut;
		pRamVariables.RevLimResume = DefaultRedLineCut - Abs(DefaultRedLineHyst);	
	}

	//pRamVariables.RevLimCut = pRamVariables.RedLineCut;
	//pRamVariables.RevLimResume = pRamVariables.RedLineCut - Abs(pRamVariables.RedLineHyst);
	//Disable FFS if clutch is out or brake is pressed
	pRamVariables.FFSEngaged = 0;
	pRamVariables.LCEngaged = 0;
	if(*pCurrentGear > 0)
	{
		pRamVariables.FFSGear = *pCurrentGear;
	}
}

void RevLimCode()
{	

		
	if (!TestClutchSwitch() || TestBrakeSwitch())
	{
			RevLimReset();
	}
	else
	{
		//check for FFS speed threshold
		if (*pVehicleSpeed > pRamVariables.FlatFootShiftSpeedThreshold 
			&& *pEngineSpeed > pRamVariables.FlatFootShiftRpmThreshold 
			&& pRamVariables.FlatFootShiftMode != 0 
			&& *pThrottlePlate > FFSMinimumThrottle)
		{
			pRamVariables.LCEngaged = 0;
			
			//calculate target rpm
			if(pRamVariables.FFSEngaged == 0)
			{
				pRamVariables.FFSEngaged = 1;
				pRamVariables.FFSRPM = *pEngineSpeed;
			}
		}
		else if (*pVehicleSpeed < pRamVariables.LaunchControlSpeedMax && *pThrottlePlate > LCMinimumThrottle)
		{
			// Launch control rev limiter thresholds.
			pRamVariables.FFSEngaged = 0;
			pRamVariables.LCEngaged = 1;
			pRamVariables.RevLimCut = pRamVariables.LaunchControlCut;
			pRamVariables.RevLimResume = pRamVariables.LaunchControlCut - Abs(pRamVariables.LaunchControlHyst);
		}
		else if (pRamVariables.bPLSLRequest == 1)
		{
			if((pRamVariables.bPLSLcutting == 0) && (*pVehicleSpeed > (NPLSL_Limit + pRamVariables.VPLSL_Adjust)))
				{
				pRamVariables.bPLSLcutting = 1;
				}
			else if((pRamVariables.bPLSLcutting == 1 ) && (*pVehicleSpeed < (NPLSL_Limit + pRamVariables.VPLSL_Adjust - Abs(NPLSL_Hyst))))
				{
				pRamVariables.bPLSLcutting = 0;
				}
		}
		else
			RevLimReset();
	}
	
	if (pRamVariables.FFSEngaged == 1)
	{
		if (pRamVariables.FlatFootShiftMode == 2) //This is Automatic Mode
		{
			float cut =  pRamVariables.FFSRPM;
			cut *=  GearRatios[(int)pRamVariables.FFSGear + 1]; 
			cut *= 1 / GearRatios[(int)pRamVariables.FFSGear];
			cut += pRamVariables.FlatFootShiftAutoDelta;
			pRamVariables.RevLimCut = cut;
			pRamVariables.RevLimResume = pRamVariables.RevLimCut - Abs(pRamVariables.FlatFootShiftHyst);
		}
		else  // This is Static Mode
		{	
			float cut = pRamVariables.RedLineCut - Abs(pRamVariables.FlatFootShiftStaticDelta);
			pRamVariables.RevLimCut = cut;
			pRamVariables.RevLimResume = cut - Abs(pRamVariables.FlatFootShiftHyst);
			pRamVariables.FFSEngaged = 2;
		}
	}
		
		

	
	//Add a SW unadjustable Hard Limit, having this in ram only is not safe
	if (*pEngineSpeed > pRamVariables.RevLimCut || *pEngineSpeed > pRamVariables.RedLineCut || *pEngineSpeed > 7500 )
		{
			*pFlagsRevLim |= RevLimBitMask;
		} 
		else if (*pEngineSpeed < pRamVariables.RevLimResume)
		{
			*pFlagsRevLim &= ~RevLimBitMask;
		}
}
#endif
