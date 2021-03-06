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

#if CRANK_FUELING_HACKS

void crankFuelHacks()
{
	if(*pCrankEngineRunning > 0)
		return;
	else
		{
			float opLow = 0;
			float opHigh = 0;
			if(*pCrankFuelABC==0)			
				{
				opLow = Pull2DHooked((void*)tCrankFuel_ECT_A, *pTwater);	
				opHigh = Pull2DHooked((void*)tCrankFuel_ECT_D, *pTwater);			
				}
			else if(*pCrankFuelABC==1)			
				{
				opLow = Pull2DHooked((void*)tCrankFuel_ECT_B, *pTwater);	
				opHigh = Pull2DHooked((void*)tCrankFuel_ECT_E, *pTwater);			
				}
			else
				{
				opLow = Pull2DHooked((void*)tCrankFuel_ECT_C, *pTwater);	
				opHigh = Pull2DHooked((void*)tCrankFuel_ECT_F, *pTwater);			
				}		
		float crankMixed = opLow  + ((opHigh- opLow) * pRamVariables.MapBlendRatio );		
		*pCrankFuelPulse = crankMixed;				
		}	
}

#endif

#if CAN_HACKS

void canAEMTimeOutDiagnostics()
{
	if(pRamVariables.aemPacketCTR > 0)
		pRamVariables.aemPacketValid = 1;
	else
		pRamVariables.aemPacketValid = 0;
		
	pRamVariables.aemPacketCTR = 0;
		
}

void canCallbackAEMwideband(unsigned char* data)
{
	pRamVariables.aemLambda = (float)(data[0]*256 + data[1])*0.0001;
	pRamVariables.aemOxygen = (float)(data[2]*256 + data[3])*0.001;
	pRamVariables.aemDataValid = (unsigned char)(data[6])>>7&0x01;
	pRamVariables.aemSensorFault = (unsigned char)(data[7])>>6&0x01;
	pRamVariables.aemPacketCTR++;	
}

void canCallbackMK3e85Packet(unsigned char* data)
{
	pRamVariables.rEthanolCAN = (float)(data[0])*0.003921568627; 		//0 to 255 for 0 to 100% 1/255 LSB/%	
	pRamVariables.tFuelCAN = (float)(data[1])-40;	//0 to 165 for -40 to 125C
	pRamVariables.pFuelCan = (float)(data[2])/3.8;	//0 to 67psig
	pRamVariables.pFuelCanRel = pRamVariables.pFuelCan - ((*pManifoldAbsolutePressure-760)/51.71492510510006);
	pRamVariables.pFuelCanRelFilt = (((1-xFuelPressureFilter)* pRamVariables.pFuelCanRelFilt) + (xFuelPressureFilter * pRamVariables.pFuelCanRel));
	
	#if POLF_HACKS
		//Update scale for fuel Pressure
		if(pRamVariables.fuelPressureFlowEnabled == 1)
		{		
			pRamVariables.kFuelPressure = sqrt(pRamVariables.pFuelCanRelFilt/BaseInjectorFlowPressureRelative);
		}
		else
			pRamVariables.kFuelPressure = 1;
	
	
	#endif
}

#endif

#if POLF_HOOK_DEFINED
	void (*PolfHooked)() __attribute__ ((section ("RomHole_Functions"))) = (void(*)()) sPolf;

#if INJECTOR_HACKS
void InjectorTrims()
{
	unsigned char ctActive = 0;
	unsigned char i = 0;
	unsigned char iRot = 0;
	*pInjCompC1 = Pull3DHooked((void*)TabInjCompC1, *pInjectorLastPulse, *pEngineSpeed);
	*pInjCompC2 = Pull3DHooked((void*)TabInjCompC2, *pInjectorLastPulse, *pEngineSpeed);
	*pInjCompC3 = Pull3DHooked((void*)TabInjCompC3, *pInjectorLastPulse, *pEngineSpeed);
	*pInjCompC4 = Pull3DHooked((void*)TabInjCompC4, *pInjectorLastPulse, *pEngineSpeed);
	pRamVariables.nINJFuncCTR++;
	if(pRamVariables.nINJCutPattern != 0) //If we have an active Cut Pattern, lets apply
	{	
		iRot = ((unsigned char)(pRamVariables.nINJCutCTR>>2))<<2;

		ctActive = pRamVariables.nINJCutPattern;
		while(i<iRot)
		{
			ctActive = ctActive >> 1;
			i++;
			//Rotates through a Nibble of the CuttPattern each round
		}
		if((ctActive & 0x01) > 0) *pInjCompC1 = 0; //Kill C1
		if((ctActive & 0x02) > 0) *pInjCompC3 = 0; //Kill C3
		if((ctActive & 0x04) > 0) *pInjCompC4 = 0; //Kill C4
		if((ctActive & 0x08) > 0) *pInjCompC2 = 0; //Kill C2

		pRamVariables.nINJCutCTR++;	//Increment the Cut Counter to select the next nibble
		if(pRamVariables.nINJCutCTR > 16) //Roll over the cut pattern
			pRamVariables.nINJCutCTR = 0;
	}
	else
		pRamVariables.nINJCutCTR = 0;
}
#endif

