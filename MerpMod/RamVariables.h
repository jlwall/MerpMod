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

//////////////////////////
//RAM VARIABLES STRUCTURE
//////////////////////////

//#ifndef RAMVAR_H
//#define RAMVAR_H

typedef struct
{
	unsigned char MasterInitFlag; 		//00
	unsigned char ecuHacksMainCtr;		//01
	
	#if INJECTOR_HACKS
		float InjectorScaling;			//04
	#endif

#if CAN_HACKS
	unsigned short initFunctionRun;				//20	
	unsigned short ccmSendTimers[ccmCount];		//12

	#if POLF_HACKS
		unsigned char fuelPressureFlowEnabled;		//10
		unsigned char flexFuelSensorEnabaled;		//11
	#endif

	#if RACEGRADE_KEYPAD_HACKS
		buttonRGStruct buttons[8];				//24
		unsigned char rgBackLight;					//22
	#endif
	
	#ifdef RCP_CAN
		unsigned char rcpFrameState;
	#endif
	
	#if AEMXFINITY
		float rEthanolCAN;
		float tFuelCAN;		
		float pFuelCan;	
		float pFuelCanRel;
		float aemLambda;
		float aemOxygen;
		float vFuelPressureRel;
		unsigned char aemDataValid;
		unsigned char aemSensorFault;
		unsigned char aemn1;
		unsigned char aemn2;
	#endif
#endif



#if SWITCH_HACKS	
	float MapBlendRatio;
	#ifdef TGV_USE
		float TGVLeftVolts;
		float TGVRightVolts;
		float TGVLeftScaled;
		float TGVRightScaled;
	#endif
	unsigned char MapSwitch;
	unsigned char null1;
	unsigned char null2;
	unsigned char null3;
#endif

#if SD_HACKS
	float VolumetricEfficiency;	//	96d
	float MafFromSpeedDensity;
	float MafFromSensor;
	float AtmosphericCompensation; //96
	float DeltaMapCompensation;	
	float SDMafBlendRatio;
	float SDMafFromBlend;
	unsigned char SDInitFlag;		//96d
	unsigned char MafMode;	
#endif
	
#if REVLIM_HACKS
	//Rev Limiter params
	unsigned char  	RevLimInitFlag;  //96
	unsigned char  	RevLimMode;
	char	bPLSLRequest;
	char	bPLSLcutting;
	char	FlatFootShiftMode;
	char	LCEngaged;
	char	FFSEngaged;
	char	elemptteey;
	unsigned char	FFSGear;
	float 	RevLimCut;	//96
	float 	RevLimResume;
  	float  	RedLineCut;
	float	RedLineHyst;	//9
	float	LaunchControlSpeedMax;
  	float  	LaunchControlCut;	
	float  	LaunchControlHyst;
 	float  	FFSRPM;
	float 	FlatFootShiftRpmThreshold;
	float	FlatFootShiftAutoDelta;
	float	FlatFootShiftStaticDelta;
	float  	FlatFootShiftHyst;	//9
  	float  	FlatFootShiftSpeedThreshold; //97
	float	VPLSL_Adjust;
#endif
	
#if CEL_HACKS
	// New variables needed for the CEL Flash Hack
	unsigned char CelSignal;				
	unsigned char CelSignalLast;				
	unsigned char CruiseSignal;			
	unsigned char CruiseSignalLast;	
		
	unsigned char CelFlashSpeed;				
	unsigned char CelFlashSpeedCounter;
	unsigned char CelFlashCount;			
	unsigned char CelFlashCounter;
			
	unsigned char CelRepeatSwitch;
	unsigned char CelFlashStatus;
	unsigned char CelFlashDelay;
	unsigned char celunused;
	
	//unsigned char CruiseSpeedCounter;			
	//unsigned char CruiseFlashCounter;

#endif

#if PROG_MODE
	unsigned char ProgModeEnable;
	unsigned char ProgModeTimer;
	unsigned char ProgModeEntry;
	unsigned char ProgModeWait;
	unsigned char ProgModeCurrentMode;
	unsigned char ProgModeValueFlashes;
	unsigned char ValetMode;
	unsigned char BlendMode;
	float ProgModeValue;
#endif			

#if TIMING_HACKS
	//Timing Hack params
	unsigned char 	TimingHackInitFlag;		//97
	unsigned char 	LCTimingMode;
	unsigned char	TimingHackEnabled;
	char	Tempty1;	
	float	BaseTiming;
	float 	TimingHackOutput;	//97
	float 	LCTimingRetard;		//97
	float 	LCTimingLock;		//97
	float	LCTimingLockRPM;
	float	LCTimingRetardMultiplier;
	float	SubtractiveKCA;
	float	MaxSubtractiveKCA;
#endif

#if POLF_HACKS
	//Fuel Hack params
	unsigned char 	POLFuelHackInitFlag;	//97
	unsigned char 	LCFuelMode;
	unsigned char	PolfHackEnabled;
	unsigned char	eeeeeeee;	
	float PolfTarget;
	float PolfOutput;		//97
	float LCFuelEnrich;			//97
	float LCFuelLock;			//97
	float LCFuelEnrichMultiplier;
	float TargetedStoich;		//	08
	float kFuelPressure;		//	0C
#endif

#if BOOST_HACKS	
	//Target Boost Params
	float TargetBoost;
		
	//PGWG Params
	float PGWGComp;
	float PGTBComp;
	
	//WGDC Params
	float WGDCInitial;
	float WGDCMax;
#endif
	
#if SPARK_CUT
	unsigned char SparkEventsX;
	unsigned char se;
	unsigned char se1;
	unsigned char se2;
	unsigned char SparkEventsY;
	unsigned char se3;
	unsigned char se4;
	unsigned char se5;
#endif
	
#if VIN_HACKS
	unsigned char VehicleIdent[20];
#endif

#if CRUISE_CONTROL
	unsigned char CruiseCoastLast;		//02
	unsigned char CruiseResumeLast;		//03
#endif
	
#if VE_RAMTUNING
//VE RAMTUNING
	unsigned char VERamFlag;
	unsigned char emptypaafr;
	unsigned char emptypdfr1;
	unsigned char emptyprdafd2;
	float VERamCols[24];
	float VERamRows[24];
	short VERamData[576];
#endif

#if TIMING_RAMTUNING
//VE RAMTUNING
	unsigned char TimingRamFlag;
	unsigned char emptypadr;
	unsigned char emptyprdadf1;
	unsigned char emptypfadfr2;
	float TimingRamCols[20];
	float TimingRamRows[20];
	unsigned char TimingRamData[400];
#endif

#if POLF_RAMTUNING
//VE RAMTUNING
	unsigned char POLFRamFlag;
	unsigned char emptypr;
	unsigned char emptypr1;
	unsigned char emptypr2;
	float POLFRamCols[20];
	float POLFRamRows[20];
	unsigned char POLFRamData[400];
	unsigned char LCFuelEnrichRamFlag;
	unsigned char emptylcfe;
	unsigned char emptylcfe1;
	unsigned char emptylcfe2;
	float LCFuelEnrichCols[20];
	float LCFuelEnrichRows[20];
	unsigned char LCFFuelEnrichData[400];
#endif

	
#if PGWG_RAMTUNING
	//PGWG RAMTUNING
	unsigned char PGWGRamFlag;
	unsigned char emptypadfdr;
	unsigned char emptyprada1;
	unsigned char emptypddfrfaf2;
	float PGWGRamCols[6];
	float PGWGRamRows[10];
	short PGWGRamData[60];
#endif

	
#if WGDC_RAMTUNING
	//WGDC RAMTUNIN
	unsigned char WGDCInitialRamFlag;
	unsigned char emptywi1;
	unsigned char emptywi2;
	unsigned char emptywi3;
	float WGDCInitialRamCols[6];
	float WGDCInitialRamRows[10];
	short WGDCInitialRamData[60];
	unsigned char WGDCMaxRamFlag;
	unsigned char emptywm1;
	unsigned char emptywm2;
	unsigned char emptywm3;
	float WGDCMaxRamCols[6];
	float WGDCMaxRamRows[10];
	short WGDCMaxRamData[60];
#endif

#if PORT_LOGGER
	unsigned char testchar1;
	unsigned char testchar2;
	unsigned char testchar3;
	unsigned char testchar4;
	unsigned short PortParameters[20];
	
#endif
long	RamHoleSpace;
char	RamHoleEndMarker;
	
	//IF ADDING PARAMS, MUST UPDATE SPARK CUT ASM!!!!
	
}RamVariables;


//#endif