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

void (*MemoryResetHooked)() __attribute__ ((section ("RomHole_Functions"))) = (void(*)()) sMemoryReset;

void Initializer()
{
	MemoryResetHooked();
#if RAM_PERSIST
	InitRamVariables();
#else
	ResetRamVariables();
#endif

}

void ResetRamVariables()
{
	ClearRamVariables((long*)&pRamVariables,(long*)&pRamVariables.RamHoleEndMarker);
	PopulateRamVariables();
}

void InitRamVariables()
{
	if(pRamVariables.MasterInitFlag != 0xB4)
	{
		ClearRamVariables((long*)&pRamVariables,(long*)&pRamVariables.RamHoleEndMarker);
		PopulateRamVariables();
	}
}

void ClearRamVariables(long *start, long *end)
{
	long *pend = end;
	long *pointy = start;
	while(pointy < pend)
	{
		*pointy = 0x00000000;
		pointy++;
	}
}

void PopulateRamVariables()
{
	pRamVariables.VPLSL_Adjust = 0;
  	pRamVariables.nINJCutPattern = 0;
  	pRamVariables.nPLSLCutRatio = 0;
  	pRamVariables.bFFSallowed = DefaultFlatFootShiftMode;
  	pRamVariables.bFFSenabled = 1;
	pRamVariables.bLCengaged = 0;
  	pRamVariables.bFFSengaged = 0;
  	pRamVariables.bPLSLRequest = 0;
  	pRamVariables.bPLSLcutting = 0;
	
#if CRUISE_CONTROL
	pRamVariables.CruiseResumeLast = TestCruiseResumeSwitch();
	pRamVariables.CruiseCoastLast = TestCruiseCoastSwitch();
#endif

#if BOOST_HACKS
	pRamVariables.Boost_Adjust = 0;
	pRamVariables.rWG_Adjust = 0;
#endif

#if INJECTOR_HACKS
	//Injector Scalar init to default
	pRamVariables.InjectorScaling = *dInjectorScaling;
//	pRamVariables.nINJCutPattern = 0;
//	pRamVariables.nPLSLCutRatio = 0;
	pRamVariables.nINJFuncCTR = 0;	
	pRamVariables.nINJCutCTR = 0;
	
	pRamVariables.flexFuelSensorEnabaled = DefaultFlexFuelSensorEnabled;
	pRamVariables.fuelPressureFlowEnabled = DefaultkPFuelPressureEnabled;
#endif

#if SWITCH_HACKS
	pRamVariables.MapSwitch = DefaultMapSwitch;
	pRamVariables.MapBlendRatio = DefaultMapBlendRatio;
	pRamVariables.BlendMode = 0;
#endif

#if CAN_HACKS
	pRamVariables.initFunctionRun = 0;
	pRamVariables.rcp0x702_tick = 0;
	pRamVariables.rcp0x708_tick = 0;
	pRamVariables.rcp0x709_tick = 0;
	pRamVariables.rcp0x70A_tick = 0;
	pRamVariables.rgBackLight = 128;
//	pRamVariables.sdTimer = 0;
#endif 

#if PROG_MODE
//	pRamVariables.ProgModeEnable = 0;
	//pRamVariables.ProgModeWait = 0;
	//pRamVariables.ProgModeEntry = 0;
	//pRamVariables.ProgModeEnable = 0;
	pRamVariables.ProgModeCurrentMode = 0;
	unsigned char i = 0;
	while(i < rgButtonCount)
	{
		pRamVariables.buttons[i].bits.state = 0;
		pRamVariables.buttons[i].bits.led = 0;
		pRamVariables.buttons[i].bits.edgeDetect = 0;
		i++;	
	}
#endif

#if REVLIM_HACKS	
	//Revlimit mode init
	if (pRamVariables.RevLimMode == RevLimModeUndefined)
	{
		pRamVariables.RevLimMode = DefaultRevLimMode;
	}
	//Init revlimit cuts
//	pRamVariables.FlatFootShiftMode = DefaultFlatFootShiftMode;
	pRamVariables.RedLineCut = DefaultRedLineCut;
	pRamVariables.RedLineHyst = DefaultRedLineHyst;
	pRamVariables.FlatFootShiftHyst = DefaultFlatFootShiftHyst;
	pRamVariables.FlatFootShiftAutoDelta = DefaultFlatFootShiftAutoDelta;
	pRamVariables.FlatFootShiftStaticDelta = DefaultFlatFootShiftStaticDelta;
	pRamVariables.LaunchControlSpeedMax = DefaultLaunchControlSpeedMax;
	pRamVariables.LaunchControlCut = DefaultLaunchControlCut;
	pRamVariables.LaunchControlHyst = DefaultLaunchControlHyst;
	pRamVariables.FlatFootShiftSpeedThreshold = DefaultFlatFootShiftSpeedThreshold;
	pRamVariables.FlatFootShiftRpmThreshold = DefaultFlatFootShiftRpmThreshold;
	//pRamVariables.bPLSLRequest = 0;
	//pRamVariables.bPLSLcutting = 0;
	//pRamVariables.VPLSL_Adjust = 0;
#endif 

#if VIN_HACKS
	VinCheck();
#endif

#if SPARK_HACKS
	//Init spark cut
	*LCSparkEventsToCut = DefaultLCSparkEventsToCut;
	*LCSparkEventsCutFrom = DefaultLCSparkEventsCutFrom;
#endif

#if POLF_HACKS
	pRamVariables.PolfHackEnabled = DefaultPolfHackEnabled;
	if (pRamVariables.LCFuelMode == LCFuelModeUndefined)
	{
		pRamVariables.LCFuelMode = DefaultLCFuelMode;
	}
	pRamVariables.LCFuelLock = DefaultLCFuelLock;
	pRamVariables.LCFuelEnrichMultiplier = DefaultLCFuelEnrichMultiplier;
#endif

#if TIMING_HACKS
	pRamVariables.TimingHackEnabled = DefaultTimingHackEnabled;

	if (pRamVariables.LCTimingMode == LCTimingModeUndefined)
	{
		pRamVariables.LCTimingMode = DefaultLCTimingMode;
	}
	pRamVariables.LCTimingLock = DefaultLCTimingLock;
	pRamVariables.LCTimingRetardMultiplier = DefaultLCTimingRetardMultiplier;
#endif

#if SD_HACKS
	pRamVariables.MafMode = DefaultMafMode;
	pRamVariables.AFRSource = AFRModeStock;
#endif

pRamVariables.ecuHacksMainCtr = 0x00;
pRamVariables.MasterInitFlag = 0xB4;//TODO Absract this
}

#if VIN_HACKS

void VinCheck()
{
	//Init VIN	
}

#endif