#if WIDEBAND_HACKS
void WideBandScaling()
{
	float afrTemp = 0;
	if((pRamVariables.AFRSource == AFRModeStock) || (pRamVariables.aemDataValid == 0))
	{		
		*pAFRConverted4 = Pull2DHooked((void*)tAFRSensorScaling, *pAFRsensedCurrent);
	}
	else if(pRamVariables.AFRSource == AFRModeBlend)
	{
		afrTemp = pRamVariables.aemLambda;
		afrTemp += Pull2DHooked((void*)tAFRSensorScaling, *pAFRsensedCurrent);
		afrTemp *= 0.5f;
		*pAFRConverted4 = afrTemp;
	}
	else if(pRamVariables.AFRSource == AFRModeWide)
	{
		*pAFRConverted4 = pRamVariables.aemLambda;
	}
	else
	{
		pRamVariables.AFRSource = AFRModeStock;
	}
	
}
#endif


//LOL function
void WideBandOpenLoopFeedback()
{
	float rLamTarget = 1/(1+pRamVariables.PolfOutput);
	pRamVariables.rLOL_error = (rLamTarget - pRamVariables.aemLambda) / rLamTarget;
	
	if((*pCLOL == 4) && (pRamVariables.aemPacketValid == 1) && ((pRamVariables.nStateLOL & 0x01) == 0x01))
	{
		pRamVariables.rLOL_pTerm  = Pull2DHooked((void*)&pLOL_PTermGainTable, pRamVariables.rLOL_error);	
		pRamVariables.rLOL_iTerm += pRamVariables.rLOL_error * Pull2DHooked((void*)&pLOL_ITermGainTable, pRamVariables.rLOL_error);
		
		if(pRamVariables.rLOL_iTerm >  WBLOL_iTermMax) pRamVariables.rLOL_iTerm =  WBLOL_iTermMax;
		else if(pRamVariables.rLOL_iTerm < WBLOL_iTermMin) pRamVariables.rLOL_iTerm = WBLOL_iTermMin;
		
		pRamVariables.nStateLOL |= 0x02;
		pRamVariables.rLOL_finalScale = pRamVariables.rLOL_pTerm + pRamVariables.rLOL_iTerm;
		if(pRamVariables.rLOL_finalScale >  WBLOL_finalTermMax) pRamVariables.rLOL_finalScale =  WBLOL_finalTermMax;
		else if(pRamVariables.rLOL_finalScale < WBLOL_finalTermMin) pRamVariables.rLOL_finalScale = WBLOL_finalTermMin;
	}
	else
	{
		pRamVariables.nStateLOL &= 0xFD;
		pRamVariables.rLOL_pTerm = 0;
		pRamVariables.rLOL_iTerm = 0;
		pRamVariables.rLOL_finalScale = 0;	
	}
}

void UpdateInjectorFlow()
{
	#if INJECTOR_HACKS
		//Update Injector scaling based off new 	
		if(pRamVariables.flexFuelSensorEnabaled == 1)	
		{
			#if SWITCH_HACKS	
				pRamVariables.TargetedStoich = Pull2DHooked(&FlexFuelStoichTable, pRamVariables.rEthanol);	 
			#else
				pRamVariables.TargetedStoich = 14.65;
			#endif		
			if(pRamVariables.fuelPressureFlowEnabled == 1)			
				pRamVariables.InjectorScaling =   (BaseGasolineAFR / pRamVariables.TargetedStoich) / pRamVariables.kFuelPressure *  (*dInjectorScaling);		
			else
				pRamVariables.InjectorScaling =   (BaseGasolineAFR / pRamVariables.TargetedStoich) *  (*dInjectorScaling);		
		}
		else
		{
			pRamVariables.TargetedStoich = 14.65;
			if(pRamVariables.fuelPressureFlowEnabled == 1)			
				pRamVariables.InjectorScaling = (*dInjectorScaling) / pRamVariables.kFuelPressure;			
			else
				pRamVariables.InjectorScaling = (*dInjectorScaling);		
		}
		
		if((*pCLOL == 4) && ((pRamVariables.nStateLOL & 0x01) == 0x01))
			pRamVariables.InjectorScaling *= (1 + pRamVariables.rLOL_finalScale);
	#endif	
}

void POLFHack()
{		
#if POLF_MAIN_HOOK
EcuHacksMain();
#endif

#if POLF_HACKS
	float OutputValue;
	
	WideBandOpenLoopFeedback();
	UpdateInjectorFlow();

	#if POLF_RAM_TUNING
		if(pRamVariables.POLFRamFlag = 0x01)
		{
			OutputValue = Pull3DHooked(&FuelRamTable, *pEngineLoad, *pEngineSpeed);
		}
		else
		{
	#endif
			OutputValue	= BlendAndSwitch(FuelTableGroup, *pEngineLoad, *pEngineSpeed);
	#if POLF_RAM_TUNING
		}
	#endif
		pRamVariables.LCFuelEnrich = Pull3DHooked(&LCFuelEnrichTable, *pVehicleSpeed, *pEngineSpeed) * pRamVariables.LCFuelEnrichMultiplier;
	
		if(pRamVariables.LCFuelMode == LCFuelModeCompensated)
		{
			OutputValue += pRamVariables.LCFuelEnrich;
		}
		//Now run existing code!
	
		pRamVariables.PolfTarget = OutputValue;
	
		if(pRamVariables.PolfHackEnabled == 0)
			pRamVariables.PolfOutput = pRamVariables.PolfTarget;
		else
			pRamVariables.PolfOutput = Pull3DHooked((void*)PrimaryOEMPolfTable, *pEngineLoad, *pEngineSpeed);					
#endif
		
	PolfHooked();
}
#endif
