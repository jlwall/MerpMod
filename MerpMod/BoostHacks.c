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

#if WGDC_HOOK_DEFINED

//Defines the function pointer to the existing WGDC Pull routine
float (*WGDCHooked)() __attribute__ ((section ("RomHole_Functions"))) = (float(*)()) sWgdc;

void WGDCHack()
{

#if WGDC_MAIN_HOOK
EcuHacksMain();
#endif

#if BOOST_HACKS	

	//Calculated gear is a BYTE!
	float cgear = (char)*pCurrentGear;
	float PGWGComp;
	float WGDCInitial;
	float WGDCMax;

	#if SWITCH_HACKS
		PGWGComp = BlendAndSwitch(PGWGTableGroup, cgear, *pEngineSpeed);
	#else
		PGWGComp = Pull3DHooked(PGWGTable1i, cgear, *pEngineSpeed);
	#endif
	
	WGDCInitial = Pull3DHooked(&tInitialWasteGate, pRamVariables.TargetBoost, *pEngineSpeed);
	WGDCMax = Pull3DHooked(&tMaximumWasteGate, pRamVariables.TargetBoost, *pEngineSpeed);
	
	pRamVariables.PGWGComp = PGWGComp;
	
	#if WGDC_LOCK
	//Apply locks
	if(*pEngineSpeed < RPMLockWGDC && *pThrottlePlate > ThrottleLockWGDC)
	{
		pRamVariables.WGDCInitial = 100.0;
		pRamVariables.WGDCMax = 100.0;
	}
	else{
	#endif
	
	#if PROG_MODE		
		if(pRamVariables.TargetBoost > 915.25)  //Only add if over 3psi targt request
		{
			WGDCInitial += pRamVariables.rWG_Adjust;
			WGDCMax += pRamVariables.rWG_Adjust;
		}
	#endif
	
	if(pRamVariables.ValetMode == ValetModeDisabled)
		{
		pRamVariables.WGDCInitial = WGDCInitial * PGWGComp;
		pRamVariables.WGDCMax = WGDCMax * PGWGComp;
		}
	else
		{
		pRamVariables.WGDCInitial = 0;
		pRamVariables.WGDCMax = 0;
		}
	
	#if WGDC_LOCK
	}
	#endif
	
#endif

	//Finish Pulling WGDC
	WGDCHooked();
	
#if BOOST_HACKS
	TargetBoostHack();
#endif
}

#if BOOST_HACKS
void TargetBoostHack()
{
		//Calculated gear is a BYTE!
	float cgear = (char)*pCurrentGear;
	float PGTBComp;
	float TargetBoost;
		
	#if SWITCH_HACKS
		PGTBComp = BlendAndSwitch(PGTBTableGroup, cgear, *pEngineSpeed);
		TargetBoost = BlendAndSwitch(TargetBoostTableGroup, *pReqTorque, *pEngineSpeed);
	#else
		PGTBComp = Pull3DHooked(PGTBTable1i, cgear, *pEngineSpeed);
		TargetBoost = Pull3DHooked(TargetBoostTable1i, *pReqTorque, *pEngineSpeed);
	#endif

	#if PROG_MODE
		TargetBoost += pRamVariables.Boost_Adjust;
	#endif
	
	if(pRamVariables.ValetMode == ValetModeEnabled)	//If Valet Mode, limit MaxBoost
		{
		if(pRamVariables.TargetBoost > ValetModeMaxBoost)
			pRamVariables.TargetBoost = ValetModeMaxBoost;	
		}
	
	pRamVariables.PGTBComp = PGTBComp;
	pRamVariables.TargetBoost = TargetBoost * PGTBComp;
	
}
#endif
#endif