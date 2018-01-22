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

void BrickBuster() __attribute__ ((section ("Misc")));
void CallMemoryReset() __attribute__ ((section ("Misc")));
void GenericTests() __attribute__ ((section ("Misc")));


#ifdef sMemoryReset

void CallMemoryReset()
{		
	void (*func)() = (void(*)()) sMemoryReset;
	(*func)();//(*pMafSensorVoltage);
	//return *pMassAirFlow;
}
#endif


void GenericTests() 
{	
	
	ResetRamVariables();
	
	*pInjectorLastPulse = 6000;
	*pEngineSpeed = 7200;
	*pEngineLoad = 1.6;
	
	float speedDiff = -1;
	unsigned char cutRat = Pull2DHookedU8((TwoDTable*)&PLSL_CutRatioTable,*((float*)&speedDiff));	
	
	unsigned long rr = 14;
	rr = 14;
	unsigned short cutPattern = Pull2DHookedU16fp((TwoDTableU16*)&FuelCutTable,*((unsigned long*)&rr));	
	rr = 15;
	unsigned short cutPattern1 = Pull2DHookedU16fp((TwoDTableU16*)&FuelCutTable,*((unsigned long*)&rr));	
	rr = 21;
	unsigned short cutPattern2 = Pull2DHookedU16fp((TwoDTableU16*)&FuelCutTable,*((unsigned long*)&rr));
		
	InjectorTrims();
	
	float r1 = *pInjCompC1;
	float r2 = *pInjCompC2;
	float r3 = *pInjCompC3;
	float r4 = *pInjCompC4;
	
	pRamVariables.nINJCutPattern = 0x20FC;
	pRamVariables.nINJCutCTR = 0;
	
	InjectorTrims();
	 r1 = *pInjCompC1;
	 r2 = *pInjCompC2;
	 r3 = *pInjCompC3;
	 r4 = *pInjCompC4;
	
	InjectorTrims();
	 r1 = *pInjCompC1;
	 r2 = *pInjCompC2;
	 r3 = *pInjCompC3;
	 r4 = *pInjCompC4;
	 
	 InjectorTrims();
	 r1 = *pInjCompC1;
	 r2 = *pInjCompC2;
	 r3 = *pInjCompC3;
	 r4 = *pInjCompC4;
	 
	 InjectorTrims();
	 r1 = *pInjCompC1;
	 r2 = *pInjCompC2;
	 r3 = *pInjCompC3;
	 r4 = *pInjCompC4;
	 
	 InjectorTrims();
	 r1 = *pInjCompC1;
	 r2 = *pInjCompC2;
	 r3 = *pInjCompC3;
	 r4 = *pInjCompC4;
	
	
#if WIDEBAND_HACKS
	*pAFRsensedCurrent = 0.24;
	*pAFRConverted4 = 0;
	WideBandScaling();
#endif
	
#if CAN_HACKS
	CustomCanUnitTests();
#endif

#if REVLIM_HACKS
	RevLimUnitTests();
#endif
	
#if VIN_HACKS
	Assert(pRamVariables.VinAuth != 0x00,"Check VIN auth!");
#endif

#if CEL_HACKS
	CelFlashUnitTests();
#endif



#if SD_HACKS
	SpeedDensityUnitTests();
#endif

#if POLF_HACKS
	PolfHackUnitTests();
#endif

#if TIMING_HACKS
	TimingHackUnitTests();
#endif

#if PROG_MODE
	ProgModeUnitTests();
#endif

	BrickBuster();
}


void BrickBuster()
{
//declare and call all of the hook test points

#ifdef pRamHoleEnd
unsigned int test = pRamHoleEnd;
unsigned int end = (unsigned int)&(pRamVariables.RamHoleEndMarker);
if(test < end)
Assert(0,"error in ram hole!");
#endif

#if SD_HACKS
	CallSpeedDensityHook();//This covers SD and Revlim
#endif

#if WGDC_HOOK_DEFINED
	WGDCHack();	//This covers everything hooked into WGDC
					//Celflash and/or wgdc/boost hacks, progmode, pgwg
#endif

#if POLF_HACKS
	POLFHack();
#endif

#if TIMING_HACKS
	TimingHack();
#endif

	CallMemoryReset();
}

void SetValues() __attribute__ ((section ("Misc")));
void SetValues() 
{
	// These are just here to clarify the boundary between the prologue and the
	// 'real' code when stepping through in a debugger.
	asm("nop");
	asm("nop");

	// If you change compiler settings, inspect the way the variables get set.
	// Ideally it should take three instructions per assignment, with no 
	// references to other memory.  If this does reference other memory, patches
	// will be difficult to apply.
	
#if VIN_HACKS
	//Init VIN
	int i;
	int j = 16;
	for(i=0; i<16; i++)
	{
		pRamVariables.VehicleIdent[j] = VinBlock.Vin[i];
		*(pObdVinDirect + j) = VinBlock.Vin[i];
		j -= 4;
		if(j<0)
		{
			j += 15;
		}
	}
	
#endif
	
#if REVLIM_HACKS
	// LC/FFS test settings
	*pEngineSpeed = 1000.0f;
	*pVehicleSpeed = 12.0f;
	*pClutchFlags |= ClutchBitMask;
	*pFlagsRevLim &= ~RevLimBitMask;				
#endif
	
	// Speed-density test settings
	*pManifoldAbsolutePressure = 268.917649; // Corresponds to -9.5psiG, which is normal for idle.
	*pAtmoPress = 700;
	*pMafSensorVoltage = 1.5 * MafVoltageToInternalUnits;
}
